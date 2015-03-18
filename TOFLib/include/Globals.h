#pragma once
/*******************************************************
*
*  Copyright (c) 2014 Texas Instruments Incorporated
*
*******************************************************/

#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdarg.h>
#include <stdio.h>

#ifdef PLAT_WINDOWS
typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int8 uint8_t;
#endif
#ifdef PLAT_LINUX
#include <stdint.h>
#endif

#ifdef PLAT_LINUX
#include <unistd.h>
#endif
#ifdef PLAT_WINDOWS
#include <Windows.h>
#endif

#define PRINT_LOGS false    //Indicates whether logMessage() prints are enabled or not

void sleepFunction(int milliSeconds);

void logMessage(const char *message, ...);

#endif // GLOBALS_H
