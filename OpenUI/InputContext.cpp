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
		++m_elementCount;

		if (IsMouseContained ( p_element->GetBounds() ))
		{
			if (!HighestElement)
			{
				IsMouseDownOnHighestElement = true;
				HighestElement = p_element;
				return;
			}

			if (p_element->GetHeight() > HighestElement->GetHeight())
			{
				IsMouseDownOnHighestElement = true;
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

			if (p_element == PressedElement && IsMouseReleased)
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
		IsMouseMoved = false;
		m_elementCount = 0;
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

		if (ActiveElement == HighestElement && !IsMouseDownOnHighestElement)
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
		EventChanged = p_renderWindow->pollEvent ( SfEvent );
		IsMouseMoved = SfEvent.type == sf::Event::MouseMoved && EventChanged;
		IsMouseDown = SfEvent.type == sf::Event::MouseButtonPressed && EventChanged;
		IsMouseReleased = SfEvent.type == sf::Event::MouseButtonReleased && EventChanged;

		if (IsMouseMoved)
		{
			MousePosition.X = SfEvent.mouseMove.x;
			MousePosition.Y = SfEvent.mouseMove.y;
		}

		if (IsMouseDown || IsMouseReleased)
		{
			MouseButton = SfEvent.mouseButton.button;
		}
	}

	bool InputContext::IsMouseContained ( IntRect & p_value )
	{
		return p_value.Contains ( MousePosition );
	}

	void InputContext::HandleMouseStates ( bool p_wasActiveElementChanged )
	{
		// Mouse is released on the active element and the pressed element is the same as active element. Call OnMouseClick.
		if (IsMouseReleased && ActiveElement == PressedElement)
		{
			PressedElement = nullptr;

			ActiveElement->OnMouseClick();
			LOG("OnMouseClick " << ActiveElement->GetName());
			return;
		}

		// Mouse is released on the active element and it's not the pressed element. Call OnMouseUp on the pressed element and OnMouseEnter on the active element.
		if (IsMouseReleased && PressedElement)
		{
			PressedElement->OnMouseUp();
			LOG("PressedElement OnMouseUp " << PressedElement->GetName());
			PressedElement = nullptr;

			ActiveElement->OnMouseEnter();
			LOG("OnMouseEnter " << ActiveElement->GetName());
			return;
		}

		if (IsMouseDown && !PressedElement)
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
