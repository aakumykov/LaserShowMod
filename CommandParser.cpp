#include <Arduino.h>

class CommandParser
{
  public:
    CommandParser(char* command_delimiter = ":", char* data_delimiter = ","){
      this->command_delimiter = command_delimiter;
      this->data_delimiter = data_delimiter;
    }
    
  void parse(char* inputData) {
    delete this->the_data;
    this->the_data = new int;
    
    this->the_command = strtok(inputData, this->command_delimiter);

    char* token;
    token = strtok(NULL, this->data_delimiter);
    while (token != NULL) {
      this->the_data[this->the_counter++] = atoi(token);
      token = strtok(NULL, this->data_delimiter);
    }
  }

  char* command(){
    return this->the_command;
  }

  int length() {
    return this->the_counter;
  }

  int* data() {
    return this->the_data;
  }

  private:
    char* command_delimiter;
    char* data_delimiter;

    char* the_command;
    int the_counter = 0;
    int* the_data;
};

