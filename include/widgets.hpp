#pragma once

#include <memory>
#include <raylib.h>
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
		   Color pressed = GREEN);

	~Button() override = default;

	void Draw() override;

	private:
	bool state{false};
	Color base;
	Color hover;
	Color pressed;
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
