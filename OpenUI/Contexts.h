#pragma once
#include "Math/Vector2.h"
#include <SFML/Window/Mouse.hpp>

namespace OpenUI
{
	struct InputContext
	{
		long Delta,ElapsedTime;
		IntVector MousePosition;
		sf::Mouse::Button MouseButtonPressed;
	};

	struct UpdateContext
	{
		long Delta, ElapsedTime;
		IntVector MousePosition;
		sf::Mouse::Button MouseButtonPressed;
	};
}

