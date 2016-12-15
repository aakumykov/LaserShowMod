#include <Arduino.h>

class SerialListener
{
  public:
    SerialTrigger() {}

    void wait() {
      if (Serial.available() > 0) {
        byte piece = Serial.read();
        if (piece != ';') {
          this->tempString += String(char(piece));
        } else {
          this->inputData = this->tempString;
          this->tempString = "";
          this->dataRecieved = true;
        }
      }
    }

    boolean recieved() {
      return this->dataRecieved;
    }

    String data(){
      String d = this->inputData;
      this->clear();
      return d;
    }

    void clear() {
      this->dataRecieved = false;
      this->inputData = "";
    }

  private:
    // настраиваемые пользователем
    String delimiter = ";";
    unsigned long checkInterval = 200; //ms
    boolean echo = false;

    // служебные
    String tempString = "";
    boolean dataRecieved = false;
    String inputData = "";
};


