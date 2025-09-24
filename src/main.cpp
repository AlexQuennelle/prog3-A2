#include "raylib.h"
#include "widgets.hpp"
#include <memory>
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

void Update();

// Pointer to the program instance
// This is necessary for WASM builds to work, because emscripten takes a
// function pointer to link to the javascript update loop
// This means the program loop needs to happen outside of main(), and the
// program instance needs to exist on the heap to be able to be ticked from
// there
// This pointer is initialized to nullptr to avoid any potential attempts to
// call raylib functions before InitWindow() is called
std::unique_ptr<wig::WidgetProgram> widgetProgram{nullptr};

int main()
{
	SetConfigFlags(FLAG_MSAA_4X_HINT);
#if defined(PLATFORM_WEB)
	InitWindow(800, 800, NAME);
	SetExitKey(KEY_NULL);
	widgetProgram = std::make_unique<wig::WidgetProgram>();
	emscripten_set_main_loop(Update, 0, 1);
#else
	InitWindow(800, 800, NAME);
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);
	widgetProgram = std::make_unique<wig::WidgetProgram>();
	while (!WindowShouldClose())
	{
		Update();
	}
#endif

	CloseWindow();

	return 0;
}

void Update() { widgetProgram->Update(); }
