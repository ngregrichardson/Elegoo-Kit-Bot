#include <Arduino.h>
#include <Servo.h>
#include <IRremote.h>

/*
 * VARIABLES
 */

typedef enum FunctionMode
{
  IDLE,
  BLUETOOTH,
  IRREMOTE
} FunctionMode;

FunctionMode func_mode = IDLE;

/* DRIVE */
#define LEFT 5
#define RIGHT 6
#define LEFT_FORWARD 7
#define LEFT_BACKWARD 8
#define RIGHT_BACKWARD 9
#define RIGHT_FORWARD 11

/* SERVO */
Servo servo;

/* ULTRASONIC */
int ECHO = A4;
int TRIG = A5;

/* LINE FOLLOWER */
#define LF_RIGHT !digitalRead(10)
#define LF_MIDDLE !digitalRead(4)
#define LF_LEFT !digitalRead(2)

/* IR */
#define IR_PIN 12
#define VALUE 16738455
#define NULL_VALUE 1386468383
IRrecv ir(IR_PIN);
decode_results results;
unsigned long preMillis;
long unsigned int val;
String button;

/* BLUETOOTH */
String bt_button;

/*
 * FUNCTIONS
 */

void start()
{
  Serial.begin(9600);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_BACKWARD, OUTPUT);
  pinMode(RIGHT_BACKWARD, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  servo.attach(3);
  ir.enableIRIn();
}

String get_mode()
{
  switch (func_mode)
  {
  case 0:
    return (String) "IDLE";
    break;
  case 1:
    return (String) "BLUETOOTH";
    break;
  case 2:
    return (String) "IRREMOTE";
    break;
  default:
    return (String) "IDLE";
    break;
  }
}

/* DRIVE  */
void forward(int speed)
{
  analogWrite(LEFT, speed);
  analogWrite(RIGHT, speed);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
}

void backward(int speed)
{
  analogWrite(LEFT, speed);
  analogWrite(RIGHT, speed);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, LOW);
}

void turn_left(int speed)
{
  analogWrite(LEFT, speed);
  analogWrite(RIGHT, speed);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
}

void turn_right(int speed)
{
  analogWrite(LEFT, speed);
  analogWrite(RIGHT, speed);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, LOW);
}

void wide_left(int speed)
{
  analogWrite(LEFT, speed);
  analogWrite(RIGHT, speed);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
}

void wide_right(int speed)
{
  analogWrite(LEFT, speed);
  analogWrite(RIGHT, speed);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
}

void brake()
{
  analogWrite(LEFT, 0);
  analogWrite(RIGHT, 0);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
}

/* SERVO */
void setServo(int pos)
{
  servo.write(pos);
}

int getServo()
{
  return servo.read();
}

/* ULTRASONIC */
int getDistance()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  return (int)pulseIn(ECHO, HIGH) / 58;
}

/* LINE FOLLOWER */
bool getRight()
{
  return LF_RIGHT;
}
bool getMiddle()
{
  return LF_MIDDLE;
}

bool getLeft()
{
  return LF_LEFT;
}

/* IR */
String ir_pressed()
{
  return button;
}

void get_ir()
{
  if (ir.decode(&results))
  {
    preMillis = millis();
    func_mode = IRREMOTE;
    val = results.value;
    ir.resume();
    switch (val)
    {
    case 16736925:
      button = "FORWARD";
      break;
    case 16754775:
      button = "BACKWARD";
      break;
    case 16720605:
      button = "LEFT";
      break;
    case 16761405:
      button = "RIGHT";
      break;
    case 16712445:
      button = "OK";
      break;
    case 16738455:
      button = "ONE";
      break;
    case 16750695:
      button = "TWO";
      break;
    case 16756815:
      button = "THREE";
      break;
    case 16724175:
      button = "FOUR";
      break;
    case 16718055:
      button = "FIVE";
      break;
    case 16743045:
      button = "SIX";
      break;
    case 16716015:
      button = "SEVEN";
      break;
    case 16726215:
      button = "EIGHT";
      break;
    case 16734885:
      button = "NINE";
      break;
    case 16730805:
      button = "ZERO";
      break;
    case 16728765:
      button = "STAR";
      break;
    case 16732845:
      button = "POUND";
      break;
    default:
      break;
    }
  }
  else
  {
    if (millis() - preMillis > 200)
    {
      preMillis = millis();
    }
  }
}

/* BLUETOOTH */
void get_bt()
{
  if (Serial.available())
  {
    if (Serial.read() != -1)
    {
      func_mode = BLUETOOTH;
    }
    if (bt_button != Serial.readString())
    {
      bt_button = Serial.readString();
    }
  }
}

String bt_pressed()
{
  return bt_button;
}

void reload()
{
  get_ir();
  get_bt();
}

void wait(float seconds)
{
  delay(seconds * 1000);
}