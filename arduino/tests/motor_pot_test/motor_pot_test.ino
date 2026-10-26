#define RPWM 5
#define LPWM 6
#define R_EN 7
#define L_EN 8
#define POT A7

void setup() {
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);

  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);

  Serial.begin(9600);
}

void loop() {
  int pot = analogRead(POT);  // 0–1023

  Serial.println(pot);

  // zona muerta al centro
  if (pot > 480 && pot < 540) {
    analogWrite(RPWM, 0);
    analogWrite(LPWM, 0);
  }

  // forward
  else if (pot >= 540) {
    int pwm = map(pot, 540, 1023, 120, 255);
    analogWrite(RPWM, pwm);
    analogWrite(LPWM, 0);
  }

  // reverse
  else {
    int pwm = map(pot, 0, 480, 255, 120);
    analogWrite(RPWM, 0);
    analogWrite(LPWM, pwm);
  }

  delay(20);
}
