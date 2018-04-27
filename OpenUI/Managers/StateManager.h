#pragma once
#include "Math/Vector2.h"
#include <iostream>
#include "Entities/Elements/Windows/ClientWindow.h"

namespace OpenUI
{

	class StateManager
	{
	public:

		StateManager ()
		{
		}

		Element* CheckMouseIntersection (ClientWindow * p_clientWindow ) 
		{
			m_activeClientWindow = p_clientWindow;
			
			// Pools the event data from the active clientwindow.
			p_clientWindow->GetRenderWindow().pollEvent ( m_event );

			m_mouseLocation = IntVector(m_event.mouseMove.x, m_event.mouseMove.y);

			SetMouseState(GetHighestElement(p_clientWindow->GetChildren()));
	
			
			/*switch (myEvent.type)
			{

				case sf::Event::Closed :
					break;
				case sf::Event::Resized :
					break;
				case sf::Event::LostFocus :
					break;
				case sf::Event::GainedFocus :
					break;
				case sf::Event::TextEntered :
					break;
				case sf::Event::MouseWheelMoved :
					{

					}
				case sf::Event::MouseWheelScrolled :
					break;
				case sf::Event::MouseButtonPressed :
					break;
				case sf::Event::MouseButtonReleased :
					break;
				case sf::Event::GetHighestElement :
					break;
				case sf::Event::MouseEntered :
					break;
				case sf::Event::MouseLeft :
					break;
				default : ;
			}*/
			return nullptr;
		}

	private:

		void SetMouseState(Element * p_element)
		{
			if(!p_element)
			{
				return;
			}

			// Active element is not set, therfore we call OnMouseEnter.
			if(!m_activeElement)
			{
				m_activeElement = p_element;
				m_activeElement->OnMouseEnter();
				return;
			}

			// Element is the same as the active element, therefore call OnMouseMove.
			if(p_element == m_activeElement)
			{
				p_element->OnMouseMove();
				return;
			}

			if (p_element != m_activeElement)
			{
				m_activeElement->OnMouseLeave();
				m_activeElement = p_element;
				m_activeElement->OnMouseEnter();
			}			
		}

		IntVector & GetMousePosition()
		{
			return m_mouseLocation;
		}

		/// <summary>
		///		Gets the element that is furthest in draw order and is also intersecting with the mouse.
		/// </summary>
		/// <param name="p_elements">The elements to retrive the highest element from</param>
		/// <returns>The element that is furthest in draw order and is intersecting the mouse</returns>
		Element * GetHighestElement (const std::vector<Element*> & p_elements) const
		{
			for (Element * element: p_elements)
			{
				IntVector & elementPos = element->GetPosition();

				// Checks to see if the mouse location is within the bounds of the element.
				if(elementPos <= m_mouseLocation && elementPos + element->GetSize() >= m_mouseLocation)
				{
					// Returns a nullptr if the element doesn't have any children.
					Element * elementChild = GetHighestElement ( element->GetChildren() );

			
					if (elementChild != nullptr && m_foundElement == false)
					{
						std::cout << "Interacted elementChild found: " << elementChild->GetName() << std::endl;
						m_foundElement = true;
						return elementChild;
					}
					if (elementChild == nullptr && m_foundElement == false)
					{
						std::cout << "Interacted element found: " << element->GetName() << std::endl;
						m_foundElement = true;
						return element;
					}
				}
			}

			return nullptr;
		}

		mutable bool m_foundElement = false;
		sf::Event m_event;
		IntVector m_mouseLocation;
		Element * m_activeElement = nullptr;
		ClientWindow * m_activeClientWindow = nullptr;
	};
}
