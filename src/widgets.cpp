#include "widgets.hpp"

#include <memory>
#include <raylib.h>

namespace wig
{

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
		DrawRectangleV(this->position, this->size, this->pressedCol);
	else
	{
		if (mouseH && mouseV)
			DrawRectangleV(this->position, this->size, this->hoverCol);
		else
			DrawRectangleV(this->position, this->size, this->baseCol);
	}
}
void TextButton::Draw()
{
	Button::Draw();
	DrawText(this->text.c_str(), static_cast<int>(this->position.x),
			 static_cast<int>(this->position.y), 30, BLACK);
}

WidgetProgram::WidgetProgram()
{
	this->widgets.push_back(std::make_unique<TextButton>(
		TextButton({50.0f, 25.0f}, {200.0f, 100.0f}, "test")));
	//this->widgets.push_back(
	//	std::make_unique<Button>(Button({50.0f, 25.0f}, {200.0f, 100.0f})));
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
