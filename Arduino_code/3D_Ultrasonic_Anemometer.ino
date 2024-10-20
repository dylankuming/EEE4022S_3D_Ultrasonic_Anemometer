/*
 * Ultrasonic Anemometer Sketch, v0.2 (3D Version)
 * Modified for 3D version by Dylan Kuming
 * 2024-09-27
 */

#include <math.h>
#include <LiquidCrystal.h>

// Pin definitions for the LCD
#define LCD_RS A1
#define LCD_RW A2
#define LCD_EN A3
#define LCD_D7 3
#define LCD_D6 4
#define LCD_D5 5
#define LCD_D4 6

// Initialize LCD object
LiquidCrystal lcd(LCD_RS, LCD_RW, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// Pin definitions for the ultrasonic system
#define AXIS1 13
#define AXIS2 12
#define DIRECTION 11
#define SIGNAL 10
#define MUTE 9
#define ZEROCROSSING 8
#define TEMPERATURE_SENSOR A0
#define TMR1_COMPB_INT A5
#define TMR1_CAPTURE_INT A4
#define CALC 2

// Direction definitions for the axes
#define NORTH_TO_SOUTH 0 /* Axis1=L, Direction=L, Axis2=L */
#define EAST_TO_WEST 1   /* Axis1=L, Direction=L, Axis2=H */
#define SOUTH_TO_NORTH 2 /* Axis1=L, Direction=H, Axis2=L */
#define WEST_TO_EAST 3   /* Axis1=L, Direction=H, Axis2=H */
#define TOP_TO_BOTTOM 4  /* Axis1=H, Direction=L, Axis2=L */
#define BOTTOM_TO_TOP 5  /* Axis1=H, Direction=L, Axis2=H */

// Constants
#define NUMBER_OF_ROUNDS 32
#define NUMBER_OF_ZEROCROSSINGS 16
#define DISTANCE 0.2  // Distance between transducers in meters

// Variables to handle timing and measurement
volatile uint8_t pulse_count;
volatile uint8_t axis_direction;
volatile uint8_t round_count;
volatile uint8_t measure_set;
volatile uint8_t calc_set;
volatile uint8_t done_flag;
volatile uint32_t envelope[2][6];  // Stores envelope times for 6 directions
volatile uint8_t zerocrossing_count;
volatile uint32_t zerocrossing[2][6][NUMBER_OF_ROUNDS];  // Zero-crossing times for 6 directions

// Time-of-flight variables for each direction
int32_t envelope_tof_ns[6];      // Envelope ToF for 6 directions
int32_t zerocrossing_tof_ns[6];  // Zero-crossing ToF for 6 directions

// Variables for wind speed calculations
float wind_ns_total = 0;
float wind_ew_total = 0;
float wind_tb_total = 0;
uint8_t sample_count = 0;

// PWM settings for timing (compare register values)
#define OCR1AH_PWM 0x01  // PWM setting for Output Compare Register A
#define OCR1AL_PWM 0x8F  // PWM setting for Output Compare Register A
#define OCR1BH_PWM 0x00  // PWM setting for Output Compare Register B
#define OCR1BL_PWM 0xC7  // PWM setting for Output Compare Register B
#define OCR1AH_LONG 0xC4 // Long setting for Output Compare Register A (double interval)
#define OCR1AL_LONG 0xDE // Long setting for Output Compare Register A (double interval)
#define OCR1BH_LONG 0x0F // Long setting for Output Compare Register B (double interval)
#define OCR1BL_LONG 0x9E // Long setting for Output Compare Register B (double interval)

void setup() {
  // Initialize control variables
  pulse_count = 0;
  axis_direction = 0;
  round_count = 0;
  measure_set = 0;
  calc_set = 1;
  done_flag = 0;
  sample_count = 0;
  wind_ns_total = 0;
  wind_ew_total = 0;
  wind_tb_total = 0;

  // Configure pins as outputs
  pinMode(AXIS1, OUTPUT);
  pinMode(AXIS2, OUTPUT);
  pinMode(DIRECTION, OUTPUT);
  pinMode(SIGNAL, OUTPUT);
  pinMode(MUTE, OUTPUT);
  pinMode(TMR1_COMPB_INT, OUTPUT);
  pinMode(TMR1_CAPTURE_INT, OUTPUT);
  pinMode(CALC, OUTPUT);

  // Initialize serial communication
  Serial.begin(9600);

  // Configure Timer1 for Fast PWM mode, prescaler=1
  TCCR1A = 0b00100011;
  TCCR1B = 0b11011001;
  TIMSK1 = 0b00000100;

  // Set PWM values in the output compare registers
  OCR1AH = OCR1AH_PWM;
  OCR1AL = OCR1AL_PWM;
  OCR1BH = OCR1BH_PWM;
  OCR1BL = OCR1BL_PWM;

  // Analog comparator settings
  ADCSRB = 0b00000000;
  ACSR = 0b01000100;

  // Initialize LCD display
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("3D Ultrasonic");
  lcd.setCursor(0, 1);
  lcd.print("Anemometer");
}

// Timer1 Compare B interrupt service routine
ISR(TIMER1_COMPB_vect) {
  digitalWrite(TMR1_COMPB_INT, HIGH); // Signal interrupt
  ++pulse_count;

  switch (pulse_count) {
    case 15:
      TCCR1A = 0b00000011;  // Disable PWM output
      OCR1AH = OCR1AH_LONG; // Set longer interval
      OCR1AL = OCR1AL_LONG;
      OCR1BH = OCR1BH_LONG;
      OCR1BL = OCR1BL_LONG;
      break;

    case 16:
      digitalWrite(MUTE, LOW);  // Unmute the amplifier for listening
      ACSR = 0b01000100;        // Analog comparator trigger
      TIFR1 = 0b00100000;       // Clear interrupt flag
      TIMSK1 = 0b00100100;      // Enable input capture interrupts
      zerocrossing_count = 0;
      OCR1AH = OCR1AH_PWM;      // Reset PWM values
      OCR1AL = OCR1AL_PWM;
      OCR1BH = OCR1BH_PWM;
      OCR1BL = OCR1BL_PWM;
      break;

    case 17:
      ++axis_direction;
      if (axis_direction >= 6) {
        axis_direction = 0;  // Reset direction when all have been measured
      }

      digitalWrite(MUTE, HIGH); // Mute amplifier for the next pulse

      // Set axis and direction for the next measurement
      digitalWrite(DIRECTION, (axis_direction & 0b010) ? HIGH : LOW);
      digitalWrite(AXIS2, (axis_direction & 0b001) ? HIGH : LOW);
      digitalWrite(AXIS1, (axis_direction & 0b100) ? HIGH : LOW);

      if (axis_direction == 0) {
        ++round_count;
        if (round_count == NUMBER_OF_ROUNDS) {
          round_count = 0;
          measure_set ^= 1;   // Toggle measurement and calculation set
          calc_set ^= 1;
          done_flag = 1;      // Measurement done

          // Reset envelope values
          for (uint8_t i = 0; i < 6; ++i) {
            envelope[measure_set][i] = 192000;
          }
        }
      }
      break;

    case 18:
      TCCR1A = 0b00100011; // Enable PWM output
      pulse_count = 0;     // Reset pulse count
      break;
  }
  digitalWrite(TMR1_COMPB_INT, LOW); // Clear interrupt signal
}

// Timer1 Input Capture interrupt service routine for actual measurement
ISR(TIMER1_CAPT_vect) {
  asm("sbi %0, %1 \n\t" ::"I"(_SFR_IO_ADDR(PORTC)), "I"(PORTC4));  // Set pin A4 high

  uint16_t timer_value;
  uint8_t timer_low = ICR1L;  // Capture timer value
  timer_value = ICR1H;
  timer_value <<= 8;
  timer_value |= timer_low;

  if (zerocrossing_count == 0) {
    envelope[measure_set][axis_direction] += timer_value;  // Add value to envelope
    zerocrossing[measure_set][axis_direction][round_count] = 72000; // Initialize zero-crossing value
    ACSR = 0b01000000;  // Set zero-crossing detector as input capture source
    TCCR1B = 0b11011001;  // Start with rising edge
  } else {
    zerocrossing[measure_set][axis_direction][round_count] += timer_value;  // Add to zero-crossing
    TCCR1B ^= 0b01000000;  // Toggle edge for next capture

    if (zerocrossing_count == NUMBER_OF_ZEROCROSSINGS) {
      TIMSK1 = 0b00000100;  // Disable input capture interrupts
    }
  }

  ++zerocrossing_count;
  asm volatile("cbi %0, %1 \n\t" ::"I"(_SFR_IO_ADDR(PORTC)), "I"(PORTC4));  // Set pin A4 low
}

// Function to calculate temperature from analog sensor
float temperature() {
  float temp = (float)analogRead(TEMPERATURE_SENSOR);
  return temp * 0.11366478;  // Convert sensor reading to degrees Celsius
}

// Function to calculate wind speed using time difference
double windspeed(int16_t timediff) {
  if (timediff == 0) {
    return 0.0;  // No wind if timediff is zero
  }
  double temperature = 20.0;  // Assume temperature is 20°C for testing
  double sos = 331.5 + (0.6 * temperature);  // Speed of sound in air
  double a = (double)timediff * -0.000000001;
  double b = 2 * DISTANCE;
  double c = a * pow(sos, 2);
  double discriminant = (b * b) - (4 * a * c);
  double wind = (-b + sqrt(discriminant)) / (2 * a);  // Solve quadratic equation
  return wind;
}

void loop() {
  if (done_flag) {
    digitalWrite(CALC, HIGH);  // Signal calculation in progress

    // Convert time-of-flight values to nanoseconds
    for (uint8_t dir = 0; dir < 6; ++dir) {
      envelope_tof_ns[dir] = envelope[calc_set][dir] * 125 >> 6;  // Envelope ToF
      zerocrossing_tof_ns[dir] = 0;
      uint32_t reference = envelope[calc_set][dir] >> 1;
      for (uint8_t i = 0; i < NUMBER_OF_ROUNDS; ++i) {
        while (zerocrossing[calc_set][dir][i] > reference)
          zerocrossing[calc_set][dir][i] -= 6400;
        zerocrossing_tof_ns[dir] += zerocrossing[calc_set][dir][i];
      }
      zerocrossing_tof_ns[dir] *= 125 >> 10;  // Convert zerocrossing ToF
    }

    // Calculate wind speeds for each axis
    int32_t diff_ns = zerocrossing_tof_ns[NORTH_TO_SOUTH] - zerocrossing_tof_ns[SOUTH_TO_NORTH];
    diff_ns = constrain(diff_ns, -12500, 12500);  // Constrain value to avoid wraparound
    float wind_ns = windspeed(diff_ns);

    int32_t diff_ew = zerocrossing_tof_ns[EAST_TO_WEST] - zerocrossing_tof_ns[WEST_TO_EAST];
    diff_ew = constrain(diff_ew, -12500, 12500);
    float wind_ew = windspeed(diff_ew);

    int32_t diff_tb = zerocrossing_tof_ns[TOP_TO_BOTTOM] - zerocrossing_tof_ns[BOTTOM_TO_TOP];
    diff_tb = constrain(diff_tb, -12500, 12500);
    float wind_tb = windspeed(diff_tb);

    // Accumulate wind speed measurements
    wind_ns_total += wind_ns;
    wind_ew_total += wind_ew;
    wind_tb_total += wind_tb;
    sample_count++;

    // After every 5 samples, calculate average and display results
    if (sample_count == 5) {
      float avg_wind_ns = wind_ns_total / 5;
      float avg_wind_ew = wind_ew_total / 5;
      float avg_wind_tb = wind_tb_total / 5;

      // Calculate total wind magnitude using all axes
      float magnitude = sqrt(avg_wind_ns * avg_wind_ns + avg_wind_ew * avg_wind_ew + avg_wind_tb * avg_wind_tb);

      // Calculate wind phase (horizontal direction)
      float phase = atan2(avg_wind_ns, avg_wind_ew) * (180.0 / PI);  // Convert radians to degrees
      if (phase < 0) {
        phase += 360.0;
      }
      phase = 90.0 - phase;  // Adjust phase to match wind direction convention
      if (phase < 0) {
        phase += 360.0;
      }

      // Calculate elevation angle (vertical direction)
      float horizontal_magnitude = sqrt(avg_wind_ns * avg_wind_ns + avg_wind_ew * avg_wind_ew);
      float elevation = atan2(avg_wind_tb, horizontal_magnitude) * (180.0 / PI);  // Elevation in degrees

      // Output results to serial for plotting
      Serial.print("NS:");
      Serial.print(avg_wind_ns, 2);
      Serial.print(",EW:");
      Serial.print(avg_wind_ew, 2);
      Serial.print(",TB:");
      Serial.print(avg_wind_tb, 2);
      Serial.print(",Mag:");
      Serial.print(magnitude, 2);
      Serial.print(",Phase:");
      Serial.print(phase, 2);
      Serial.print(",Elevation:");
      Serial.println(elevation, 2);

      // Reset totals and sample count
      wind_ns_total = 0;
      wind_ew_total = 0;
      wind_tb_total = 0;
      sample_count = 0;
    }

    done_flag = 0;  // Reset done flag
    digitalWrite(CALC, LOW);  // End calculation signal
  }
}
