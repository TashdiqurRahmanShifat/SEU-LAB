// -------------------- PIN DECLARATIONS --------------------

// LED1 is connected to digital pin 10.
const int LED1 = 10;

// LED2 is connected to digital pin 11.
const int LED2 = 11;

// IN1 receives a digital signal from the first switch/button.
const int IN1 = 7;

// IN2 receives a digital signal from the second switch/button.
const int IN2 = 8;

// Stores the selected operating mode.
// 0 = both LEDs OFF, 1 = LED1 blinks and LED2 stays ON,
// 2 = LED1 stays ON and LED2 blinks, 3 = LED1 stays ON and LED2 breathes.
int mode = 0;


// -------------------- BLINK TIMING VARIABLES --------------------

// Stores the time when the blinking LED last changed its state.
unsigned long previousMillis = 0;

// The blinking LED changes state every 500 milliseconds (0.5 seconds).
const unsigned long blinkInterval = 500;

// Stores the blinking LED state: false = OFF, true = ON.
bool blinkState = false;


// -------------------- BREATHING TIMING VARIABLES --------------------

// Starting brightness of LED2. 0 means OFF.
int brightness = 0;

// Amount added to or subtracted from brightness at each update.
int brightnessAmount = 5;

// Stores the time when LED2 brightness was last updated.
unsigned long previousBrightnessMillis = 0;

// LED2 brightness is updated every 20 milliseconds.
const unsigned long brightnessInterval = 20;


// ============================================================
// setup()
// Runs once when the Arduino starts or resets.
// ============================================================

void setup() {

  // Configure pin 10 as an OUTPUT because it controls LED1.
  pinMode(LED1, OUTPUT);

  // Configure pin 11 as an OUTPUT because it controls LED2.
  pinMode(LED2, OUTPUT);

  // Configure pin 7 as an INPUT because it receives a signal.
  pinMode(IN1, INPUT);

  // Configure pin 8 as an INPUT because it receives a signal.
  pinMode(IN2, INPUT);
}


// ============================================================
// loop()
// Runs repeatedly while the Arduino is powered.
// ============================================================

void loop() {

  // Read the two input pins and decide which mode should run.
  readInputs();

  // Perform the LED operation for the selected mode.
  updateOutputs();
}


// ============================================================
// readInputs()
// Reads IN1 and IN2 and selects mode 0, 1, 2, or 3.
// ============================================================

void readInputs() {

  // Read the digital state of pin 7.
  // digitalRead() returns either HIGH or LOW.
  int val1 = digitalRead(IN1);

  // Read the digital state of pin 8.
  int val2 = digitalRead(IN2);

  // IN1 = LOW and IN2 = HIGH selects Mode 1.
  if (val1 == LOW && val2 == HIGH) {
    mode = 1;
  }

  // IN1 = HIGH and IN2 = LOW selects Mode 2.
  else if (val1 == HIGH && val2 == LOW) {
    mode = 2;
  }

  // Both inputs HIGH selects Mode 3.
  else if (val1 == HIGH && val2 == HIGH) {
    mode = 3;
  }

  // If neither of the above conditions is true,
  // both inputs are LOW, so select idle Mode 0.
  else {
    mode = 0;  // idle or undefined
  }
}


// ============================================================
// updateOutputs()
// Controls the LEDs according to the selected mode.
// ============================================================

void updateOutputs() {

  // millis() returns the number of milliseconds since the Arduino started.
  // It allows timing without pausing the program with delay().
  unsigned long currentMillis = millis();


  // -------------------- MODE 1 --------------------
  // IN1 = LOW, IN2 = HIGH
  // LED1 blinks; LED2 stays continuously ON.

  if (mode == 1) {

    // Keep LED2 ON.
    digitalWrite(LED2, HIGH);

    // Check whether at least 500 milliseconds have passed
    // since the previous blinking state change.
    if (currentMillis - previousMillis >= blinkInterval) {

      // Save the current time as the latest blink time.
      previousMillis = currentMillis;

      // Reverse blinkState: false becomes true, true becomes false.
      blinkState = !blinkState;

      // Turn LED1 ON or OFF according to blinkState.
      digitalWrite(LED1, blinkState);
    }
  }


  // -------------------- MODE 2 --------------------
  // IN1 = HIGH, IN2 = LOW
  // LED1 stays continuously ON; LED2 blinks.

  else if (mode == 2) {

    // Keep LED1 ON.
    digitalWrite(LED1, HIGH);

    // Check whether at least 500 milliseconds have passed.
    if (currentMillis - previousMillis >= blinkInterval) {

      // Save the current time as the latest blink time.
      previousMillis = currentMillis;

      // Reverse the blinking state.
      blinkState = !blinkState;

      // Turn LED2 ON or OFF according to blinkState.
      digitalWrite(LED2, blinkState);
    }
  }


  // -------------------- MODE 3 --------------------
  // IN1 = HIGH, IN2 = HIGH
  // LED1 stays continuously ON; LED2 has a breathing effect.

  else if (mode == 3) {

    // Keep LED1 ON.
    digitalWrite(LED1, HIGH);

    // Check whether 20 milliseconds have passed since
    // the previous brightness update.
    if (currentMillis - previousBrightnessMillis >= brightnessInterval) {

      // Save the current time as the latest brightness-update time.
      previousBrightnessMillis = currentMillis;

      // Set LED2 brightness using PWM.
      // On Arduino Uno: 0 = OFF and 255 = maximum PWM output.
      analogWrite(LED2, brightness);

      // Increase or decrease brightness by brightnessAmount.
      brightness += brightnessAmount;

      // If brightness reaches either limit, reverse its direction.
      // At the upper limit it starts decreasing; at the lower limit
      // it starts increasing again.
      if (brightness <= 0 || brightness >= 255) {
        brightnessAmount = -brightnessAmount;
      }
    }
  }


  // -------------------- MODE 0 --------------------
  // Both input pins are LOW.
  // Turn both LEDs OFF.

  else {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
}
