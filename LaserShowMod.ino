#include "Laser.h"
#include "Drawing.h"
#include "Cube.h"
#include "Objects.h"
#include "Logo.h"

#include "SerialListener.cpp"
#include "Interval.cpp"
#include "CommandParser.cpp"

Laser laser(5);
SerialListener sListener;
Interval interval(1000);
CommandParser cmdParser;

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

//const unsigned short draw_boxes_array[] = {
//0x0,0x0,
//0x8000,0x3e8,
//0x83e8,0x3e8,
//0x83e8,0x0,
//0x8000,0x0,
//
//0xfa,0xfa,
//0x80fa,0x2ee,
//0x82ee,0x2ee,
//0x82ee,0xfa,
//0x80fa,0xfa,
//};

void setup()
{  
  laser.init();
  Serial.begin(9600);
  while(!Serial);

  Serial.println("= LaserShowMod2, setup complete =");
}

void drawBoxes(unsigned short data, int data_length)
{
  long centerX, centerY, w,h;
  Drawing::calcObjectBox(data, data_length/4, centerX, centerY, w, h);

  laser.setOffset(2048,2048);
  laser.setScale(4);
  
  for (int i = 0;i<1;i++) {
    Drawing::drawObjectArray(data_length, data_length/2, -centerX, -centerY);
  }
}


void loop() {
  sListener.wait();

  if (interval.ready()) {
    if (sListener.recieved()){
      String string_data = sListener.data();
      int data_length = string_data.length();
      
      Serial.print("string_data: ");
      Serial.print(string_data);
      Serial.println(" (" + String(data_length) + ")");

      char* char_data = new char[data_length+1];
      string_data.toCharArray(char_data, data_length+1);

      cmdParser.parse(char_data);

      char* command = cmdParser.command();
      int* data = cmdParser.data();
      int count = cmdParser.length();
      
      Serial.print("command: ");
      Serial.println(command);

      Serial.print("count: ");
      Serial.println(count);
      
      Serial.println("data: ");
      for (int i=0; i<count; i++) { Serial.println(data[i]); }

      unsigned short *data2 = new unsigned short;
      for (int i=0; i<count; i++) {
        data2[i] = (unsigned short)data[i];
      }

      drawBoxes(data2, count);
    }
  }
}

