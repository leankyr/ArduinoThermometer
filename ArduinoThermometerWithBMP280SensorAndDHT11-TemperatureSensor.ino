#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
// The BMP280 sensor
#include <Adafruit_BMP280.h>

// define the pin to use:
#define DHTPIN 8

// sensor in use:
#define DHTTYPE    DHT11

// Using the sensor with I2C protocol
Adafruit_BMP280 bmp; // I2C


DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
// initialize the lcd screen object:
LiquidCrystal_I2C lcd(0x38, 2, 1, 0, 4, 5, 6, 7, 2, POSITIVE);  // Set the LCD I2C address
                    //addr, en, rw, rs, d4, d5, d6, d7, bl, blpol
                    /*
                      addr: address of the device(usually 0x20, 0x27, 0x38)
                      en: Switches on the output pings
                      rw:
                      rs:
                      d4: Data pins connected on the LCD
                      d5: >>
                      d6: >>
                      d7: >>
                      bl: index for backlight pin
                      blpol: Polarity of the backlight pin(different according to device used)
                    */


int temperature_row = 0;
int humidity_and_pressure_row = 1;

void setup()        
{
  Serial.begin(9600); // this the address I guess?

  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  
  // initialize devise
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  lcd.home();
  lcd.begin(16, 3); // lcd.begin(cols, rows)       
  ; // top left
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop()
{
  // set the Cursor
  lcd.setCursor(0, temperature_row);
  // Delay between measurements.
  delay(delayMS);

  // Get temperature event and print its value.
  //from the DHT sensor
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    lcd.print("Error!!!");
  }
  // Get temeperature from BMP SENSOR
  
  else {
    lcd.print("Temp ");
    lcd.setCursor(9, temperature_row);
    lcd.print(bmp.readTemperature());
    // DHT sensor temperature
    //lcd.print(event.temperature);
    lcd.setCursor(15, temperature_row);
    lcd.print("C");
  }
  
  // GET HUMIDITY //
 
    // set the Cursor
    int dis = 1;  
    switch (dis){
      case 1:    
        // Get humidity event and print its value.
        dht.humidity().getEvent(&event);
        if (isnan(event.relative_humidity)) {
          lcd.print("Error!!!");
        }
        else {
          lcd.setCursor(0, humidity_and_pressure_row);
          lcd.print("Humidity ");
          lcd.setCursor(9, humidity_and_pressure_row);
          lcd.print(event.relative_humidity);
          lcd.setCursor(14, humidity_and_pressure_row);
          lcd.print(" ");
          lcd.setCursor(15, humidity_and_pressure_row);
          lcd.print("%");
          
          delay(2000);
          //lcd.clear();
         }
      case 2:
        // Get Preassure
        lcd.setCursor(0, humidity_and_pressure_row); 
        lcd.print("Pressure ");
        lcd.setCursor(9, humidity_and_pressure_row);
        lcd.print(bmp.readPressure());
        lcd.setCursor(14, humidity_and_pressure_row);
        lcd.print("Pa");
        delay(2000);
        //lcd.clear();

      case 3:
      // Get Altitude
      lcd.setCursor(0, humidity_and_pressure_row); 
      lcd.print("Altitude ");
      lcd.setCursor(9, humidity_and_pressure_row);
      lcd.print(bmp.readAltitude(1013.25));
      lcd.setCursor(14, humidity_and_pressure_row);
      lcd.print(" m");
      delay(2000);
      }
}
