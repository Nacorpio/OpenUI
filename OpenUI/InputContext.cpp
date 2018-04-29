#include "stdafx.h"
#include "InputContext.h"
#include <iso646.h>
#include <iostream>
#include <cfenv>

namespace OpenUI
{
	InputContext::InputContext ()
	{
	}

	/// <summary>
	///		Checks if an element is contains the mouse cursor and compares it against the highest element.
	/// </summary>
	/// <param name="p_element">The element to be checked</param>
	void InputContext::CheckMouseContained ( Element * p_element )
	{
		++ElementCount;

		if (IsMouseContained ( p_element->GetBounds() ))
		{
			if (!HighestElement)
			{
				m_isMouseDownOnHighestElement = true;
				HighestElement = p_element;
				return;
			}

			if (p_element->GetHeight() > HighestElement->GetHeight())
			{
				m_isMouseDownOnHighestElement = true;
				HighestElement = p_element;
			}
		}
		else
		{
			if (ActiveElement == p_element && !PressedElement)
			{
				ActiveElement->OnMouseLeave();
				ActiveElement = nullptr;
			}

			if (p_element == PressedElement && m_isMouseReleased)
			{
				PressedElement->OnMouseUp();
				LOG("PressedElement - OnMouseUp");
				PressedElement = nullptr;
			}

			if (HighestElement == p_element)
			{
				HighestElement = nullptr;
			}
		}
	}

	void InputContext::EndInput ()
	{
		if (!HighestElement)
		{
			return;
		}

		HandleMouseStates ( IsActiveElementChanged() );

		HighestElement = nullptr;
		m_isMouseMoved = false;
		ElementCount = 0;
	}

	bool InputContext::IsActiveElementChanged ()
	{
		if (!ActiveElement)
		{
			ChangeActiveElement();
			return true;
		}

		if (ActiveElement == HighestElement)
		{
			return false;
		}

		if (ActiveElement->GetHeight() < HighestElement->GetHeight())
		{
			ChangeActiveElement();
			return true;
		}

		if (ActiveElement == HighestElement && !m_isMouseDownOnHighestElement)
		{
			ChangeActiveElement();
			return true;
		}

		if (!IsMouseContained ( ActiveElement->GetBounds() ))
		{
			ChangeActiveElement();
			return true;
		}

		return false;
	}

	void InputContext::ChangeActiveElement ()
	{
		if (ActiveElement && ActiveElement != PressedElement)
		{
			ActiveElement->OnMouseLeave();
		}

		ActiveElement = HighestElement;
	}

	void InputContext::PollEvent ( sf::RenderWindow * p_renderWindow )
	{
		m_eventChanged = p_renderWindow->pollEvent ( m_sfEvent );
		m_isMouseMoved = m_sfEvent.type == sf::Event::MouseMoved && m_eventChanged;
		m_isMouseDown = m_sfEvent.type == sf::Event::MouseButtonPressed && m_eventChanged;
		m_isMouseReleased = m_sfEvent.type == sf::Event::MouseButtonReleased && m_eventChanged;

		if (m_isMouseMoved)
		{
			MousePosition.X = m_sfEvent.mouseMove.x;
			MousePosition.Y = m_sfEvent.mouseMove.y;
		}

		if (m_isMouseDown || m_isMouseReleased)
		{
			m_mouseButton = m_sfEvent.mouseButton.button;
		}
	}

	bool InputContext::IsMouseContained ( IntRect & p_value )
	{
		return p_value.Contains ( MousePosition );
	}

	void InputContext::HandleMouseStates ( bool p_wasActiveElementChanged )
	{
		// Mouse is released on the active element and the pressed element is the same as active element. Call OnMouseClick.
		if (m_isMouseReleased && ActiveElement == PressedElement)
		{
			PressedElement = nullptr;

			ActiveElement->OnMouseClick();
			LOG("OnMouseClick " << ActiveElement->GetName());
			return;
		}

		// Mouse is released on the active element and it's not the pressed element. Call OnMouseUp on the pressed element and OnMouseEnter on the active element.
		if (m_isMouseReleased && PressedElement)
		{
			PressedElement->OnMouseUp();
			LOG("PressedElement OnMouseUp " << PressedElement->GetName());
			PressedElement = nullptr;

			ActiveElement->OnMouseEnter();
			LOG("OnMouseEnter " << ActiveElement->GetName());
			return;
		}

		if (m_isMouseDown && !PressedElement)
		{
			PressedElement = ActiveElement;
			ActiveElement->OnMouseDown();
			LOG("OnMouseDown " << ActiveElement->GetName());
			return;
		}

		if (!p_wasActiveElementChanged && !PressedElement)
		{
			ActiveElement->OnMouseMove();
			return;
		}

		if (p_wasActiveElementChanged && !PressedElement)
		{
			ActiveElement->OnMouseEnter();
			LOG("OnMouseEnter " << ActiveElement->GetName());
		}
	}
}
