#include "widgets.hpp"

#include <memory>
#include <raylib.h>

namespace wig
{

Button::Button(Vector2 pos, Vector2 size, Color base, Color hover,
			   Color pressed)
	: iWidget(pos, size), base(base), hover(hover), pressed(pressed)
{}
void Button::Draw()
{
	auto mousePos{GetMousePosition()};
	bool mouseH{mousePos.x <= this->position.x + this->size.x &&
				mousePos.x >= this->position.x};
	bool mouseV{mousePos.y <= this->position.y + this->size.y &&
				mousePos.y >= this->position.y};

	if (mouseH && mouseV)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			state = !state;
	}
	if (this->state)
		DrawRectangleV(this->position, this->size, this->pressed);
	else
	{
		if (mouseH && mouseV)
			DrawRectangleV(this->position, this->size, this->hover);
		else
			DrawRectangleV(this->position, this->size, this->base);
	}
}

WidgetProgram::WidgetProgram()
{
	this->widgets.push_back(
		std::make_unique<Button>(Button({0.0f, 0.0f}, {200.0f, 150.0f})));
}
void WidgetProgram::Update()
{
	BeginDrawing();
	ClearBackground({100, 149, 237, 255});
	for (auto& wig : this->widgets)
	{
		wig->Draw();
	}
	EndDrawing();
}

} //namespace wig
