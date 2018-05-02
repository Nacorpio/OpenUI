#include "stdafx.h"
#include "InputHandler.h"
#include "Entities/Elements/Element.h"

namespace OpenUI
{
	InputHandler::InputHandler()
	{
	}

	bool InputHandler::IsMouseWithin ( Element* element ) const
	{
		return IsMouseWithin ( element->GetBounds (), MousePosition );
	}

	void InputHandler::Refresh ( sf::Event::MouseMoveEvent& event )
	{
		MousePosition.X = event.x;
		MousePosition.Y = event.y;
	}

	void InputHandler::OnMouseEnter ( Element* element )
	{
		element->OnMouseEnter ();

		// TODO: Should the elements be able to send data to themselves?
		if ( m_dragDropSource )
		{
			m_dragDropTarget = element;
			element->OnDragEnter ( m_dragDropSource );
		}
	}

	void InputHandler::OnDragBegin ( Element* source )
	{
		source->OnDragBegin ();
	}

	void InputHandler::OnMouseLeave ( Element* element )
	{
		element->OnMouseLeave ();

		// The mouse is being held down outside of the element's borders.
		if ( element->IsBeingPressed () && !element->IsBeingDragged () )
		{
			m_dragDropSource = element;
			OnDragBegin ( element );
		}
	}

	void InputHandler::OnMouseDown ( Element* element, const sf::Event::MouseButtonEvent& event, const InputContext & p_inputContext)
	{
		element->OnMouseDown ( event );
	}

	void InputHandler::OnMouseMove ( Element* element )
	{
		const bool isMouseWithin = IsMouseWithin ( element );

		if ( isMouseWithin )
		{
			if ( !m_activeElement )
			{
				m_activeElement = element;
			}

			if ( element->GetHeight () > m_activeElement->GetHeight () )
			{
				m_activeElement->OnMouseLeave ();
				m_activeElement = element;
			}

			if ( element != m_activeElement )
			{
				return;
			}

			if ( element->IsCursorInside () )
			{
				if ( element == m_dragDropTarget )
				{
					element->OnDragMove ( m_dragDropSource );
				}

				element->OnMouseMove ();
				return;
			}

			OnMouseEnter ( element );
			return;
		}

		if ( element->IsCursorInside () )
		{
			m_activeElement = nullptr;
			OnMouseLeave ( element );
		}
	}

	void InputHandler::OnMouseUp ( Element* element, const sf::Event::MouseButtonEvent& event, const InputContext & p_inputContext)
	{
		if ( m_pressedElement == m_activeElement )
		{
			m_pressedElement = nullptr;
			element->OnMouseClick ( event );

			return;
		}

		element->OnMouseUp ( event );
	}

	void InputHandler::HandleElementEvent ( Element* element, const sf::Event& event, const InputContext & p_inputContext )
	{
		switch ( event.type )
		{
			case sf::Event::MouseMoved :
			{
				OnMouseMove ( element );
				break;
			}

			case sf::Event::MouseButtonPressed :
			{
				if ( !element->IsCursorInside () || element->IsBeingPressed())
				{
					return;
				}

				m_pressedElement = element;
				OnMouseDown ( element, event.mouseButton, p_inputContext);

				return;
			}

			case sf::Event::MouseButtonReleased :
			{
				if ( !element->IsBeingPressed () )
				{
					return;
				}

				if ( element->IsBeingDragged () && m_dragDropSource == element )
				{
					m_dragDropSource = nullptr;

					if ( !m_dragDropTarget )
					{
						return;
					}

					m_dragDropTarget->OnDrop ( MouseDropEvent ( *element ) );
				
					element->OnDragDrop ( MouseDragDropEvent ( *m_dragDropTarget ) );
					m_dragDropTarget = nullptr;
				}

				OnMouseUp ( element, event.mouseButton, p_inputContext );
				break;
			}

			default : ;
		}
	}

	template < typename _Ty >
	bool InputHandler::IsMouseWithin ( IntRect& rectangle, Vector2 <_Ty> point )
	{
		return rectangle.Contains ( point );
	}
}
