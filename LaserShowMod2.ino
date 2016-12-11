#include "Laser.h"
#include "Drawing.h"
#include "Cube.h"
#include "Objects.h"
#include "Logo.h"
#include "SerialTrigger.cpp"
#include "Interval.cpp"

Laser laser(5);
SerialTrigger trigger("start");
Interval interval(1000);

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

void setup()
{  
  laser.init();
  Serial.begin(9600);
  while(!Serial);

  Serial.println("LaserShowMod2, setup complete");
}

void drawBoxes()
{
  long centerX, centerY, w,h;
  Drawing::calcObjectBox(draw_boxes_array, sizeof(draw_boxes_array)/4, centerX, centerY, w, h);

  laser.setOffset(2048,2048);
  laser.setScale(4);
  
  for (int i = 0;i<20;i++) {
    Drawing::drawObject(draw_boxes, sizeof(draw_boxes)/4, -centerX, -centerY);
  }
}


void loop() {
  trigger.wait("start");

  if (trigger.triggered()) {
    Serial.println("LaserShowMod2, TRIGGERED");
    drawBoxes();
    delay(1000);
  }
}

