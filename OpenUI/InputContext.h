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
		Element * PressedElement = nullptr;
		IntVector MousePosition{0,0};
		uint16_t ElementCount = 0;
		InputContext ();

		void CheckMouseContained ( Element * p_element );

		void EndInput ();

		/// <summary>
		///		Pools the event to be used with input handling from a specified render window.
		/// </summary>
		/// <param name="p_renderWindow"></param>
		void PollEvent(sf::RenderWindow * p_renderWindow);

	private:
		bool m_eventChanged = false;
		bool m_isMouseMoved = false;
		bool m_isMouseDown = false;
		bool m_isMouseReleased = false;
		bool m_isMouseDownOnHighestElement = false;
		bool m_isMouseDownOnActiveElement = false;
		sf::Event m_sfEvent;
		sf::Mouse::Button m_mouseButton;

		bool IsMouseContained ( IntRect & p_value );

		bool IsActiveElementChanged ();

		void ChangeActiveElement ();
		
		void HandleMouseStates ( bool p_wasActiveElementChanged );
	};
}

