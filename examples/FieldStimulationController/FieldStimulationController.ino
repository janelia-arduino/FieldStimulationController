#include <FieldStimulationController.h>


FieldStimulationController dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
