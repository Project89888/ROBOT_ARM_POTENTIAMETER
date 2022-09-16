#include <Wire.h>
#include <Servo.h>
//initialize a servo object for the connected servo
Servo servo_test;
Servo servo_test2;
Servo servo_test3;
Servo servo_test4;
//SERVO variables for robotic ARM
int a =110;
int b=0;
int c=60;
int d=78;
// variable for arm moment according to color RED = 1 BLUE =2 GREEN=3, default =0
int colorVariable;
// RGB color sensor connected to Arduino
const int s0 = 2;
const int s1 = 4;
const int s2 = 7;
const int s3 = 8;
const int sout = 12;
// LED pins connected to Arduino
int redLed = 15;
int greenLed = 16;
int blueLed = 17;
// color Variables
int red = 0;
int green = 0;
int blue = 0;
// MOTOR mount connected to Arduino
int enB = 10;
int in3 = 11;
int in4 = 13;

void setup()
{
  Serial.begin(9600);
  servo_test.attach(3); // servo up/down
  servo_test2.attach(5); // servo cc/co
  servo_test3.attach(6); //servo front back
  servo_test4.attach(9); // sevo open /close
  
  // set all the motor control pins to outputs
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // set all the Sensor control pins to outputs
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sout, INPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  // set all the LED pins to outputs
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
}

void loop()
{
  
  armDefault();
  int sensorValue = analogRead(14); // IR detector pin 
  color();
  Serial.println(sensorValue); // print out the value you read:
  Serial.println(colorVariable); // print out the value you read:
  //temp();
  if (sensorValue<70 )
  {
    armDefault();
    //lcd.clear();
    delay(1000);
    motorS();
    arm();
    delay(500);
   }
   motorF();
   delay(500);
}

void armDefault()
{
  servo_test.write(a=110);
  servo_test2.write(b=0);
  servo_test3.write(c=60);
  servo_test4.write(d=78); //command to rotate the servo to the specified angle
}

void arm()
{
  up();delay(400);
  co();delay(400);
  ope();delay(400);
  front();delay(400);
  clos();delay(400);
  back();delay(400);
  cored();delay(400);// red
  down();delay(400);
  ope();delay(400);
  clos();delay(400);
  
  
  
  //up();delay(400);
  ccred();delay(400);//red
  cc();delay(400);
  switch (colorVariable)
  {
    case '1':
    up();delay(400);
    co();delay(400);
    ope();delay(400);
    front();delay(400);
    clos();delay(400);
    back();delay(400);
    cc();delay(400);
    down();delay(400);
    ope();delay(400);
    clos();delay(400);
    break;
    
    case '2':
    break;
    case '3':
    break;
    default:
    // turn all the connections off if an unmapped key is pressed:
    for (int thisPin = 2; thisPin < 11; thisPin++) {
      digitalWrite(thisPin, LOW);}
    }
}

void motorR()
{
  //Conveyor Reverse
  digitalWrite(in4, LOW); // turn on motor B
  digitalWrite(in3, HIGH);
  analogWrite(enB, 255); } // set speed to 200 out of possible range 0~255
  
void motorF()
{
  //Conveyor forward
  digitalWrite(in3, LOW); // turn on motor B
  digitalWrite(in4, HIGH);
  analogWrite(enB, 255); 
} // set speed to 200 out of possible range 0~255
    
void motorS()
{
  //Conveyor stop
  digitalWrite(in3, LOW); // now turn off motors
  digitalWrite(in4, LOW);
}

void up() 
{
  //ARM : UP
  for(a = 110; a < 175; a += 1)
  { // command to move from 0 degrees to 180 degrees
    servo_test.write(a); //command to rotate the servo to the specified angle
    delay(100); 
   }
}

void down()
{
  //ARM : DOWN
  for(a = 175; a>=110; a-=1) 
  { 
    // command to move from 180 degrees to 0 degrees
    servo_test.write(a); //command to rotate the servo to the specified angle
    delay(15); 
   }
}

void ope() 
{
  //ARM : OPEN
  for(d = 78; d>0; d-=1) 
  { // command to move from 180 degrees to 0 degrees
    servo_test4.write(d); //command to rotate the servo to the specified angle
    delay(100); 
    }
}

void clos() 
{
  //ARM : CLOSE
  for(d = 0; d < 78; d += 1) 
  { // command to move from 0 degrees to 180 degrees
    servo_test4.write(d); //command to rotate the servo to the specified angle
    delay(50); 
   }
}

void front() 
{
  //ARM : FRONT
  for(c = 60; c < 110; c += 1) 
  { // command to move from 0 degrees to 180 degrees
    servo_test3.write(c); //command to rotate the servo to the specified angle
    delay(90); 
   }
}

void back() 
{
  //ARM : BACK 
  for(c = 110; c > 60; c -= 1) 
  {
    servo_test3.write(c);
    delay(60); 
   }
}

void co() 
{
  //ARM : ROTATE
  for(b = 0; b < 75; b += 1) 
  { // command to move from 0 degrees to 180 degrees
    servo_test2.write(b); //command to rotate the servo to the specified angle
    delay(60); 
   }
}

void cc() 
{
  //ARM : ROTATE
  for(b = 75; b > 0; b -= 1) 
  { // command to move from 0 degrees to 180 degrees
    servo_test2.write(b); //command to rotate the servo to the specified angle
    delay(60); 
   }
}

void cored() 
{
  //ARM : ROTATE
  for(b = 75; b < 180; b += 1) 
  { // command to move from 0 degrees to 180 degrees
    servo_test2.write(b); //command to rotate the servo to the specified angle
    delay(60); 
  }
}

void ccred() 
{
  //ARM : ROTATE
  for(b = 180; b > 75; b -= 1) 
  { // command to move from 0 degrees to 180 degrees
    servo_test2.write(b); //command to rotate the servo to the specified angle
    delay(60); 
    }
}

void color()
{
  //OBJ COL =
  colorcal();
  if (red < blue && red < green && red < 20)
  {
    colorVariable = 1;
    //OBJ COL = RED
    digitalWrite(redLed, HIGH); // Turn RED LED ON
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, LOW);
  } 
  // variable for switch case = 1 if RED color detected
  else if (blue < red && blue < green) 
  {
    //OBJ COL = BLUE
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, HIGH); // Turn BLUE LED ON
    colorVariable = 2; 
  }// variable for switch case = 2 if BLUE color is detected
  else if (green < red && green < blue) 
  {
    //OBJ COL = GREEN
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH); // Turn GREEN LED ON
    digitalWrite(blueLed, LOW);
    colorVariable = 3; 
  } // variable for switch case =3 if GREEn color is detected
  else{
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, LOW);
    colorVariable = 0; 
    } // variable for switch case =0 for DEFAULT value
}
void colorcal()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  red = pulseIn(sout, digitalRead(sout) == HIGH ? LOW : HIGH); //count OUT, pRed, RED
  digitalWrite(s3, HIGH);
  blue = pulseIn(sout, digitalRead(sout) == HIGH ? LOW : HIGH); //count OUT, pBLUE, BLUE
  digitalWrite(s2, HIGH);
  green = pulseIn(sout, digitalRead(sout) == HIGH ? LOW : HIGH); //count OUT, pGreen, GREEN
}
