#include <Wire.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>

MPU6050 mpu;
SoftwareSerial bluetooth(2, 3); // RX, TX

int buzzerPin = 9;

float offsetX = 0;
float offsetY = 0;

bool isWalking = false;
unsigned long walkStart = 0;
unsigned long totalWalkTime = 0;

int stepCount = 0;

void setup() {
  bluetooth.begin(9600);

  Wire.begin();
  mpu.initialize();
  pinMode(buzzerPin, OUTPUT);

  if (!mpu.testConnection()) {
    while (1); // لو الـ MPU مش شغال
  }

  delay(2000);
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  offsetX = atan2(ay, az) * 180 / PI;
  offsetY = atan2(ax, az) * 180 / PI;
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  float angleX = atan2(ay, az) * 180 / PI - offsetX;
  float angleY = atan2(ax, az) * 180 / PI - offsetY;
  float accelTotal = sqrt(ax * ax + ay * ay + az * az) / 16384.0;

  // الكشف عن المشي
  if (accelTotal > 1.2) {
    if (!isWalking) {
      isWalking = true;
      walkStart = millis(); // وقت بداية المشي
    }
    stepCount++; // كلما تم الكشف عن الحركة، نزيد عدد الخطوات
  } else {
    if (isWalking) {
      isWalking = false;
      totalWalkTime += millis() - walkStart; // حساب الوقت الكلي للمشي
    }
  }

  // قراءة مستوى الجهد (البطارية)
  float batteryVoltage = readBatteryVoltage();
  int batteryPercent = map(batteryVoltage, 3.5, 4.2, 0, 100); // افتراض أن البطارية بين 3.5 إلى 4.2 فولط

  // إرسال البيانات عبر البلوتوث
  if (!isWalking && totalWalkTime > 0) {
    unsigned long walkMinutes = totalWalkTime / 60000; // تحويل الوقت إلى دقائق
    bluetooth.print("Walk duration: ");
    bluetooth.print(walkMinutes);
    bluetooth.print(" minutes | Steps: ");
    bluetooth.print(stepCount);
    bluetooth.print(" | Battery: ");
    bluetooth.print(batteryPercent);
    bluetooth.println("%");
    
    // إعادة تعيين القيم بعد إرسال البيانات
    totalWalkTime = 0;
    stepCount = 0;
  }

  // تنبيه عند الانحناء غير الصحيح
  if (abs(angleX) > 15 || abs(angleY) > 15) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  delay(500);
}

// قراءة مستوى الجهد (البطارية)
float readBatteryVoltage() {
  int sensorValue = analogRead(A0);  // قراءة الجهد على المدخل A0
  float voltage = sensorValue * (5.0 / 1023.0); // تحويل القيمة إلى فولط
  return voltage;  // إرجاع الجهد
}