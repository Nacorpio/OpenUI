#pragma once
#include <SFML/Window/Mouse.hpp>
#include "Math/Vector2.h"
#include <SFML/Window/Event.hpp>

namespace OpenUI
{
	class InputInformation
	{
	public:
		static InputInformation* instance()
		{
			static InputInformation instance;
			return &instance;
		}

		bool MouseIsDown;
		IntVector MousePosition;
		sf::Mouse::Button LastActiveMouseButton;
		sf::Event::EventType LastEvent;
	};	
}
#define sInputInformation OpenUI::InputInformation::instance()