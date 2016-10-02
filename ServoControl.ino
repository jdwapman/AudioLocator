
/*---------- DEFINING PINS ----------*/
#define SW01 31  // Left Switch, used for decrementing
#define SW02 17  // Right Switch, used for incrementing
#define SERVO_PIN 23  // defining Analog 7 pin to drive servo
#define RLED 30  // Red LED
#define GLED 39  // Green LED
#define BLED 40  // Blue LED

/*---------- DEFINING SERVO ----------*/
#include <Servo.h>  // where versio stuff is located
Servo myServo;      // creating a servo object to control a servo

/*---------- DEFINING CONSTANTS ----------*/
const int DEG_MAX = 180;  // max value of DEG
const int DEG_MIN = 0;    // min value of DEG

/*---------- DEFINING VARIABLES ----------*/
int DEG_value = 0;    // DEG value
int SW01_state = 0;
int SW02_state = 0;
char data[10];
int degree;
int currentValue = 90; //Set to middle
String inString;
String rString = "R";
String lString = "L";
String turnDirection;
int Rval = 0;  // for pwm, the values can be from 0 to 255
int Gval = 0;  // so starting lights at off state
int Bval = 0;
int PWM_value = 0;    // PWM value
int angle = 0;
int currentTime = 0;
int lastTime = 0;
int leftBlinks = 0;
int rightBlinks = 0;
int shouldBlink = 0;
int oldValue = 90;
int i = 0;



void setup()
{
  // pull up resistor defaults to logic 1, enabling pullup resistor
  pinMode(SW01, INPUT_PULLUP);
  pinMode(SW02, INPUT_PULLUP);

  // attaching servo to PD0
  myServo.attach(SERVO_PIN);

  // Starting Serial Communications and BAUD rate
  Serial.begin(9600);

  //reset Servo
  myServo.write(currentValue);

  //Initialize Blue, Green, and Red_LED pins as outputs.
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);

  //Turn off LEDs, turn on BLUE
  digitalWrite(RLED, LOW);
  digitalWrite(GLED, LOW);
  digitalWrite(BLED, HIGH);


}

void loop()
{

  if (Serial.available() > 0) //Get data
  {


    inString = Serial.readStringUntil(','); //Get angle to turn to

    currentValue = inString.toInt();
    currentValue = constrain(currentValue, 0, 180); //Constrain to 0 to 180 degrees

    //Next, get brightness values for each LED

    //Left intensity
    inString = Serial.readStringUntil(',');
    leftBlinks = inString.toInt();

    //Right intensity
    inString = Serial.readStringUntil(',');
    rightBlinks = inString.toInt();

    myServo.write(currentValue);

    //WRITE LEDS IF THERE IS A DIFFERENT ANGLE
    if (myServo.read() != oldValue)
    {
      //TURN OFF BLUE LED
      digitalWrite(BLED, LOW);

      //BLINK RED LED
      for (i = 1; i <= leftBlinks; ++i)
      {
        digitalWrite(RLED, HIGH);
        delay(200);
        digitalWrite(RLED, LOW);
        delay(200);

      }

      delay(300);

      //BLINK GREEN LED
      for (i = 1; i <= rightBlinks; ++i)
      {
        digitalWrite(GLED, HIGH);
        delay(200);
        digitalWrite(GLED, LOW);
        delay(200);

      }

      //TURN ON BLUE LED
      delay(500);
      digitalWrite(BLED, HIGH);
    }

    oldValue = currentValue; //Update the old value to have the current value
    
  }


  delay(15);

}

