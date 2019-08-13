// ----------------------------------------------------------------------------
// FieldStimulationController.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "../FieldStimulationController.h"


using namespace field_stimulation_controller;

FieldStimulationController::FieldStimulationController()
{
}

void FieldStimulationController::setup()
{
  // Parent Setup
  OpticalSwitchInterface::setup();

  // Reset Watchdog
  resetWatchdog();

  // Event Controller Setup
  event_controller_.setup();

  // Variable Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Pins
  modular_server::Pin & btn_a_pin = modular_server_.pin(modular_device_base::constants::btn_a_pin_name);

  modular_server::Pin & bnc_a_pin = modular_server_.pin(modular_device_base::constants::bnc_a_pin_name);

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & stimulation_delay_property = modular_server_.createProperty(constants::stimulation_delay_property_name,constants::stimulation_delay_default);
  stimulation_delay_property.setRange(constants::delay_min,constants::delay_max);
  stimulation_delay_property.setUnits(constants::ms_units);

  modular_server::Property & stimulation_period_property = modular_server_.createProperty(constants::stimulation_period_property_name,constants::stimulation_period_default);
  stimulation_period_property.setRange(constants::period_min,constants::period_max);
  stimulation_period_property.setUnits(constants::ms_units);

  modular_server::Property & stimulation_on_duration_property = modular_server_.createProperty(constants::stimulation_on_duration_property_name,constants::stimulation_on_duration_default);
  stimulation_on_duration_property.setRange(constants::on_duration_min,constants::on_duration_max);
  stimulation_on_duration_property.setUnits(constants::ms_units);

  modular_server::Property & stimulation_count_property = modular_server_.createProperty(constants::stimulation_count_property_name,constants::stimulation_count_default);
  stimulation_count_property.setRange(constants::count_min,constants::count_max);
  stimulation_count_property.setUnits(constants::ms_units);

  // Parameters
  modular_server::Parameter & delay_parameter = modular_server_.createParameter(constants::delay_parameter_name);
  delay_parameter.setRange(constants::delay_min,constants::delay_max);
  delay_parameter.setUnits(constants::ms_units);

  modular_server::Parameter & period_parameter = modular_server_.createParameter(constants::period_parameter_name);
  period_parameter.setRange(constants::period_min,constants::period_max);
  period_parameter.setUnits(constants::ms_units);

  modular_server::Parameter & on_duration_parameter = modular_server_.createParameter(constants::on_duration_parameter_name);
  on_duration_parameter.setRange(constants::on_duration_min,constants::on_duration_max);
  on_duration_parameter.setUnits(constants::ms_units);

  modular_server::Parameter & count_parameter = modular_server_.createParameter(constants::count_parameter_name);
  count_parameter.setRange(constants::count_min,constants::count_max);

  // Functions
  modular_server::Function & stimulation_on_function = modular_server_.createFunction(constants::stimulation_on_function_name);
  stimulation_on_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FieldStimulationController::stimulationOnHandler));

  modular_server::Function & stimulation_off_function = modular_server_.createFunction(constants::stimulation_off_function_name);
  stimulation_off_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FieldStimulationController::stimulationOffHandler));

  modular_server::Function & stimulation_pwm_function = modular_server_.createFunction(constants::stimulation_pwm_function_name);
  stimulation_pwm_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FieldStimulationController::stimulationPwmHandler));
  stimulation_pwm_function.addParameter(delay_parameter);
  stimulation_pwm_function.addParameter(period_parameter);
  stimulation_pwm_function.addParameter(on_duration_parameter);
  stimulation_pwm_function.addParameter(count_parameter);

  // Callbacks
  modular_server::Callback & output_0_callback = modular_server_.callback(optical_switch_interface::constants::output_0_callback_name);
  output_0_callback.detachFromAll();

  modular_server::Callback & output_1_callback = modular_server_.callback(optical_switch_interface::constants::output_1_callback_name);
  output_1_callback.detachFromAll();

  modular_server::Callback & output_2_callback = modular_server_.callback(optical_switch_interface::constants::output_2_callback_name);
  output_2_callback.detachFromAll();

  modular_server::Callback & output_3_callback = modular_server_.callback(optical_switch_interface::constants::output_3_callback_name);
  output_3_callback.detachFromAll();

  modular_server::Callback & stimulate_callback = modular_server_.createCallback(constants::stimulate_callback_name);
  stimulate_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FieldStimulationController::stimulateHandler));
  stimulate_callback.attachTo(btn_a_pin,modular_server::constants::pin_mode_interrupt_falling);
  stimulate_callback.attachTo(bnc_a_pin,modular_server::constants::pin_mode_interrupt_falling);

  stimulationOff();
  enableAllOutputs();
}

void FieldStimulationController::stimulationOn()
{
  event_controller_.remove(pwm_event_id_pair_);
  stimulationOnEventHandler();
}

void FieldStimulationController::stimulationOff()
{
  event_controller_.remove(pwm_event_id_pair_);
  stimulationOffEventHandler();
}

void FieldStimulationController::stimulationPwm(long delay,
  long period,
  long on_duration,
  long count)
{
  event_controller_.remove(pwm_event_id_pair_);
  if (event_controller_.eventsAvailable() < 2)
  {
    return;
  }
  pwm_event_id_pair_ = event_controller_.addPwmUsingDelay(
    makeFunctor((Functor1<int> *)0,*this,&FieldStimulationController::stimulationOnEventHandler),
    makeFunctor((Functor1<int> *)0,*this,&FieldStimulationController::stimulationOffEventHandler),
    delay,
    period,
    on_duration,
    count);
  event_controller_.enable(pwm_event_id_pair_);
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void FieldStimulationController::stimulationOnEventHandler(int arg)
{
  bool inverted;
  modular_server_.property(optical_switch_interface::constants::inverted_property_name).getElementValue(constants::stimulation_channel,inverted);

  if (!inverted)
  {
    digitalWrite(optical_switch_interface::constants::output_pins[constants::stimulation_channel],HIGH);
  }
  else
  {
    digitalWrite(optical_switch_interface::constants::output_pins[constants::stimulation_channel],LOW);
  }
}

void FieldStimulationController::stimulationOffEventHandler(int arg)
{
  bool inverted;
  modular_server_.property(optical_switch_interface::constants::inverted_property_name).getElementValue(constants::stimulation_channel,inverted);

  if (!inverted)
  {
    digitalWrite(optical_switch_interface::constants::output_pins[constants::stimulation_channel],LOW);
  }
  else
  {
    digitalWrite(optical_switch_interface::constants::output_pins[constants::stimulation_channel],HIGH);
  }
}

void FieldStimulationController::stimulationOnHandler()
{
  stimulationOn();
}

void FieldStimulationController::stimulationOffHandler()
{
  stimulationOff();
}

void FieldStimulationController::stimulationPwmHandler()
{
  long delay;
  modular_server_.parameter(constants::delay_parameter_name).getValue(delay);

  long period;
  modular_server_.parameter(constants::period_parameter_name).getValue(period);

  long on_duration;
  modular_server_.parameter(constants::on_duration_parameter_name).getValue(on_duration);

  long count;
  modular_server_.parameter(constants::count_parameter_name).getValue(count);

  stimulationPwm(delay,
    period,
    on_duration,
    count);
}

void FieldStimulationController::stimulateHandler(modular_server::Pin * pin_ptr)
{
  long delay;
  modular_server_.property(constants::stimulation_delay_property_name).getValue(delay);

  long period;
  modular_server_.property(constants::stimulation_period_property_name).getValue(period);

  long on_duration;
  modular_server_.property(constants::stimulation_on_duration_property_name).getValue(on_duration);

  long count;
  modular_server_.property(constants::stimulation_count_property_name).getValue(count);

  stimulationPwm(delay,
    period,
    on_duration,
    count);
}
