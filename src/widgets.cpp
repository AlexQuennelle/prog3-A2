#include "widgets.hpp"

#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>

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
	// Call the base version of the draw function to avoid repeated code
	Button::Draw();
	Vector2 textSize{
		MeasureTextEx(GetFontDefault(), this->text.c_str(), 30.0f, 0.0f)};
	// Center text within the button. Overflow is ignored
	Vector2 textPos{
		.x = this->position.x + (this->size.x / 2.0f) - (textSize.x / 2.0f),
		.y = this->position.y + (this->size.y / 2.0f) - (textSize.y / 2.0f),
	};
	DrawText(this->text.c_str(), static_cast<int>(textPos.x),
			 static_cast<int>(textPos.y), 30.0f, BLACK);
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
		// IsKeyPressed() triggers only on the first frame
		// IsKeyPressedRepeat() triggers repeatedly on a consistent delay, but
		// ignores the first cycle
		// Both are needed for the holding to feel correct
		if ((IsKeyPressed(KEY_BACKSPACE) ||
			 IsKeyPressedRepeat(KEY_BACKSPACE)) &&
			this->text.length() > 0)
		{
			this->text.pop_back();
		}
		else if (IsKeyPressed(KEY_ENTER) || IsKeyPressedRepeat(KEY_ENTER))
		{
			this->text.push_back('\n');
		}
		else
		{
			// This part is taken from the text box example raylib project
			// Loop through queued keys pressed this frame
			// GetCharPressed() returns 0 when the queue is empty
			while (key > 0)
			{
				if (key >= 32 && key <= 125)
				{
					this->text.push_back(static_cast<char>(key));
				}
				key = GetCharPressed();
			}
		}
		// Draw a cursor to indicate that typing is occurring
		DrawRectangleV(this->position + this->cursorPos, {3.0f, 30.0f}, GRAY);
	}
	this->ProcessText();
}
void TextInput::ProcessText()
{
	std::vector<std::string> lines{};
	static const int fontSize{30};
	std::string line;
	for (int i{0}; i < this->text.length(); i++)
	{
		if (this->text[i] == '\n')
		{
			lines.push_back(line);
			line = "";
			continue;
		}
		line.push_back(this->text[i]);
		if (MeasureText(line.c_str(), fontSize) + 2.0f >= this->size.x)
		{
			line.pop_back();
			lines.push_back(line);
			line = "";
			line.push_back(this->text[i]);
		}
	}
	lines.push_back(line);
	this->cursorPos = {
		.x = static_cast<float>(
				 MeasureText(lines[lines.size() - 1].c_str(), fontSize)) +
			 2.0f,
		.y = cursorPos.y,
	};
	int lineCount{
		(static_cast<int>(this->size.y) + 2) /
		static_cast<int>(MeasureTextEx(GetFontDefault(), " ", fontSize, 0).y)};
	if (lines.size() < lineCount)
	{
		for (int i{0}; i < lines.size(); i++)
		{
			DrawText(lines[i].c_str(), static_cast<int>(this->position.x) + 2,
					 static_cast<int>(this->position.y + (i * fontSize)),
					 fontSize, BLACK);
		}
		this->cursorPos = {
			.x = cursorPos.x,
			.y = (static_cast<float>(lines.size() - 1) * fontSize)};
	}
	else
	{
		for (int i{lineCount - 1}; i >= 0; i--)
		{
			int offset{static_cast<int>(lines.size() - lineCount)};
			DrawText(lines[i + offset].c_str(),
					 static_cast<int>(this->position.x) + 2,
					 static_cast<int>(this->position.y + (i * fontSize)),
					 fontSize, BLACK);
		}
		this->cursorPos = {.x = cursorPos.x,
						   .y = static_cast<float>((lineCount - 1) * fontSize)};
	}
}

WidgetProgram::WidgetProgram()
{
	this->widgets.push_back(std::make_unique<Button>(Button(
		{500.0f, 35.0f}, {150.0f, 50.0f}, {.r = 55, .g = 55, .b = 60, .a = 255},
		{.r = 80, .g = 80, .b = 100, .a = 255},
		{.r = 200, .g = 210, .b = 220, .a = 255})));

	this->widgets.push_back(std::make_unique<TextButton>(
		TextButton({50.0f, 25.0f}, {200.0f, 100.0f}, "test")));

	this->widgets.push_back(std::make_unique<TextInput>(
		TextInput({200.0f, 700.0f}, {400.0f, 62.0f})));
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
