
// =====================================================
// TWO LED CONTROL USING SERIAL MONITOR
// Mode 1: LED1 Blinks, LED2 ON
// Mode 2: LED2 Blinks, LED1 ON
// Mode 3: LED1 ON, LED2 Breathing Effect
// =====================================================


// ----------- LED PIN DECLARATION -----------

const int LED1 = 10;  // LED1 is connected to digital pin 10
const int LED2 = 11;  // LED2 is connected to digital pin 11

int mode = 0;         // Initially, no mode is selected


// ----------- VARIABLES FOR BLINKING -----------

unsigned long previousMillis = 0; 
// Stores the time when the LED last changed its state

const unsigned long blinkInterval = 500; 
// LED changes its state every 500 milliseconds (0.5 seconds)

bool ledState = false; 
// false = LED OFF, true = LED ON


// ----------- VARIABLES FOR BREATHING EFFECT -----------

int brightness = 0;   
// Initial LED brightness is zero (OFF)

int brightnessAmount = 5;    
// Brightness increases or decreases by 5 each time

unsigned long previousBrightnessMillis = 0;
// Stores the time of the last brightness update

const unsigned long brightnessInterval = 20; 
// Brightness updates every 20 milliseconds


// =====================================================
// SETUP FUNCTION
// Executes only once when Arduino starts
// =====================================================

void setup() {

  pinMode(LED1, OUTPUT); 
  // Configure pin 10 as OUTPUT

  pinMode(LED2, OUTPUT); 
  // Configure pin 11 as OUTPUT

  Serial.begin(9600); 
  // Start serial communication at 9600 baud

  Serial.println("Enter 1, 2, or 3:");
  // Display instructions in Serial Monitor
}


// =====================================================
// LOOP FUNCTION
// Executes repeatedly
// =====================================================

void loop() {

  handleSerialInput();
  // Check whether a command is received from Serial Monitor

  updateMode();
  // Execute LED operations according to the selected mode
}


// =====================================================
// FUNCTION: HANDLE SERIAL INPUT
// Reads the user's command from Serial Monitor
// =====================================================

void handleSerialInput() {

  if (Serial.available() > 0) {
    // Check whether data is available to read

    char command = Serial.read();
    // Read one character from Serial Monitor

    if (command == '1') {

      mode = 1;
      // Select Mode 1

      Serial.println("Mode 1: LED1 blink, LED2 ON");
      // Display selected mode
    }

    else if (command == '2') {

      mode = 2;
      // Select Mode 2

      Serial.println("Mode 2: LED2 blink, LED1 ON");
      // Display selected mode
    }

    else if (command == '3') {

      mode = 3;
      // Select Mode 3

      Serial.println("Mode 3: LED1 ON, LED2 breathing");
      // Display selected mode
    }
  }
}


// =====================================================
// FUNCTION: UPDATE MODE
// Controls the LEDs according to the selected mode
// =====================================================

void updateMode() {

  unsigned long currentMillis = millis();
  // Get the time elapsed since Arduino started


  // ---------------- MODE 1 ----------------
  // LED1 BLINKS, LED2 REMAINS ON

  if (mode == 1) {

    digitalWrite(LED2, HIGH);
    // Keep LED2 continuously ON

    if (currentMillis - previousMillis >= blinkInterval) {
      // Check whether 500 milliseconds have passed

      previousMillis = currentMillis;
      // Update the previous time

      ledState = !ledState;
      // Toggle LED state: ON becomes OFF, OFF becomes ON

      digitalWrite(LED1, ledState);
      // Apply the new state to LED1
    }
  }


  // ---------------- MODE 2 ----------------
  // LED2 BLINKS, LED1 REMAINS ON

  else if (mode == 2) {

    digitalWrite(LED1, HIGH);
    // Keep LED1 continuously ON

    if (currentMillis - previousMillis >= blinkInterval) {
      // Check whether 500 milliseconds have passed

      previousMillis = currentMillis;
      // Update the previous time

      ledState = !ledState;
      // Toggle LED state

      digitalWrite(LED2, ledState);
      // Apply the new state to LED2
    }
  }


  // ---------------- MODE 3 ----------------
  // LED1 REMAINS ON, LED2 HAS BREATHING EFFECT

  else if (mode == 3) {

    digitalWrite(LED1, HIGH);
    // Keep LED1 continuously ON

    if (currentMillis - previousBrightnessMillis >= brightnessInterval) {
      // Check whether 20 milliseconds have passed

      previousBrightnessMillis = currentMillis;
      // Update the previous fading time

      analogWrite(LED2, brightness);
      // Control LED2 brightness using PWM

      brightness += brightnessAmount;
      // Increase or decrease brightness by 5

      if (brightness <= 0 || brightness >= 255) {
        // Check whether minimum or maximum brightness is reached

        brightnessAmount = -brightnessAmount;
        // Reverse the direction of brightness change
      }
    }
  }
}
