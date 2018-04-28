#pragma once
#include "Math/Vector2.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Entities/Elements/Element.h"

namespace OpenUI
{
	struct InputContext
	{		
		Element * ActiveElement = nullptr;
		Element * HighestElement = nullptr;
		IntVector MousePosition{0,0};
		sf::Event SfEvent;

		InputContext ();

		explicit InputContext ( sf::RenderWindow & p_renderWindow );

		void CheckMouseIntersection ( Element * p_element );

		void EndInput ();

		/// <summary>
		///		Pools the event to be used with input handling from a specified render window.
		/// </summary>
		/// <param name="p_renderWindow"></param>
		void PoolEvent(sf::RenderWindow & p_renderWindow);

	private:

		bool IsActiveElementChanged ();

		void ChangeActiveElement ();
		
		void HandleMouseStates ( bool p_wasActiveElementChanged ) const;
	};
}

