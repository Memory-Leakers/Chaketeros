#include "Application.h"
#include "Globals.h"
#include "MemLeaks.h"

// Include SDL libraries
#include "SDL/include/SDL.h"	// Required for SDL base systems functionality

// Define libraries required by linker
// WARNING: Not all compilers support this option and it couples 
// source code with build system, it's recommended to keep both 
// separated, in case of multiple build configurations
//#pragma comment(lib, "SDL/lib/x86/SDL2.lib")
//#pragma comment(lib, "SDL/lib/x86/SDL2main.lib")

// Main application states
enum class MainState
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = nullptr;

int main(int argc, char* argv[])
{
	ReportMemoryLeaks();

	int main_result = EXIT_FAILURE;
	MainState state = MainState::MAIN_CREATION;

	while (state != MainState::MAIN_EXIT)
	{
		switch (state)
		{
			case MainState::MAIN_CREATION:
			{
				LOG("Application Creation --------------\n");
				App = new Application();
				state = MainState::MAIN_START;
			}	break;

			case MainState::MAIN_START:
			{
				LOG("Application Start --------------\n");
				if(App->Init() == false)
				{
					LOG("Application Init exits with error -----\n");
					state = MainState::MAIN_EXIT;
				}
				else
				{
					state = MainState::MAIN_UPDATE;
				}
			}	break;

			case MainState::MAIN_UPDATE:
			{
				UpdateResult status = App->Update();

				if (status == UpdateResult::UPDATE_ERROR)
				{
					LOG("Application Update exits with error -----\n");
					state = MainState::MAIN_EXIT;
				}
				else if (status == UpdateResult::UPDATE_STOP)
				{
					state = MainState::MAIN_FINISH;
				}
			}	break;

			case MainState::MAIN_FINISH:
			{
				LOG("Application Finish --------------\n");
				if (App->CleanUp() == true)
				{
					main_result = EXIT_SUCCESS;
				}
				else
				{
					LOG("Application CleanUp exits with error -----\n");
				}
				state = MainState::MAIN_EXIT;
			}
			default: break;
		}
	}

	LOG("\nBye :)\n");

	delete App;

	return main_result;
}