#include "Laser.h"
#include "Drawing.h"
#include "Cube.h"
#include "Objects.h"
#include "Logo.h"

#include <SerialListener.h>
#include <Interval.h>
#include <CommandParser.h>

Laser laser(5);
SerialListener sListener(256, ';');
Interval interval(100);
CommandParser p(128, "|", ",", ':', 'Y');

const unsigned short draw_boxes[] PROGMEM = {
0x0,0x0,
0x8000,0x3e8,
0x83e8,0x3e8,
0x83e8,0x0,
0x8000,0x0,

//0xfa,0xfa,
//0x80fa,0x2ee,
//0x82ee,0x2ee,
//0x82ee,0xfa,
//0x80fa,0xfa,
};

const unsigned short draw_boxes_array[] = {
0x0,0x0,
0x8000,0x3e8,
0x83e8,0x3e8,
0x83e8,0x0,
0x8000,0x0,

//0xfa,0xfa,
//0x80fa,0x2ee,
//0x82ee,0x2ee,
//0x82ee,0xfa,
//0x80fa,0xfa,
};


void drawBoxes()
{
  Serial.println(F("drawBoxes()"));
  
  long centerX, centerY, w,h;
  Drawing::calcObjectBox(draw_boxes, sizeof(draw_boxes)/4, centerX, centerY, w, h);

  laser.setOffset(2048,2048);
  laser.setScale(4);
  
  for (int i=0; i<1; i++) {
    Drawing::drawObject(draw_boxes, sizeof(draw_boxes)/4, -centerX, -centerY);
  }

  Serial.println(F(""));
}

void drawBoxesArray()
{
  Serial.println(F("drawBoxesArray()"));
  
  long centerX, centerY, w,h;
  Drawing::calcObjectBoxArray(draw_boxes_array, sizeof(draw_boxes_array)/4, centerX, centerY, w, h);

  laser.setOffset(2048,2048);
  laser.setScale(4);
  
  for (int i=0; i<1; i++) {
    Drawing::drawObjectArray(draw_boxes_array, sizeof(draw_boxes_array)/2, -centerX, -centerY, false);
  }

  Serial.println(F(""));
}

void drawBoxesExternal(unsigned int* data, int data_length)
{
  Serial.println(F("drawBoxesExternal()"));
  
  long centerX, centerY, w,h;
  Drawing::calcObjectBoxArray(data, data_length/2, centerX, centerY, w, h);

  laser.setOffset(2048,2048);
  laser.setScale(4);
  
  for (int i=0; i<1; i++) {
    Drawing::drawObjectArray(data, data_length, -centerX, -centerY);
  }

  Serial.println(F(""));
}


void setup()
{  
  laser.init();
  Serial.begin(9600);
  Serial.println(F("= LaserShowMod ="));
}

void loop() {
  sListener.wait();

  if (interval.ready()) {
    
    if (sListener.isRecieved()){

    Serial.println(F(""));
    
    drawBoxes();
    
    drawBoxesArray();

      // ==== с внешними данными ====
      int len = sListener.length();
      char* externalData = sListener.data();
//
//      Serial.print(F("externalData length: "));
//      Serial.println(len);
//      
//      Serial.print(F("externalData: -->@"));
//      for (int i=0; i<len; i++) { Serial.print(externalData[i]); }
//      Serial.println(F("@<--"));

      p.parse(externalData);
      unsigned int* data = p.data();
      int data_len = p.length();

//      for (int i=0; i<data_len; i++) { Serial.println(externalData[i]); }

      Serial.print(F("parsed data length: "));
      Serial.println(data_len);

//      drawBoxesExternal(data, data_len);

      delay(1);
    }
  }
}

//1|N:0,0_Y:0,1000_Y:1000,1000_Y:1000,0_Y:0,0;

