// motor A is left motor
#define SpeedPin_A 6
#define AIN1 8
#define SpeedPin_B 5
#define BIN1 7
#define Enable_motors 3

int PWM_A;
int PWM_B;

void setup() {
  Serial.begin(9600);
  pinMode(SpeedPin_A, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(SpeedPin_B, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(Enable_motors, OUTPUT);
}
bool done = 0;

void loop() {
  if (done == 1)
    return;
  go_forward(50);
  delay(3000);
  rotate_left(100);
  delay(600);//delay to get 90 degrees
  go_forward(100);
  delay(3000);
  rotate_right(100);
  delay(600);
  go_forward(70);
  delay(2000);
  stop();
  // delay(5000);
  done=1;
}


void stop() {
  digitalWrite(Enable_motors, LOW);  //turn off
}

void go_forward(int speed) {
  digitalWrite(Enable_motors, HIGH);  //turn on
  digitalWrite(AIN1, HIGH);           //motor A clockwise
  digitalWrite(BIN1, HIGH);           //moto B clockwise
  PWM_A = speed;
  PWM_B = speed;
  analogWrite(SpeedPin_A, PWM_A);
  analogWrite(SpeedPin_B, PWM_B);
}

void go_backward(int speed) {
  digitalWrite(Enable_motors, HIGH);  //turn on
  digitalWrite(AIN1, LOW);            //motor A clockwise
  digitalWrite(BIN1, LOW);            //moto B clockwise
  PWM_A = speed;
  PWM_B = speed;
  analogWrite(SpeedPin_A, PWM_A);
  analogWrite(SpeedPin_B, PWM_B);
}

void turn_left(int speed) {
  digitalWrite(Enable_motors, HIGH);  //turn on
  digitalWrite(AIN1, HIGH);           //motor A clockwise
  digitalWrite(BIN1, HIGH);           //moto B clockwise
  PWM_A = speed * 0.75;
  PWM_B = speed;
  analogWrite(SpeedPin_A, PWM_A);
  analogWrite(SpeedPin_B, PWM_B);
}

void turn_right(int speed) {
  digitalWrite(Enable_motors, HIGH);  //turn on
  digitalWrite(AIN1, HIGH);           //motor A clockwise
  digitalWrite(BIN1, HIGH);           //moto B clockwise
  PWM_A = speed;
  PWM_B = speed * 0.75;
  analogWrite(SpeedPin_A, PWM_A);
  analogWrite(SpeedPin_B, PWM_B);
}

void rotate_left(int speed) {
  digitalWrite(Enable_motors, HIGH);  //turn on
  digitalWrite(AIN1, LOW);            //motor A cclockwise
  digitalWrite(BIN1, HIGH);           //moto B clockwise
  PWM_A = speed;
  PWM_B = speed;
  analogWrite(SpeedPin_A, PWM_A);
  analogWrite(SpeedPin_B, PWM_B);
}

void rotate_right(int speed) {
  digitalWrite(Enable_motors, HIGH);  //turn on
  digitalWrite(AIN1, HIGH);           //motor A clockwise
  digitalWrite(BIN1, LOW);            //moto B cclockwise
  PWM_A = speed;
  PWM_B = speed;
  analogWrite(SpeedPin_A, PWM_A);
  analogWrite(SpeedPin_B, PWM_B);
}