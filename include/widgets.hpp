#pragma once

#include <memory>
#include <raylib.h>
#include <string>
#include <utility>
#include <vector>

namespace wig
{

using std::vector;

class WidgetBase
{
	public:
	WidgetBase(Vector2 pos, Vector2 size) : position(pos), size(size) {};

	virtual ~WidgetBase() = default;

	virtual void Draw() = 0;

	protected:
	Vector2 position;
	Vector2 size;
};
using Widget = std::unique_ptr<WidgetBase>;

class Button : public WidgetBase
{
	public:
	Button(Vector2 pos, Vector2 size, Color base = BROWN, Color hover = RED,
		   Color pressed = GREEN)
		: WidgetBase(pos, size), baseCol(base), hoverCol(hover),
		  pressedCol(pressed)
	{}

	~Button() override = default;

	void Draw() override;

	private:
	bool state{false};
	Color baseCol;
	Color hoverCol;
	Color pressedCol;
};
class TextButton : public Button
{
	public:
	TextButton(Vector2 pos, Vector2 size, std::string text, Color base = BROWN,
			   Color hover = RED, Color pressed = GREEN)
		: Button(pos, size, base, hover, pressed), text(std::move(text)) {};

	~TextButton() override = default;

	void Draw() override;

	private:
	std::string text;
};

class TextInput : public WidgetBase
{
	public:
	TextInput(Vector2 pos, Vector2 size,
			  std::string placeholder = "Input text Here")
		: WidgetBase(pos, size), placeHolderText(std::move(placeholder)) {};

	~TextInput() override = default;

	void Draw() override;

	private:
	bool focused{false};
	Vector2 cursorPos{};
	const std::string placeHolderText;
	std::string text;

	void ProcessText();
};

class WidgetProgram
{
	public:
	WidgetProgram();

	void Update();

	private:
	vector<Widget> widgets;
};

} //namespace wig
