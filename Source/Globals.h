#ifndef __GLOBALS_H__
#define __GLOBALS_H__

// Log macro for debug messages
#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

// Exit status values
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

// Update function result return values
enum class UpdateResult
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Useful typedefs
typedef unsigned int uint;

// Window Configuration
#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 224

#define SCREEN_SIZE 3
#define WIN_FULLSCREEN 0
#define WIN_FULLSCREEN_DESKTOP 0
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 0
#define VSYNC 1

#endif // __GLOBALS_H__