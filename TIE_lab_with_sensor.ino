#define L A2
#define M A1
#define R A0

#define SpeedPin_A 6
#define AIN1 8
#define SpeedPin_B 5
#define BIN1 7
#define Enable_motors 3

int PWM_A;
int PWM_B;
float L_cur, M_cur, R_cur;
float L_prev, M_prev, R_prev;
int th_trig = 790;
int threashold_trig_m = th_trig, threashold_trig_l = th_trig, threashold_trig_r = th_trig;
bool sharpTurnLeft = false, sharpTurnRight = false;
int sharpTurnCheckInterval = 300;
int lastPrintTime = 0;
unsigned long sharpTurnStart = 0;
void setup() {
  Serial.begin(9600);
  pinMode(L, INPUT);
  pinMode(M, INPUT);
  pinMode(R, INPUT);
  Serial.println("start!");
  pinMode(SpeedPin_A, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(SpeedPin_B, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(Enable_motors, OUTPUT);
}
int done = 0;
void loop() {
  // delay(10);
  get_sensor_data();
  
  if (millis() - lastPrintTime >= 500) {
    lastPrintTime = millis();
    Serial.println("----------------------------");
    Serial.print("L: "); Serial.println(L_cur);
    Serial.print("M: "); Serial.println(M_cur);
    Serial.print("R: "); Serial.println(R_cur);
    Serial.println("----------------------------");
  }
  if (done){
    return;
  }
  else if (L_cur < threashold_trig_l && R_cur < threashold_trig_r && M_cur < threashold_trig_m && R_prev > threashold_trig_r){
    sharpTurnRight = true;
  }
  else if (L_cur < threashold_trig_l && R_cur < threashold_trig_r && M_cur < threashold_trig_m && L_prev > threashold_trig_l){
    sharpTurnLeft = true;
  }
  else if (L_cur > threashold_trig_l && R_cur > threashold_trig_r && M_cur > threashold_trig_m){
    stop();
    done = 1;
    return;
  }
  L_prev = L_cur;
  R_prev = R_cur;
  M_prev = M_cur;
  // delay(500);
  int speed = 70;
  // if (L_cur > threashold_trig && M_cur > threashold_trig) {
  //   if (sharpTurnStart == 0) sharpTurnStart = millis();
  //   if (millis() - sharpTurnStart >= 200) sharpTurnLeft = true;
  // } else if (R_cur > threashold_trig && M_cur > threashold_trig) {
  //   if (sharpTurnStart == 0) sharpTurnStart = millis();
  //   if (millis() - sharpTurnStart >= 200) sharpTurnRight = true;
  // }

  sharpTurnStart = 0;
  if (sharpTurnLeft) {
    go_forward(speed);
    unsigned long prev_mill = millis();
    while (millis() - prev_mill < 150){
      get_sensor_data();
      if(R_cur > threashold_trig_r){
        return;
        // break;
      }
    }    
    rotate_left(50);
    while (M_cur <= threashold_trig_m) {
      get_sensor_data();
      if (R_cur > threashold_trig_r){
        sharpTurnRight = true;
        break;
      }
    }
    sharpTurnLeft = false;
  } 
  else if (sharpTurnRight) {
    go_forward(speed);
    unsigned long prev_mill = millis();
    while (millis() - prev_mill < 150){
      get_sensor_data();
      if(L_cur > threashold_trig_l){
        return;
      }
    }
    // delay(150);
    rotate_right(50);
    while (M_cur <= threashold_trig_m && L_cur <= threashold_trig_l) {
      get_sensor_data();
      if (L_cur > threashold_trig_l){
        sharpTurnLeft = true;
        break;
      }
    }
    sharpTurnRight = false;
  }
  else if (L_cur > threashold_trig_l) {
    turn_left(speed);
    while (L_cur > threashold_trig_l) {
      // if (L_cur > threashold_trig_l && M_cur > threashold_trig_m) {
      //   if (sharpTurnStart == 0) sharpTurnStart = millis();
      //   if (millis() - sharpTurnStart >= sharpTurnCheckInterval){
      //     sharpTurnLeft = true;
      //     break;
      //   }
      // }
      get_sensor_data();
    }
  } 
  else if (R_cur > threashold_trig_r) {
    turn_right(speed);
    while (R_cur > threashold_trig_r) {
      // if (R_cur > threashold_trig_r && M_cur > threashold_trig_m) {
      //   if (sharpTurnStart == 0) sharpTurnStart = millis();
      //   if (millis() - sharpTurnStart >= sharpTurnCheckInterval){
      //     sharpTurnRight = true;
      //     break;
      //   }
      // }
      get_sensor_data();
    }
  } 
  else {
    go_forward(speed);
  }
}

void get_sensor_data(){
  float n_avg = 200;
  L_cur = 0;
  M_cur = 0;
  R_cur = 0;
  for(int i = 0; i < n_avg; i++){
    L_cur += float(analogRead(L)) / n_avg;
    M_cur += float(analogRead(M)) / n_avg;
    R_cur += float(analogRead(R)) / n_avg;
    // delay(1);
  }
}

void stop() {
  digitalWrite(Enable_motors, LOW);
}

void go_forward(int speed) {
  digitalWrite(Enable_motors, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  analogWrite(SpeedPin_A, speed);
  analogWrite(SpeedPin_B, speed);
}

void go_backward(int speed) {
  digitalWrite(Enable_motors, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  analogWrite(SpeedPin_A, speed);
  analogWrite(SpeedPin_B, speed);
}

void turn_left(int speed) {
  digitalWrite(Enable_motors, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  analogWrite(SpeedPin_A, speed * 0.5);
  analogWrite(SpeedPin_B, speed);
}

void turn_right(int speed) {
  digitalWrite(Enable_motors, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  analogWrite(SpeedPin_A, speed);
  analogWrite(SpeedPin_B, speed * 0.5);
}

void rotate_left(int speed) {
  digitalWrite(Enable_motors, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, HIGH);
  analogWrite(SpeedPin_A, speed);
  analogWrite(SpeedPin_B, speed);
}

void rotate_right(int speed) {
  digitalWrite(Enable_motors, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, LOW);
  analogWrite(SpeedPin_A, speed);
  analogWrite(SpeedPin_B, speed);
}

