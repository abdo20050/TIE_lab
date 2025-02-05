#define SpeedPin_1 5
#define AIN1 7
#define SpeedPin_2 6
#define BIN1 8
#define Enable_motors 3

int PWM_1;
int PWM_2;

void setup() {
  Serial.begin(9600);
  pinMode(SpeedPin_1,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(SpeedPin_2, OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(Enable_motors,OUTPUT);
}

void loop() {
  digitalWrite(Enable_motors, HIGH);//turn on
  digitalWrite(AIN1, HIGH);//motor A clockwise
  digitalWrite(BIN1, HIGH);//moto B clockwise
  PWM_1 = 50;
  PWM_2 = 50;
  analogWrite(SpeedPin_1, PWM_1);
  analogWrite(SpeedPin_2, PWM_2);
  delay(2000);
  digitalWrite(Enable_motors, LOW);
  delay(5000);
  digitalWrite(Enable_motors, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  PWM_1 = 50;
  PWM_2 = 50;
  analogWrite(SpeedPin_1, PWM_1);
  analogWrite(SpeedPin_2, PWM_2);
  delay(2000);
  digitalWrite(Enable_motors, LOW);
  delay(5000);
}


void Stop(){
  digitalWrite(Enable_motors, LOW);//turn off
}

void go_forward(int speed = 100){
  digitalWrite(Enable_motors, HIGH);//turn on
  digitalWrite(AIN1, HIGH);//motor A clockwise
  digitalWrite(BIN1, HIGH);//moto B clockwise
  PWM_1 = speed;
  PWM_2 = speed;
  analogWrite(SpeedPin_1, PWM_1);
  analogWrite(SpeedPin_2, PWM_2);
}

void go_backward(int speed = 100){
  digitalWrite(Enable_motors, HIGH);//turn on
  digitalWrite(AIN1, LOW);//motor A clockwise
  digitalWrite(BIN1, LOW);//moto B clockwise
  PWM_1 = speed;
  PWM_2 = speed;
  analogWrite(SpeedPin_1, PWM_1);
  analogWrite(SpeedPin_2, PWM_2);
}

void turn_left(int speed = 100){
  digitalWrite(Enable_motors, HIGH);//turn on
  digitalWrite(AIN1, HIGH);//motor A clockwise
  digitalWrite(BIN1, HIGH);//moto B clockwise
  PWM_1 = speed;
  PWM_2 = speed*0.75;
  analogWrite(SpeedPin_1, PWM_1);
  analogWrite(SpeedPin_2, PWM_2);
}

void turn_right(int speed = 100){
  digitalWrite(Enable_motors, HIGH);//turn on
  digitalWrite(AIN1, HIGH);//motor A clockwise
  digitalWrite(BIN1, HIGH);//moto B clockwise
  PWM_1 = speed*0.75;
  PWM_2 = speed;
  analogWrite(SpeedPin_1, PWM_1);
  analogWrite(SpeedPin_2, PWM_2);
}

void rotate_left(int speed = 100){
  digitalWrite(Enable_motors, HIGH);//turn on
  digitalWrite(AIN1, LOW);//motor A clockwise
  digitalWrite(BIN1, HIGH);//moto B clockwise
  PWM_1 = speed;
  PWM_2 = speed;
  analogWrite(SpeedPin_1, PWM_1);
  analogWrite(SpeedPin_2, PWM_2);
}

void rotate_right(int speed = 100){
  digitalWrite(Enable_motors, HIGH);//turn on
  digitalWrite(AIN1, HIGH);//motor A clockwise
  digitalWrite(BIN1, LOW);//moto B clockwise
  PWM_1 = speed;
  PWM_2 = speed;
  analogWrite(SpeedPin_1, PWM_1);
  analogWrite(SpeedPin_2, PWM_2);
}