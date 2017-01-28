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
  myTimer.begin(blinkLED, 10000);  // blinkLED to run every 1 seconds
}

// The interrupt will blink the LED, and keep
// track of how many times it has blinked.
int ledRState = 255;
int ledGState = 255;
int ledBState = 255;

//track the current led state
// 1 for R up, 2 for R down
// 3 for G up, 4 for G down
// 5 for B up, 6 for B down
int ledState = 1;

volatile unsigned long blinkCount = 0; // use volatile for shared variables

// functions called by IntervalTimer should be short, run as quickly as
// possible, and should avoid calling other functions if possible.
void blinkLED(void) {
  if (ledState == 1) {
    ledRState--;
    if (ledRState == 0){
      ledState++;
    }
  }
  else if (ledState == 2) {
    ledRState++;
    if (ledRState == 255){
      ledState++ ;
    }
  }
  else if (ledState == 3) {
    ledGState--;
    if (ledGState == 0){
      ledState++ ;
    }
  }
  else if (ledState == 4) {
    ledGState++;
    if (ledGState == 255){
      ledState++ ;
    }
  }
  else if (ledState == 5) {
    ledBState--;
    if (ledBState == 0){
      ledState++ ;
    }
  }
  else {
    ledBState++;
    if (ledBState == 255){
      ledState = 1 ;
    } 
  }
  analogWrite(ledRed, ledRState);
  analogWrite(ledGreen, ledGState);
  analogWrite(ledBlue, ledBState);
}

int val;

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

  val = analogRead(2);
  
  Serial.print("blinkCount = ");
  Serial.println(blinkCopy);
  Serial.print("analog 2 is: ");
  Serial.println(val);
  delay(val);
  delay(val);
  delay(val);
}
