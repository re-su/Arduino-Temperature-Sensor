#include <LiquidCrystal.h>
#include "DHT.h"

#define DHT11_PIN 8

DHT dht;
// Create an LCD object. Parameters: (RS, E, D4, D5, D6, D7):
LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);
int i = 0;
const String TEXT = "Temperature";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(115200); 
  dht.setup(DHT11_PIN);
}

float roundHalf(float number){
    if(number - (int)number <= 0.25){
      number = (int)number;
    } else if(number - (int)number <= 0.75){
      number = (int)number + 0.5;
    } else {
      number = (int)number + 1;
    }

    return number;
}

void printToLCD(float temperature, float humidity){ // Wprowadza opoznienie
    lcd.clear();
    
    if(i + TEXT.length() > 16){
       lcd.setCursor(0, 0);
       lcd.print(TEXT.substring(16 - (i % 16)));
    }
    lcd.setCursor(i++ % 16, 0);
    lcd.print(TEXT);
    
    lcd.setCursor(2, 1);
    
    lcd.print(temperature);
    lcd.write(byte(0));
    lcd.print("C ");
    lcd.print(humidity);
    lcd.print("%");
    //Odczekanie wymaganego czasu
    delay(1000);  
}

void printToJson(float temperature, float humidity){
  Serial.print("{\"temperature\": ");
  Serial.print(temperature);
  Serial.print(",\"humidity\": ");
  Serial.print(humidity);
  Serial.print("}");
}

void loop() {
  //Pobranie informacji o wilgotnosci
  float humidity = dht.getHumidity();
  String humidity_status = dht.getStatusString();
  //Pobranie informacji o temperaturze
  float temperature = dht.getTemperature();
  String temperature_status = dht.getStatusString();
  
  if (humidity_status == "OK" && temperature_status  == "OK"){
    printToJson(temperature, humidity);
    //printToLCD(temperature, humidity);
  }
}


 
