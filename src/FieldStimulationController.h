// ----------------------------------------------------------------------------
// FieldStimulationController.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef FIELD_STIMULATION_CONTROLLER_H
#define FIELD_STIMULATION_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <EventController.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <OpticalSwitchInterface.h>

#include "FieldStimulationController/Constants.h"


class FieldStimulationController : public OpticalSwitchInterface
{
public:
  FieldStimulationController();
  virtual void setup();

  void stimulationOn();
  void stimulationOff();
  void stimulationPwm(long delay,
    long period,
    long on_duration,
    long count);

private:
  modular_server::Property properties_[field_stimulation_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[field_stimulation_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[field_stimulation_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[field_stimulation_controller::constants::CALLBACK_COUNT_MAX];

  EventController<field_stimulation_controller::constants::EVENT_COUNT_MAX> event_controller_;
  EventIdPair pwm_event_id_pair_;

  // Handlers
  void stimulationOnEventHandler(int arg=-1);
  void stimulationOffEventHandler(int arg=-1);
  void stimulationOnHandler();
  void stimulationOffHandler();
  void stimulationPwmHandler();
  void stimulateHandler(modular_server::Pin * pin_ptr);

};

#endif
