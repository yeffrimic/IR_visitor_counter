#include <mqtt.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson/releases/tag/v5.0.7
#define sensor1 4
#define sensor2 5 
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

const int thresh = 0;
int PersonsCountedin;
int PersonsCountedout;

void draw(void) {
  String b = String(PersonsCountedout);
  char b2[4];
  String c = String(PersonsCountedin);
  char c2[4];
  b.toCharArray(b2, sizeof(b));
  c.toCharArray(c2, sizeof(c));
  // graphic commands to redraw the complete screen should be placed here
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 32, "entrada");
  u8g.drawStr( 80, 32, (const char*)(c2));
  u8g.drawStr( 0, 42, "salida");
  u8g.drawStr( 80, 42, (const char*)(b2));
}
//Definir pines de Software Serial.
void setup() {
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  digitalWrite(sensor1, LOW);
  digitalWrite(sensor2, LOW);
}

void loop() { 
  
int  sensA = !digitalRead(sensor1); // READ SENSOR A
int  sensB = !digitalRead(sensor2); // READ SENSOR B
//  Serial.println(sensA);
//  Serial.println(sensB);
  InorOut (sensA,sensB);
}

void InorOut (int sens1,int sens2) {
  if (sens1 <= thresh && sens2 > thresh) {
    PersonsCountedin = PersonsCountedin + 1; //  IN
    delay(100);
  }
  else {
  }
  if (sens1 > thresh && sens2 <= thresh) {
    PersonsCountedout = PersonsCountedout + 1; // OUT
    delay(100);
  }
  else {
  }
  u8g.firstPage();
  do {
    draw();

  } while ( u8g.nextPage() );
}
