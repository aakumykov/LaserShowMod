#include "Laser.h"
#include "Drawing.h"
#include "Cube.h"
#include "Objects.h"
#include "Logo.h"

#include <SerialListener.h>
#include <Interval.h>
#include <CommandParser.h>

// 1|N:0,N:0,Y:0,Y:1000,Y:1000,Y:1000,Y:1000,Y:0,Y:0,Y:0;

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

0xfa,0xfa,
0x80fa,0x2ee,
0x82ee,0x2ee,
0x82ee,0xfa,
0x80fa,0xfa,
};

const unsigned short draw_boxes_array[] = {
0x0,0x0,
0x8000,0x3e8,
0x83e8,0x3e8,
0x83e8,0x0,
0x8000,0x0,

0xfa,0xfa,
0x80fa,0x2ee,
0x82ee,0x2ee,
0x82ee,0xfa,
0x80fa,0xfa,
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

//    Serial.println(F(""));
    drawBoxes();
//    
//    Serial.println(F(""));
//    drawBoxesArray();

      // ==== с внешними данными ====
      char* inputData = sListener.data();

//      p.parse(inputData);
//      unsigned int* data = p.data();
//      int data_len = p.length();
//
//      Serial.println(F(""));
//      drawBoxesExternal(data, data_len);

      delay(1);
    }
  }
}



