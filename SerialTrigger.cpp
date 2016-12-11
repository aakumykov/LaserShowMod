#include <Arduino.h>

class SerialTrigger
{
  public:
    SerialTrigger(String triggerWord){
      this->triggerWord = triggerWord;
    }

    void echoON(){ this->echo = true; }
    void echoOFF(){ this->echo = false; }
    
    void wait(unsigned long checkInterval=200){
      if (Serial.available() > 0) {
          this->piece = Serial.read();
          if (this->piece != ';') {
            this->tempString += String(char(this->piece));
          } else {
            this->inputData = this->tempString;
            this->tempString = "";
            if (this->inputData == this->triggerWord) {
              this->isTriggered = true;
              this->inputData = "";
            } else {
              if (this->echo) Serial.println(this->inputData);
            }
          }
      }
    }
    
    boolean triggered(bool onlyOnce=true){
      boolean t = this->isTriggered;
      if (onlyOnce) this->clear();
      return t;
    }
    
    void clear(){
      this->isTriggered = false;
      this->inputData = "";
    }

    private:
      // настраиваемые пользователем
      String triggerWord;
      String delimiter = ";";
      unsigned long checkInterval = 200; //ms
      boolean echo = false;

      // служебные
      boolean isTriggered; // основное свойство
      byte piece;
      String tempString = "";
      String inputData = "";
      unsigned long lastCheck = 0;
};


