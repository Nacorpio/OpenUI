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

	enum ControlState
	{
		None = 1 << 0,
		Entered = 1 << 1,
		Hovered = 1 << 2,
		Pressed = 1 << 3,
		Dragged = 1 << 4,
	};

	#define ENUM_OSTREAM_SWITCH(type, name) case type: os << name; break

	#define ENUM(name, ...) enum name \
	{ \
	__VA_ARGS__ \
	}

	#define ENUM_CLASS(name, ...) enum class name \
	{ \
	__VA_ARGS__ \
	}

	ENUM(Test, t1, t2, t3);

	inline std::ostream& operator<< ( std::ostream& os, const ElementType& value )
	{
		switch ( value )
		{
			ENUM_OSTREAM_SWITCH(ElementType::Button, "Button");
			ENUM_OSTREAM_SWITCH(ElementType::Label, "Label");
			ENUM_OSTREAM_SWITCH(ElementType::ClientWindow, "ClientWindow");
			ENUM_OSTREAM_SWITCH(ElementType::WindowHeader, "WindowHeader");
			ENUM_OSTREAM_SWITCH(ElementType::WindowContainer, "WindowContainer");

			default : ;
		}

		return os;
	}

	inline std::ostream& operator<< ( std::ostream& os, const ControlState& value )
	{
		switch ( value )
		{
			ENUM_OSTREAM_SWITCH(ControlState::None,"None");
			ENUM_OSTREAM_SWITCH(ControlState::Entered, "Entered");
			ENUM_OSTREAM_SWITCH(ControlState::Hovered, "Hovered");
			ENUM_OSTREAM_SWITCH(ControlState::Pressed, "Pressed");

			default : ;
		}

		return os;
	}

	#undef ENUM_OSTREAM_SWITCH
}
