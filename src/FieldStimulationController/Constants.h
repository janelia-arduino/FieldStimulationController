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
enum{PROPERTY_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=1};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]

// Parameters

// Functions

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
