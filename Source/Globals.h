#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <windows.h>

// Log macro for debug messages
#define LOG(message) OutputDebugString(message)

// Exit status values
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

// Game configuration
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Update function result return values
enum class UpdateResult
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

#endif // __GLOBALS_H__