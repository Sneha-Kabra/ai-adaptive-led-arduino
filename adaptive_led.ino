// AI-based adaptive LED: linear regression model trained in train_model.py
const int LDR_PIN = A0;
const int LED_PIN = 9;       // PWM pin
const float W = -0.2648f;    // weights from train_model.py
const float B = 254.0f;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int ldr = analogRead(LDR_PIN);
  float pred = W * ldr + B;                 // model inference
  int pwm = constrain((int)pred, 0, 255);
  analogWrite(LED_PIN, pwm);
  Serial.print("LDR: "); Serial.print(ldr);
  Serial.print(" PWM: "); Serial.println(pwm);
  delay(100);
}
