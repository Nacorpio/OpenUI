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

	class TimeInformation
	{
	public:
		static TimeInformation* instance()
		{
			static TimeInformation instance;
			return &instance;
		}

		long ElapsedTime;
		const uint16_t TicksPerSecond = 60;
		const uint16_t SkipTicks = 1000 / TicksPerSecond;
		const uint16_t MaxFrameSkips = 10;
	};
}
#define sInputInformation OpenUI::InputInformation::instance()
#define sTimeInformation OpenUI::TimeInformation::instance()


