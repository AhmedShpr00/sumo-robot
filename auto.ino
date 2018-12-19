 #define SW1 A0
#define SW2 A1
#define SW3 A2

#define RED_LED 30
#define BLUE_LED 31

byte motorSpeed = 255;
byte turn_motorSpeed = 80;

const int trigPin1 = A12;
const int echoPin1 = A13;
long duration1;
int distance1;

const int trigPin2 = A8;
const int echoPin2 = A9;
long duration2;
int distance2;

const int trigPin3 = A6;
const int echoPin3 = A7;
long duration3;
int distance3;


int lineStandard = 800;
long previousMillies = 0;
unsigned long  currentMillis;
int strategy = 0;

volatile boolean border = false ;

// back  ir sensors
int b_left_sen = 3  ;  
int b_right_sen = 3;
// front  ir sensors  
int f_right_sen = 20;
int f_left_sen = 21 ; 



void setup(){

  Serial3.begin(4800);
  Serial.begin(115200);
  pinMode(20, INPUT);
  pinMode(21, INPUT);
  pinMode( 2, INPUT);
  pinMode( 3, INPUT);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);


  pinMode(A5, OUTPUT);
  digitalWrite(A5, HIGH);


  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
    digitalWrite(trigPin1, LOW);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
    digitalWrite(trigPin2, LOW);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
    digitalWrite(trigPin3, LOW);
  
  delay (2);
}
float f_ultrasonic(){
    digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1*.0343)/2;

  Serial.println(distance1);
  delay(100);
  }
  float b_ultrasonic(){
    digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2*.0343)/2;
  Serial.println(distance2);
  delay(100);
  }
   float u_ultrasonic3(){
    digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = (duration3*.0343)/2;
  Serial.println(distance3);
  delay(100);
  }
void loop()
{
  
  b_ultrasonic();
  f_ultrasonic();
  u_ultrasonic();
  while (1)
  {
    if (Serial3.available())
    {
      if (Serial3.read() == 'F')
      {
        digitalWrite(RED_LED, HIGH);
        digitalWrite(BLUE_LED, LOW);
        delay(5000);
        digitalWrite(RED_LED, LOW);
        digitalWrite(BLUE_LED, HIGH);
        break;
      }
    }
  }

if (distance1 <= 50 || (distance2 <= 50 || distance3 <= 50  )){
  forward(); 
  
  }
else if(){
  rotat() ; 
  }
  if(digitalRead(f_right_sen) == HIGH )
  {
   back(); delay(1000);   left();
 
  }
 
  else if(digitalRead(f_left_sen) == HIGH )
  {
   back(); delay(1000);   right();
   
  }

  else if(analogRead(b_left_sen) > lineStandard)
  {
  forward(); delay(1000);   right();
  }
  else if(analogRead(b_right_sen) > lineStandard)
  {
  forward(); delay(1000);   left();
  }

  if((analogRead(b_left_sen)> lineStandard) && (analogRead(b_right_sen) > lineStandard)  )
  {
    
    forward ();
  }
  else if ((digitalRead(f_left_sen) == HIGH ) && (digitalRead(f_right_sen) == HIGH)  )
  {
    back();
  }
  delay(0);  // add a delay to decrease sensitivity.
}

void right() {
  digitalWrite(4, 0);
  analogWrite(5, turn_motorSpeed);
  digitalWrite(6, 1);
  analogWrite(7, turn_motorSpeed);

}
void Stop () {
  digitalWrite(4, 0);
  analogWrite(5, 0);
  digitalWrite(6, 0);
  analogWrite(7, 0);
}


void left() {
  digitalWrite(4, 1);
  analogWrite(5, turn_motorSpeed);
  digitalWrite(6, 0);
  analogWrite(7, turn_motorSpeed);

}
void forward() {
  digitalWrite(4, 0);
  analogWrite(5, motorSpeed);
  digitalWrite(6, 0);
  analogWrite(7, motorSpeed);

}
void back(){

digitalWrite(4, 1);
  analogWrite(5, motorSpeed);
  digitalWrite(6, 1);
  analogWrite(7, motorSpeed);

}
void rotat(){
  digitalWrite(4, 0);
  analogWrite(5,  turn_motorSpeed);
  digitalWrite(6, 1);
  analogWrite(7, turn_motorSpeed);

  }

