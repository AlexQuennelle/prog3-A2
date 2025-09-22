#include "widgets.hpp"

#include <csignal>
#include <iostream>
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
	Vector2 textSize{
		MeasureTextEx(GetFontDefault(), this->text.c_str(), 30.0f, 0.0f)};
	Vector2 textPos{
		.x = this->position.x + (this->size.x / 2.0f) - (textSize.x / 2.0f),
		.y = this->position.y + (this->size.y / 2.0f) - (textSize.y / 2.0f),
	};
	DrawText(this->text.c_str(), static_cast<int>(textPos.x),
			 static_cast<int>(textPos.y), 30, BLACK);
}

void TextInput::Draw()
{
	Vector2 mousePos{GetMousePosition()};
	bool mouseH{mousePos.x <= this->position.x + this->size.x &&
				mousePos.x >= this->position.x};
	bool mouseV{mousePos.y <= this->position.y + this->size.y &&
				mousePos.y >= this->position.y};
	if (mouseH && mouseV)
	{
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			focused = true;
		}
	}
	else
	{
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			focused = false;
		}
	}
	if (IsKeyPressed(KEY_ESCAPE))
		focused = false;

	DrawRectangleV(this->position, this->size, WHITE);
	if (!focused)
	{
		if (this->text == "")
		{
			DrawText(this->placeHolderText.c_str(),
					 static_cast<int>(this->position.x) + 2,
					 static_cast<int>(this->position.y), 30.0f, LIGHTGRAY);
			return;
		}
	}
	else
	{
		int key = GetCharPressed();
		while (key > 0)
		{
			if (static_cast<char>(key) == '\b')
			{
				this->text.pop_back();
			}
			else if (key >= 32 && key <= 125)
			{
				this->text.push_back(static_cast<char>(key));
			}
			key = GetCharPressed();
		}
	}
	DrawText(this->text.c_str(), static_cast<int>(this->position.x) + 2,
			 static_cast<int>(this->position.y), 30.0f, BLACK);
}

WidgetProgram::WidgetProgram()
{
	this->widgets.push_back(std::make_unique<TextButton>(
		TextButton({50.0f, 25.0f}, {200.0f, 100.0f}, "test")));
	this->widgets.push_back(std::make_unique<TextInput>(
		TextInput({100.0f, 300.0f}, {400.0f, 300.0f})));
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
