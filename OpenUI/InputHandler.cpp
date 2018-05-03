#include "stdafx.h"
#include "InputHandler.h"
#include "Entities/Elements/Element.h"
#include "MouseInformation.h"
#include <iostream>

namespace OpenUI
{
	InputHandler::InputHandler ()
	{
	}

	bool InputHandler::IsMouseWithin ( Element* element ) const
	{
		return IsMouseWithin ( element->GetBounds (), sInputInformation->MousePosition );
	}

	//void InputHandler::Refresh ( sf::Event::MouseMoveEvent& event )
	//{
	//	MousePosition.X = event.x;
	//	MousePosition.Y = event.y;
	//}

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
		if ( element->IsBeingDragged () && m_dragDropSource == element )
		{
			return;
		}

		element->OnMouseLeave ();

		// The mouse is being held down outside of the element's borders.
		if ( element->IsBeingPressed () )
		{
			m_dragDropSource = element;
			OnDragBegin ( element );
		}
	}

	void InputHandler::OnMouseDown ( Element* element)
	{
		element->OnMouseDown (  );
	}

	void InputHandler::OnMouseMove ( Element* element)
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
			OnMouseLeave ( m_activeElement );
			m_activeElement = element;
		}
	}

	void InputHandler::OnMouseMove ( Element* element )
	{
		const bool isMouseWithin = IsMouseWithin ( element );

		if ( isMouseWithin )
		{
			UpdateActiveElement ( element );

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

			if ( element->IsBeingDragged () )
			{
				element->AddState ( Entered );
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

	void InputHandler::OnMouseUp ( Element* element)
	{
		if ( m_pressedElement != m_activeElement )
		{
			m_pressedElement = nullptr;
			element->OnMouseUp ( event );
		}

		m_pressedElement = nullptr;
		++m_consecutiveClicks;

		if ( inputContext.ElapsedTime - m_lastMouseClick <= 200 )
		{
			++m_consecutiveClicks;
			m_lastMouseClick = inputContext.ElapsedTime;

			if ( m_consecutiveClicks == 2 )
			{
				element->OnMouseDoubleClick ( event );
			}

			return;
		}

		m_consecutiveClicks = 0;
		m_lastMouseClick = inputContext.ElapsedTime;

		element->OnMouseClick ( event );
	}

	void InputHandler::HandleElementEvent ( Element* element)
	{
		switch ( sInputInformation->LastEvent )
		{
			case sf::Event::MouseMoved :
			{
				OnMouseMove ( element );
				break;
			}

			case sf::Event::MouseButtonPressed :
			{
				if ( !element->IsCursorInside () || element->IsBeingPressed () )
				{
					return;
				}

				m_pressedElement = element;

				m_lastPressMousePos = MousePosition;
				m_lastMousePress = inputContext.ElapsedTime;

				OnMouseDown ( element, event.mouseButton, inputContext );
				OnMouseDown ( element);
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

					element->OnDragDrop ( MouseDragDropEvent ( m_dragDropTarget, m_lastPressMousePos, MousePosition ) );

					if ( m_dragDropTarget )
					{
						m_dragDropTarget->OnDrop ( MouseDropEvent ( *element, m_lastPressMousePos, MousePosition ) );
						m_dragDropTarget = nullptr;
					}
				}

				OnMouseUp ( element );
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
