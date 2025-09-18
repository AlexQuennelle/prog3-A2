#pragma once

#include <memory>
#include <raylib.h>
#include <string>
#include <vector>

namespace wig
{

using std::vector;

class iWidget
{
	public:
	iWidget(Vector2 pos, Vector2 size) : position(pos), size(size) {};

	virtual ~iWidget() = default;

	virtual void Draw() = 0;

	protected:
	Vector2 position;
	Vector2 size;
};
using Widget = std::unique_ptr<iWidget>;

class Button : public iWidget
{
	public:
	Button(Vector2 pos, Vector2 size, Color base = BROWN, Color hover = RED,
		   Color pressed = GREEN)
		: iWidget(pos, size), baseCol(base), hoverCol(hover),
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
		: Button(pos, size, base, hover, pressed), text(text) {};

	~TextButton() override = default;

	void Draw() override;

	private:
	std::string text;
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
