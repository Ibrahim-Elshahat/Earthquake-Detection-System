#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define BUZZER_PIN 12
#define LED_PIN 13
#define X_PIN A0
#define Y_PIN A1
#define Z_PIN A2

int xSample = 0;
int ySample = 0;
int zSample = 0;
long startTime;
int isAlerting = 0;

#define SAMPLES_COUNT 50
#define MAX_CHANGE_LIMIT 20
#define MIN_CHANGE_LIMIT -20
#define BUZZER_TIME 5000

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  delay(1000);
  displayMessage("Earthquake", "Detector");
  calibrateAccelerometer();
  displayMessage("Calibrated", "Device Ready");
}

void loop() {
  int xValue = analogRead(X_PIN);
  int yValue = analogRead(Y_PIN);
  int zValue = analogRead(Z_PIN);

  displayAccelerometerValues(xValue, yValue, zValue);

  if (isEarthquakeDetected(xValue, yValue, zValue)) {
    if (isAlerting == 0)
      startTime = millis();
    isAlerting = 1;
  } else if (isAlerting == 1) {
    lcd.clear();
    lcd.print("Earthquake Alert");
    if (millis() >= startTime + BUZZER_TIME)
      isAlerting = 0;
  } else {
    lcd.clear();
    lcd.print(" X Y Z ");
  }

  updateAlertComponents();
  sendValuesToProcessing(xValue, yValue, zValue);
}

void calibrateAccelerometer() {
  displayMessage("Calibrating.....", "Please wait...");
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  isAlerting = 0;
  digitalWrite(BUZZER_PIN, isAlerting);
  digitalWrite(LED_PIN, isAlerting);

  for (int i = 0; i < SAMPLES_COUNT; i++) {
    xSample += analogRead(X_PIN);
    ySample += analogRead(Y_PIN);
    zSample += analogRead(Z_PIN);
  }

  xSample /= SAMPLES_COUNT;
  ySample /= SAMPLES_COUNT;
  zSample /= SAMPLES_COUNT;

  delay(3000);
  lcd.clear();
  lcd.print("Calibrated");
  delay(1000);
  lcd.clear();
  lcd.print("Device Ready");
  delay(1000);
  lcd.clear();
  lcd.print(" X Y Z ");
}

void displayMessage(const char *line1, const char *line2) {
  lcd.clear();
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
  delay(2000);
  lcd.clear();
}

void displayAccelerometerValues(int x, int y, int z) {
  lcd.setCursor(0, 1);
  lcd.print(x);
  lcd.setCursor(6, 1);
  lcd.print(y);
  lcd.setCursor(12, 1);
  lcd.print(z);
  delay(100);
}

bool isEarthquakeDetected(int x, int y, int z) {
  return (
    x < MIN_CHANGE_LIMIT || x > MAX_CHANGE_LIMIT ||
    y < MIN_CHANGE_LIMIT || y > MAX_CHANGE_LIMIT ||
    z < MIN_CHANGE_LIMIT || z > MAX_CHANGE_LIMIT
  );
}

void updateAlertComponents() {
  digitalWrite(BUZZER_PIN, isAlerting);
  digitalWrite(LED_PIN, isAlerting);
}

void sendValuesToProcessing(int x, int y, int z) {
  Serial.print("x=");
  Serial.println(x);
  Serial.print("y=");
  Serial.println(y);
  Serial.print("z=");
  Serial.println(z);
  Serial.println(" $");
}