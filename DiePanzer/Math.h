#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#ifndef M_PI
	#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.

#ifndef RAD2DEG
	#define RAD_TO_DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
	#define DEG_TO_RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif


