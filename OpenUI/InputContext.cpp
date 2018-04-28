#include "stdafx.h"
#include "InputContext.h"

namespace OpenUI
{
	InputContext::InputContext ()
	{
	}

	InputContext::InputContext ( sf::RenderWindow & p_renderWindow )
	{
		PoolEvent ( p_renderWindow );
	}

	void InputContext::CheckMouseIntersection ( Element * p_element )
	{
		if (SfEvent.type != sf::Event::MouseMoved)
		{
			return;
		}

		if (p_element->GetBounds().Contains ( MousePosition ))
		{
			if (!HighestElement)
			{
				HighestElement = p_element;
				return;
			}

			if (p_element->GetHeight() > HighestElement->GetHeight())
			{
				HighestElement = p_element;
			}
		}
		else
		{
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

		if (IsActiveElementChanged())
		{
			HandleMouseStates ( true );
		}

		HandleMouseStates ( false );
		HighestElement = nullptr;
	}

	bool InputContext::IsActiveElementChanged ()
	{
		if (!ActiveElement)
		{
			ChangeActiveElement();
			return true;
		}

		if (ActiveElement->GetHeight() < HighestElement->GetHeight())
		{
			ChangeActiveElement();
			return true;
		}

		if (ActiveElement == HighestElement && !HighestElement->GetBounds().Contains ( MousePosition ))
		{
			ChangeActiveElement();
			return true;
		}

		if (!ActiveElement->GetBounds().Contains ( MousePosition ))
		{
			ChangeActiveElement();
			return true;
		}

		return false;
	}

	void InputContext::ChangeActiveElement ()
	{
		if (ActiveElement)
		{
			ActiveElement->OnMouseLeave();
		}

		ActiveElement = HighestElement;
	}

	void InputContext::PoolEvent ( sf::RenderWindow & p_renderWindow )
	{
		p_renderWindow.pollEvent ( SfEvent );
		MousePosition.X = SfEvent.mouseMove.x;
		MousePosition.Y = SfEvent.mouseMove.y;
	}

	void InputContext::HandleMouseStates ( bool p_wasActiveElementChanged ) const
	{
		if (p_wasActiveElementChanged)
		{
			ActiveElement->OnMouseEnter();
		}
		else
		{
			ActiveElement->OnMouseMove();
		}
	}
	
}
