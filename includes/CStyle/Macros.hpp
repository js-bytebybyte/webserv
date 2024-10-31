#pragma once

/*
	Include the errorMessages used
	If you need to add a new message
	please add it in this file
*/
#include "ErrorMessages.hpp"

/*
	Include the Colors used for the output
	If you need to add a new color
	please add it in this file
*/
#include "Colors.hpp"

/*
	Include the Text MACROS used
	If you need to add a new enumeration
	please add it in this file
*/
#include "Keys.hpp"

/*
	Define all the macros for the project here
*/

#define MAX_FD 1000
#define MAX_BUF 18500000
#define MAX_S 4 // JST TODO: remove once config ok
#define DEFAULTERRORPAGE 404

#ifdef __linux__
# define DIRREAD __O_DIRECTORY
# define SMALL_BUF 80000
#elif defined(__APPLE__)
# define DIRREAD O_DIRECTORY
# define SMALL_BUF 80000
#endif