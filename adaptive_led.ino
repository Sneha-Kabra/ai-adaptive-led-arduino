// AI-based adaptive LED: linear regression model trained in train_model.py
const int LDR_PIN = A0;
const int LED_PIN = 9;       // PWM pin
const float W = -0.2648f;    // weights from train_model.py
const float B = 254.0f;

const int N = 5;             // moving average window (fixes noisy readings)
int readings[N];
int idx = 0;
long total = 0;
unsigned long lastPrint = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  int first = analogRead(LDR_PIN);
  for (int i = 0; i < N; i++) { readings[i] = first; total += first; }
}

void loop() {
  total -= readings[idx];
  readings[idx] = analogRead(LDR_PIN);
  total += readings[idx];
  idx = (idx + 1) % N;
  float ldr = total / (float)N;             // filtered LDR value

  float pred = W * ldr + B;                 // model inference
  int pwm = constrain((int)pred, 0, 255);   // keep within valid PWM range
  analogWrite(LED_PIN, pwm);

  if (millis() - lastPrint >= 500) {        // print every 500 ms only
    lastPrint = millis();
    Serial.print("LDR: "); Serial.print(ldr);
    Serial.print(" PWM: "); Serial.println(pwm);
  }
  delay(20);
}
