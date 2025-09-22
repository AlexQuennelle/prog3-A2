#include "raylib.h"
#include "widgets.hpp"
#include <memory>

void Update();

std::unique_ptr<wig::WidgetProgram> widgetProgram{nullptr};

int main()
{
	SetConfigFlags(FLAG_MSAA_4X_HINT);
#if defined(PLATFORM_WEB)
	InitWindow(400, 400, NAME);
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

void Update()
{
	widgetProgram->Update();
}
