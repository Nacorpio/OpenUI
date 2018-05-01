#pragma once
#include <ostream>
#include "Entities/Controls/Control.h"

namespace OpenUI
{
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

	#define State(type, name) case Control::ControlState::##type: os << name; break

	inline std::ostream& operator<< ( std::ostream& os, const Control::ControlState& p_state )
	{
		switch ( p_state )
		{
			State(None,"None");
			State(Entered, "Entered");
			State(Hovered, "Hovered");
			State(Pressed, "Pressed");
			State(Dragged, "Left");
			default : ;
		}
		return os;
	}
}
