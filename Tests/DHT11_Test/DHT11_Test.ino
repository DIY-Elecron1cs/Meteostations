#include <DHT11.h>
DHT11 dht11(4);

void setup(){
  Serial.begin(9600);
}
void loop(){
  int temperature = dht11.readTemperature();
  int humidity = dht11.readHumidity();

  if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT){
    Serial.print("температура: ");
    Serial.print(temperature);
    Serial.println(" °C");
  }
  else{
    Serial.println(DHT11::getErrorString(temperature));
  }
  if (humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT){
    Serial.print("влажность: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
  else{
    Serial.print(DHT11::getErrorString(humidity));
  }
  delay(1000);
}
