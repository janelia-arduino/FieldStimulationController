// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace field_stimulation_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"field_stimulation_controller");

CONSTANT_STRING(firmware_name,"FieldStimulationController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=1,
  .version_minor=0,
  .version_patch=0,
};

const size_t stimulation_channel = 0;

// Pins

// Units
CONSTANT_STRING(ms_units,"ms");

// Properties
CONSTANT_STRING(stimulation_delay_property_name,"stimulationDelay");
const long stimulation_delay_default = 0;

CONSTANT_STRING(stimulation_period_property_name,"stimulationPeriod");
const long stimulation_period_default = 100;

CONSTANT_STRING(stimulation_on_duration_property_name,"stimulationOnDuration");
const long stimulation_on_duration_default = 50;

CONSTANT_STRING(stimulation_count_property_name,"stimulationCount");
const long stimulation_count_default = 4;

// Parameters
CONSTANT_STRING(delay_parameter_name,"delay");
const long delay_min = 0;
const long delay_max = 2000000000;

CONSTANT_STRING(period_parameter_name,"period");
const long period_min = 2;
const long period_max = 2000000000;

CONSTANT_STRING(on_duration_parameter_name,"on_duration");
const long on_duration_min = 1;
const long on_duration_max = 2000000000;

CONSTANT_STRING(count_parameter_name,"count");
const long count_min = 1;
const long count_max = 2000000000;

// Functions
CONSTANT_STRING(stimulation_on_function_name,"stimulationOn");
CONSTANT_STRING(stimulation_off_function_name,"stimulationOff");
CONSTANT_STRING(stimulation_pwm_function_name,"stimulationPwm");

// Callbacks
CONSTANT_STRING(stimulate_callback_name,"stimulate");

// Errors
}
}
