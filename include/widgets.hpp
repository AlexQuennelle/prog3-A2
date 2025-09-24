#pragma once

#include <memory>
#include <raylib.h>
#include <string>
#include <utility>
#include <vector>

namespace wig
{

using std::vector;

/**
 * Base widget class to inherit from. Provides some common properties and a
 * Draw() method to be overridden.
 */
class WidgetBase
{
	public:
	WidgetBase(Vector2 pos, Vector2 size) : position(pos), size(size) {};

	virtual ~WidgetBase() = default;

	/** Draws the widget to the canvas. */
	virtual void Draw() = 0;

	protected:
	Vector2 position;
	Vector2 size;
};
/** Alias for a pointer to WidgetBase for less typing and better readability. */
using Widget = std::unique_ptr<WidgetBase>;

/** Simple toggleable button widget. */
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
/** Toggleable button widget with a text label. */
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

/** Text input box widget. Input text wraps on horizontal overflow and scrolls
 * on vertical overflow. */
class TextInput : public WidgetBase
{
	public:
	TextInput(Vector2 pos, Vector2 size,
			  std::string placeholder = "Input text here")
		: WidgetBase(pos, size), placeHolderText(std::move(placeholder)) {};

	~TextInput() override = default;

	void Draw() override;

	private:
	bool focused{false};
	Vector2 cursorPos{};
	const std::string placeHolderText;
	std::string text;

	/**
	 * Processes and draws the stored text to the screen. This function handles
	 * wrapping and scrolling the text by splitting it on overflow and storing
	 * the new strings in a vector.
	 */
	void ProcessText();
};

/** Class that represents an instance of the widget demo program. */
class WidgetProgram
{
	public:
	WidgetProgram();

	/** The main program loop. */
	void Update();

	private:
	vector<Widget> widgets;
};

} //namespace wig
