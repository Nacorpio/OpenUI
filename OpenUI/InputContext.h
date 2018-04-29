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
		sf::Event SfEvent;
		sf::Mouse::Button MouseButton;
		bool EventChanged = false;
		bool IsMouseMoved = false;
		bool IsMouseDown = false;
		bool IsMouseReleased = false;
		bool IsMouseDownOnHighestElement = false;
		bool IsMouseDownOnActiveElement = false;

		InputContext ();

		void CheckMouseContained ( Element * p_element );

		void EndInput ();

		/// <summary>
		///		Pools the event to be used with input handling from a specified render window.
		/// </summary>
		/// <param name="p_renderWindow"></param>
		void PollEvent(sf::RenderWindow * p_renderWindow);

	private:
		uint16_t m_elementCount = 0;
		bool IsMouseContained ( IntRect & p_value );

		bool IsActiveElementChanged ();

		void ChangeActiveElement ();
		
		void HandleMouseStates ( bool p_wasActiveElementChanged );
	};
}

