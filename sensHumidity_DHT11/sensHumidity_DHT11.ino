
/*****************************************************
 * name:Humiture Detection 
 * function:you can see the current value of humidity and temperature displayed on the I2C LCD1602.
 ******************************************************/
//Email:support@sunfounder.com
//Website:www.sunfounder.com

//include the libraries
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
//#include <string.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


#define DHTPIN 3     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);//Initialize DHT sensor.

void setup()
{
  Serial.begin(9600);//initialize the serial
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 

  dht.begin();
}

void loop()
{
  // READ DATA
  //Serial.println("DHT11:");
  
  // Wait a few seconds between measurements.
  delay(200);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  // LCD DISPLAY DATA
  lcd.setCursor(0, 0);
  lcd.print("Temp[C] Hum[%]");
  lcd.setCursor(0, 1);
  lcd.print(t,2); //print the temperature on lcd
  lcd.setCursor(8, 1);
  lcd.print(h,2);


  //SERIAL PRINT
//  Serial.print(F("Humidity: "));
  Serial.println(h);
//  Serial.print(F("%  Temperature: "));
  Serial.println(t);
//  Serial.print(F("°C "));
//  Serial.print(f);
//  Serial.print(F("°F  Heat index: "));
//  Serial.print(hic);
//  Serial.print(F("°C "));
//  Serial.print(hif);
//  Serial.println(F("°F"));
}
