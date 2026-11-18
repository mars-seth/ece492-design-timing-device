
/*

  GPIO 22 HIGH = Run sequence
  GPIO 22 LOW  = LEDs OFF

  Physical LED pin order:
  GREEN - GND - BLUE - RED
  Binary sequence:
  RGB = 000 through 111
*/

// LED 1
const int LED1_G = 15;
const int LED1_B = 2;
const int LED1_R = 4;

// LED 2
const int LED2_G = 16;
const int LED2_B = 17;
const int LED2_R = 5;

// LED 3
const int LED3_G = 18;
const int LED3_B = 19;
const int LED3_R = 21;

// Digital input
const int INPUT_PIN = 22;


const bool COMMON_ANODE = false;

// SETUP

void setup() {

  pinMode(LED1_G, OUTPUT);
  pinMode(LED1_B, OUTPUT);
  pinMode(LED1_R, OUTPUT);

  pinMode(LED2_G, OUTPUT);
  pinMode(LED2_B, OUTPUT);
  pinMode(LED2_R, OUTPUT);

  pinMode(LED3_G, OUTPUT);
  pinMode(LED3_B, OUTPUT);
  pinMode(LED3_R, OUTPUT);

  // Configure GPIO 22 as digital input
  pinMode(INPUT_PIN, INPUT);

  // Start with all LEDs OFF
  setAllLEDs(0, 0, 0);
}


void loop() {

  // Check digital input
  if (digitalRead(INPUT_PIN) == HIGH) {

    //8 bit sequence
    for (int i = 0; i < 8; i++) {

      // Stop sequence if input goes LOW
      if (digitalRead(INPUT_PIN) == LOW) {
        break;
      }

      
      int red   = (i >> 2) & 1;
      int green = (i >> 1) & 1;
      int blue  = i & 1;

      // Update all three LEDs
      setAllLEDs(red, green, blue);

      delay(500);
    }

    // Turn all LEDs OFF
    setAllLEDs(0, 0, 0);

  }

  else {

    // Input LOW: keep LEDs OFF
    setAllLEDs(0, 0, 0);

  }

}


void setColor(int greenPin, int bluePin, int redPin, int red, int green, int blue) {

  digitalWrite(redPin,   COMMON_ANODE ? !red : red);
  digitalWrite(greenPin, COMMON_ANODE ? !green : green);
  digitalWrite(bluePin,  COMMON_ANODE ? !blue : blue);

}


void setAllLEDs(int red, int green, int blue) {

  setColor(LED1_G, LED1_B, LED1_R, red, green, blue);

  setColor(LED2_G, LED2_B, LED2_R, red, green, blue);

  setColor(LED3_G, LED3_B, LED3_R, red, green, blue);

}
