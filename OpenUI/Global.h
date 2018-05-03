#pragma once
#include <SFML/Window/Event.hpp>
#include "Math/Vector2.h"

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

	static long ElapsedTime;
	static const uint16_t TicksPerSecond = 60;
	static const uint16_t SkipTicks = 1000 / TicksPerSecond;
	static const uint16_t MaxFrameSkips = 10;
}
#define sInputInformation OpenUI::InputInformation::instance()

