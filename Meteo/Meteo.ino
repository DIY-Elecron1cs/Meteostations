#include <IRremote.h>
#define BLUE 11
#define GREEN 10
#define RED 9
#include <iarduino_DHT.h>
iarduino_DHT sensor(2);

#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Подключение библиотеки
LiquidCrystal_I2C lcd(0x27, 16, 2);

IRrecv irrecv(6);
decode_results results;
bool flag1 = 0;
bool flag2 = 0;
bool flag3 = 0;
bool flag4 = 0;
bool flag5 = 0;
bool lcdlist = 0;

int DELAY = 100;
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args) write(args);
#else
#define printByte(args) print(args, BYTE);
#endif
unsigned long timer;
byte GRAD[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};


int VR = 0;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(A0, INPUT);

  lcd.init();
  lcd.backlight();
}
void loop() {
  if (irrecv.decode(& results)) {
    Serial.println(results.value);


    if (results.value == 16769565) {
      flag1 = !flag1;
      digitalWrite(RED, flag1);
      delay(DELAY);
    }
    if (results.value == 16761405) {
      flag2 = !flag2;
      digitalWrite(GREEN, flag2);
      delay(DELAY);
    }
    if (results.value == 16748655) {
      flag3 = !flag3;
      digitalWrite(BLUE, flag3);
      delay(DELAY);
    }
    if (results.value == 16736925) {
      flag4 = !flag4;
      if (flag4 == 1) {
        lcd.noBacklight();
      }
      if (flag4 == 0) {
        lcd.backlight();
      }
      delay(DELAY);
    }

    if (results.value == 16753245) {
      flag5 = !flag5;
      if (flag5 == 1) {
        lcdlist = 1;
        lcd.clear();
      }
      if (flag5 == 0) {
        lcdlist = 0;
        lcd.clear();
      }
      delay(DELAY);
    }

    irrecv.resume();
  }

  if (lcdlist == 1) {
    if (millis() - timer > 200) {
      timer  = millis();
      lcd.setCursor(12, 0);
      lcd.print("    ");
    }
    VR = analogRead(A0);

    lcd.setCursor(0, 0);
    lcd.print("h:");

    lcd.setCursor(3, 0);
    lcd.print(int (sensor.hum));

    lcd.setCursor(6, 0);
    lcd.print("%");

    lcd.setCursor(0, 1);
    lcd.print("t:");

    lcd.setCursor(3, 1);
    lcd.print(int (sensor.tem));

    lcd.createChar(1, GRAD);
    lcd.setCursor(6, 1);
    lcd.print("\1C");

    lcd.setCursor(9, 0);
    lcd.print("p:");

    lcd.setCursor(12, 0);
    lcd.print(VR);
    delay(3000);
  }

  Serial.print("сенсор в комнате: ");
  switch (sensor.read()) {
    case DHT_OK:               Serial.println((String) sensor.hum + "% - " + sensor.tem + "°C");   break;
    case DHT_ERROR_CHECKSUM:   Serial.println("не равенство кс");                                  break;
    case DHT_ERROR_DATA:       Serial.println("ответ не соответствует сенсорам 'DHT'");            break;
    case DHT_ERROR_NO_REPLY:   Serial.println("нет ответа");                                       break;
    default:                   Serial.println("ERROR");
  }

  if (lcdlist == 1) {
    lcd.clear();
  }
}
