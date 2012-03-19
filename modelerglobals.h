#ifndef _MODELER_GLOBALS_H
#define _MODELER_GLOBALS_H

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif

// This is a list of the controls for the SampleModel
// We'll use these constants to access the values 
// of the controls from the user interface.
enum SampleModelControls
{ 
	XPOS, YPOS, ZPOS, 
	XSCALE,YSCALE,ZSCALE,
	HEAD_SIZE, HEAD_ROTATE, 
	HEIGHT,
	ARM_LENGTH, LEFT_ARM_ROTATE_X, LEFT_ARM_ROTATE_Y,
	RIGHT_ARM_ROTATE_X, RIGHT_ARM_ROTATE_Y,
	LEG_LENGTH, LEFT_LEG_ROTATE_X, LEFT_LEG_ROTATE_Y,
	RIGHT_LEG_ROTATE_X, RIGHT_LEG_ROTATE_Y,
	//TAIL_X, TAIL_Y,TAIL_LENGTH,
	FEET_SIZE,
	TORUS_R,
	TORUS_r,
	

	// add more here
	NUMCONTROLS
};

// Colors
#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f
#define COLOR_GRAY		0.8f, 0.8f, 0.8f

// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))
#define SETVAL(x, d) (ModelerApplication::Instance()->SetControlValue(x, d))
#define MAX(x) (ModelerApplication::Instance()->GetMaxValue(x))
#define MIN(x) (ModelerApplication::Instance()->GetMinValue(x))

#endif