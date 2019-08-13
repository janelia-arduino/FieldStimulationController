// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef FIELD_STIMULATION_CONTROLLER_CONSTANTS_H
#define FIELD_STIMULATION_CONTROLLER_CONSTANTS_H
#include <ConstantVariable.h>
#include <OpticalSwitchInterface.h>


namespace field_stimulation_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=4};
enum{PARAMETER_COUNT_MAX=4};
enum{FUNCTION_COUNT_MAX=3};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern const size_t stimulation_channel;

// Pins

// Units
extern ConstantString ms_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString stimulation_delay_property_name;
extern const long stimulation_delay_default;

extern ConstantString stimulation_period_property_name;
extern const long stimulation_period_default;

extern ConstantString stimulation_on_duration_property_name;
extern const long stimulation_on_duration_default;

extern ConstantString stimulation_count_property_name;
extern const long stimulation_count_default;

// Parameters
extern ConstantString delay_parameter_name;
extern const long delay_min;
extern const long delay_max;

extern ConstantString period_parameter_name;
extern const long period_min;
extern const long period_max;

extern ConstantString on_duration_parameter_name;
extern const long on_duration_min;
extern const long on_duration_max;

extern ConstantString count_parameter_name;
extern const long count_min;
extern const long count_max;

// Functions
extern ConstantString stimulation_on_function_name;
extern ConstantString stimulation_off_function_name;
extern ConstantString stimulation_pwm_function_name;

// Callbacks
extern ConstantString stimulate_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
