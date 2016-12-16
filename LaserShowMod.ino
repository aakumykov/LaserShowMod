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

void drawBoxesArray()
{
  long centerX, centerY, w,h;
  Drawing::calcObjectBoxArray(draw_boxes_array, sizeof(draw_boxes_array)/4, centerX, centerY, w, h);

  laser.setOffset(2048,2048);
  laser.setScale(4);
  
  for (int i = 0;i<1;i++) {
    Drawing::drawObjectArray(draw_boxes_array, sizeof(draw_boxes_array)/2, -centerX, -centerY);
  }
}

void drawBoxesExternal(unsigned short data, int data_length)
{
  long centerX, centerY, w,h;
  Drawing::calcObjectBoxArray(draw_boxes, sizeof(draw_boxes)/4, centerX, centerY, w, h);

  laser.setOffset(2048,2048);
  laser.setScale(4);
  
  for (int i = 0;i<1;i++) {
    Drawing::drawObjectArray(draw_boxes, sizeof(draw_boxes)/2, -centerX, -centerY);
  }
}


void setup()
{  
  laser.init();
  Serial.begin(9600); while(!Serial);
  Serial.println("= LaserShowMod2 =");
}

void loop() {
  sListener.wait();

  if (interval.ready()) {
    if (sListener.recieved()){
//      Serial.print("data ("); Serial.print(count); Serial.print("): ");
//      for (int i=0; i<count; i++) { 
//        Serial.print(data[i]); Serial.print(",");
//      } Serial.println("");

      // внутренние данные (для сверки)
      Serial.println("------- draw_boxes_array -------");
      int a_length = sizeof(draw_boxes_array) / sizeof(unsigned short);
      for (int i=0; i<a_length; i++) {
        Serial.print(draw_boxes_array[i]); Serial.print(",");
      }
      Serial.println("");

      drawBoxesArray();


      // ==== с внешними данными ====
      
      // получение (пока кривое)
      String string_data = sListener.data();
      int data_length = string_data.length();
      char* char_data = new char[data_length+1];
      string_data.toCharArray(char_data, data_length+1);
      
      cmdParser.parse(char_data);
      int* data = cmdParser.data();
      int data_count = cmdParser.length();

      Serial.println("data:"); 
      for (int i=0; i < data_count; i++) {
        Serial.print(data[i]); Serial.print(",");
      }
      Serial.println(""); 
      
      // преобразование в unsigned short
      unsigned short *usData = new unsigned short;
      for (int i=0; i < data_count; i++) {
        usData[i] = (unsigned short)data[i];
      }

      Serial.println("usData:"); 
      for (int i=0; i < data_count; i++) {
        Serial.print(usData[i]); Serial.print(",");
      }
      Serial.println(""); 
      
      //drawBoxes(usData, count);
    }
  }
}



