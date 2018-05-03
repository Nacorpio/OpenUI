#include "stdafx.h"
#include "InputHandler.h"
#include "Entities/Elements/Element.h"
#include "Global.h"
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

	void InputHandler::OnMouseDown ( Element* element )
	{
		element->OnMouseDown ();
	}

	//void InputHandler::OnMouseMove ( Element* element)
	//{
	//	const bool isMouseWithin = IsMouseWithin ( element );

	//	if ( isMouseWithin )
	//	{
	//		if ( !m_activeElement )
	//		{
	//			m_activeElement = element;
	//		}

	//	if ( element->GetHeight () > m_activeElement->GetHeight () )
	//	{
	//		OnMouseLeave ( m_activeElement );
	//		m_activeElement = element;
	//	}
	//}

	void InputHandler::OnMouseMove ( Element* element )
	{
		const bool isMouseWithin = IsMouseWithin ( element );

		if ( isMouseWithin )
		{
			CalculateTopMost ( element );

			if ( element != m_top )
			{
				return;
			}

			m_lastMoved = element;
			m_lastMouseMoveTime = sTimeInformation->ElapsedTime;

			if ( element->IsCursorInside () )
			{
				if ( element == m_dragDropTarget )
				{
					element->OnDragMove ( m_dragDropSource );
				}

				if (!element->IsBeingHovered () && element == m_lastMoved)
				{
					LOG("HOVER");
					element->OnMouseHover();
					return;
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
			m_top = nullptr;
			OnMouseLeave ( element );
		}
	}

	void InputHandler::CalculateClick ( Element* element )
	{
		const bool isInTime = sTimeInformation->ElapsedTime - m_lastMouseClickTime <= 200;

		if ( !m_lastClicked || m_lastClicked != element || m_lastClicked == element && !isInTime )
		{
			m_consecutiveClicks = 1;
			return;
		}

		++m_consecutiveClicks;
	}

	void InputHandler::OnMouseUp ( Element* element )
	{
		// If it isn't the top-most element receiving the event, don't proceed.
		if (element != m_top)
		{
			return;
		}

		// If the mouse was released on another element, don't proceed.
		if ( element != m_pressing )
		{
			m_pressing->OnMouseUp();
			return;
		}

		// Make sure it's not another button being released.
		if (sInputInformation->LastActiveMouseButton != m_lastMousePress)
		{
			return;
		}

		CalculateClick ( element );

		switch ( m_consecutiveClicks )
		{
			case 1 :
			{
			single:
				element->OnMouseClick ();
				break;
			}

			case 2 :
			{
				element->OnMouseDoubleClick ();
				break;
			}

				/*case 3 :
				{
					LOG("TRIPLE CLICK!!!");
					break;
				}*/

			default :
			{
				m_consecutiveClicks = 1;
				goto single;
			}
		}

		m_pressing = nullptr;

		m_lastClicked = element;
		m_lastMouseClickTime = sTimeInformation->ElapsedTime;
		m_lastMouseClickPos = sInputInformation->MousePosition;
		m_lastMouseClick = sInputInformation->LastActiveMouseButton;
	}

	void InputHandler::HandleInput ( Element* element )
	{
		const IntVector mousePos = sInputInformation->MousePosition;

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

				if (element != m_top)
				{
					return;
				}

				m_pressing = element;

				m_lastMousePressPos = mousePos;
				m_lastMousePressTime = sTimeInformation->ElapsedTime;
				m_lastMousePress = sInputInformation->LastActiveMouseButton;

				OnMouseDown ( element );
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

					element->OnDragDrop ( MouseDragDropEvent ( m_dragDropTarget, m_lastMousePressPos, mousePos ) );

					if ( m_dragDropTarget )
					{
						m_dragDropTarget->OnDrop ( MouseDropEvent ( *element, m_lastMousePressPos, mousePos ) );
						m_dragDropTarget = nullptr;
					}
				}

				OnMouseUp ( element );
				break;
			}

			default : ;
		}
	}

	void InputHandler::CalculateTopMost ( Element* element )
	{
		if ( !m_top )
		{
			m_top = element;
		}

		if ( element->GetHeight () > m_top->GetHeight () )
		{
			OnMouseLeave ( m_top );
			m_top = element;
		}
	}

	template < typename _Ty >
	bool InputHandler::IsMouseWithin ( IntRect& rectangle, Vector2 <_Ty> point )
	{
		return rectangle.Contains ( point );
	}
}
