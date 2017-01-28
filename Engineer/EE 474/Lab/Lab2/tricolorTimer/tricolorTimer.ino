// Create an IntervalTimer object 
IntervalTimer myTimer;

const int ledPin   = LED_BUILTIN;  // the pin with a LED
const int ledRed   = 20;
const int ledGreen = 21;
const int ledBlue  = 22;


void setup(void) {
  pinMode(ledPin, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  Serial.begin(9600);
  myTimer.begin(blinkLED, 1000000);  // blinkLED to run every 1 seconds
}

// The interrupt will blink the LED, and keep
// track of how many times it has blinked.
int ledRState = HIGH;
int ledGState = HIGH;
int ledBState = HIGH;
volatile unsigned long blinkCount = 0; // use volatile for shared variables

// functions called by IntervalTimer should be short, run as quickly as
// possible, and should avoid calling other functions if possible.
void blinkLED(void) {
  if (ledRState == LOW) {
    ledRState = HIGH;
    ledGState = LOW;
    ledBState = HIGH;
    blinkCount = blinkCount + 1;  // increase when LED turns on
  }
  else if (ledGState == LOW) {
    ledRState = HIGH;
    ledGState = HIGH;
    ledBState = LOW;
  }
  else {
    ledRState = LOW;
    ledGState = HIGH;
    ledBState = HIGH; 
  }
  digitalWrite(ledRed, ledRState);
  digitalWrite(ledGreen, ledGState);
  digitalWrite(ledBlue, ledBState);
}

// The main program will print the blink count
// to the Arduino Serial Monitor
void loop(void) {
  unsigned long blinkCopy;  // holds a copy of the blinkCount

  // to read a variable which the interrupt code writes, we
  // must temporarily disable interrupts, to be sure it will
  // not change while we are reading.  To minimize the time
  // with interrupts off, just quickly make a copy, and then
  // use the copy while allowing the interrupt to keep working.
  noInterrupts();
  blinkCopy = blinkCount;
  interrupts();

  Serial.print("blinkCount = ");
  Serial.println(blinkCopy);
  delay(100);
}
