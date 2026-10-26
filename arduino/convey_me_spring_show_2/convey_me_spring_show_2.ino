// BTS7960 + Potenciómetro
// Control de velocidad y dirección

#define POT_PIN A0

#define RPWM 5
#define LPWM 6

int deadZone = 40;
int maxPWM = 180;

void setup() {

  Serial.begin(115200);

  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);

  // partir detenido
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
}

void loop() {

  // leer potenciometro
  int potValue = analogRead(POT_PIN);

  Serial.print("Pot: ");
  Serial.println(potValue);

  int pwm = 0;

  // centro = stop
  if (potValue > (512 - deadZone) && potValue < (512 + deadZone)) {

    analogWrite(RPWM, 0);
    analogWrite(LPWM, 0);
  }

  // izquierda = reverse
  else if (potValue < 512) {

    pwm = map(potValue, 0, 512 - deadZone, maxPWM, 0);

    analogWrite(RPWM, pwm);
    analogWrite(LPWM, 0);
  }

  // derecha = forward
  else {

    pwm = map(potValue, 512 + deadZone, 1023, 0, maxPWM);

    analogWrite(RPWM, 0);
    analogWrite(LPWM, pwm);
  }

  delay(20);
}
