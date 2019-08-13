// ----------------------------------------------------------------------------
// FieldStimulationController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef FIELD_STIMULATION_CONTROLLER_H
#define FIELD_STIMULATION_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <OpticalSwitchInterface.h>

#include "FieldStimulationController/Constants.h"


class FieldStimulationController : public OpticalSwitchInterface
{
public:
  FieldStimulationController();
  virtual void setup();

private:
  modular_server::Property properties_[field_stimulation_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[field_stimulation_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[field_stimulation_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[field_stimulation_controller::constants::CALLBACK_COUNT_MAX];

  // Handlers

};

#endif
