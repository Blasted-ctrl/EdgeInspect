#include <ESP32Servo.h>

// Configs

// Types

enum class State
{
  Effective,
  Defective
};

struct Object
{
  State status;
  std::string name;
  boolean Effective;
};

void setup()
{

  Serial.begin(115200);  

}

void loop()
{

}

// put function definitions here:
