#pragma once
#include <ostream>

namespace OpenUI
{
	enum class ElementType
	{
		Button,
		Label,
		ClientWindow,
		WindowHeader,
		WindowContainer,
	};

#define ElementType(type, name) case ElementType::##type: os << name; break

	inline std::ostream& operator<<(std::ostream& os, const ElementType& p_state)
	{
		switch (p_state)
		{
			ElementType(Button, "Button");
			ElementType(Label, "Label");
			ElementType(ClientWindow, "ClientWindow");
			ElementType(WindowHeader, "WindowHeader");
			ElementType(WindowContainer, "WindowContainer");
		default:;
		}

		return os;
	}

	enum class ColorType
	{
		BackgroundColor,
		ForegroundColor,
		OutlineColor
	};

	enum class GraphicType
	{
		Sprite,
		Text
	};

	enum class DockStyle
	{
		None,
		Left,
		Right,
		Top,
		Bottom,
		Filled
	};

	enum class MouseState
	{
		None,
		Entered,
		Moved,
		Hovered,
		Pressed,
		Released,
		Clicked
	};

#define State(type, name) case MouseState::##type: os << name; break

	inline std::ostream& operator<<(std::ostream& os, const MouseState& p_state)
	{
		switch (p_state)
		{
			State(None,"None");
			State(Entered, "Entered");
			State(Moved, "Moved");
			State(Hovered, "Hovered");
			State(Pressed, "Pressed");
			State(Released, "Released");
			State(Clicked, "Clicked");
			default: ;
		}

		return os;
	}
}