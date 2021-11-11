#include <PZEM004Tv30.h>
#include <Wire.h>
#include "rgb_lcd.h"
#define RELAY_PIN 4

/* https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight */
rgb_lcd lcd;
/*
const int colorR = 0;
const int colorG = 0;
const int colorB = 0;
*/

/* Hardware Serial3 is only available on certain boards.
 * For example the Arduino MEGA 2560
*/
PZEM004Tv30 pzem(&Serial3);

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(115200);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // randomSeed(analogRead(0));
  // lcd.setRGB( random(256), random(256), random(256));

  // Print a message to the LCD.
  lcd.print("Starting...");
  digitalWrite(RELAY_PIN, HIGH);

  delay(1000);
}

void loop() {
    float voltage = pzem.voltage();
    if(!isnan(voltage)){
        Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");
        lcd.setCursor(0, 0);
        lcd.print("Voltage: "+ String(voltage, 2) + "V");
    } else {
        Serial.println("Error reading voltage");
    }

    float current = pzem.current();
    if(!isnan(current)){
        Serial.print("Current: "); Serial.print(current); Serial.println("A");
        // (note: line 1 is the second row, since counting begins with 0)
        lcd.setCursor(0, 1);
        lcd.print("Current: "+ String(current, 4) + "A");
        if(current >=0.02){
          digitalWrite(RELAY_PIN, LOW);
          delay(100);
        }else{
          digitalWrite(RELAY_PIN, HIGH);
          delay(100);
        }
    } else {
        Serial.println("Error reading current");
    }

    float power = pzem.power();
    if(!isnan(power)){
        Serial.print("Power: "); Serial.print(power); Serial.println("W");
    } else {
        Serial.println("Error reading power");
    }

    float energy = pzem.energy();
    if(!isnan(energy)){
        Serial.print("Energy: "); Serial.print(energy,3); Serial.println("kWh");
    } else {
        Serial.println("Error reading energy");
    }

    float frequency = pzem.frequency();
    if(!isnan(frequency)){
        Serial.print("Frequency: "); Serial.print(frequency, 1); Serial.println("Hz");
    } else {
        Serial.println("Error reading frequency");
    }

    float pf = pzem.pf();
    if(!isnan(pf)){
        Serial.print("PF: "); Serial.println(pf);
    } else {
        Serial.println("Error reading power factor");
    }

    Serial.println();
    delay(2000);
}
