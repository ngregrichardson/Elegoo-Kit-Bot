#include <Arduino.h>

String IDLE = (String) "IDLE";
String BLUETOOTH = (String) "BLUETOOTH";
String IRREMOTE = (String) "IRREMOTE";

String FORWARD = (String) "FORWARD";
String BACKWARD = (String) "BACKWARD";
String LEFT = (String) "LEFT";
String RIGHT = (String) "RIGHT";
String OK = (String) "OK";
String ONE = (String) "ONE";
String TWO = (String) "TWO";
String THREE = (String) "THREE";
String FOUR = (String) "FOUR";
String FIVE = (String) "FIVE";
String SIX = (String) "SIX";
String SEVEN = (String) "SEVEN";
String EIGHT = (String) "EIGHT";
String NINE = (String) "NINE";
String ZERO = (String) "ZERO";
String STAR = (String) "STAR";
String POUND = (String) "POUND";

void start();
void reload();
String get_mode();
void wait(float seconds);

// Drive
void forward(int speed);
void backward(int speed);
void turn_left(int speed);
void turn_right(int speed);
void wide_left(int speed);
void wide_right(int speed);
void brake();

// Servo
void setServo(int pos);
int getServo();

// Ultrasonic
int getDistance();

// Line follower
bool getRight();
bool getMiddle();
bool getLeft();

// IR
String ir_pressed();

// Bluetooth
bool bt_pressed(String btn);