#pragma once
#include "Math/Vector2.h"
#include <iostream>
#include "Entities/Elements/Windows/ClientWindow.h"
#include "Common/Comparers/ElementComparer.h"

namespace OpenUI
{

	struct HighestElementInfo
	{
		Element * HighestElement;
		bool IntersectingMouse = false;

		HighestElementInfo(Element * p_element,bool p_intersectingMouse)
			: HighestElement( p_element ), IntersectingMouse ( p_intersectingMouse )
		{
		}

		void Reset()
		{
			HighestElement = nullptr;
			IntersectingMouse = false;
		}
	};

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

			m_mouseLocation.X = m_event.mouseMove.x;
			m_mouseLocation.Y = m_event.mouseMove.y;
			m_highestElementInfo.Reset();
			//auto x = GetHighestElement(p_clientWindow->GetChildren());
			GetHighestElement(p_clientWindow->GetChildren());
			SetMouseState(m_highestElementInfo.HighestElement);

			if(m_hoveredElements.size() > 0 && m_highestElementInfo.HighestElement)
			{
		/*		std::cout << "Size: " << m_hoveredElements.size() << " Name: " << GetHighestElement()->GetName() << " Height: " << GetHighestElement()->GetHeight() 
							<< " HighestElement: " << m_highestElementInfo.HighestElement->GetName() << " IntersectingMouse: " << m_highestElementInfo.IntersectingMouse << std::endl;
*/
			}
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

		IntVector & GetMousePosition ()
		{
			return m_mouseLocation;
		}

		void AddHoveringElement(Element * p_element)
		{
			m_hoveredElements.insert(p_element);
		}

		void RemoveHoveredElement(Element * p_element)
		{
			m_hoveredElements.erase(p_element);
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
				m_hoveredElements.insert(m_activeElement);
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
				if(!m_highestElementInfo.IntersectingMouse)
				{
					m_hoveredElements.erase(m_activeElement);
				}

				m_activeElement = p_element;
				m_activeElement->OnMouseEnter();

				m_hoveredElements.insert(p_element);
			}			
		}

		Element * GetHighestElement() const
		{
			if(m_hoveredElements.size() > 0)
			{
				return m_hoveredElements.begin()._Ptr->_Myval;
			}
			return nullptr;
		}

		/// <summary>
		///		Gets the highest element that is also intersecting with the mouse.
		/// </summary>
		/// <param name="p_elements">The elements to retrive the highest element from</param>
		/// <returns>The element that is highest and is intersecting the mouse</returns>
		void GetHighestElement (const std::vector<Element*> & p_elements)
		{
			for (Element * element: p_elements)
			{
				IntVector & elementPos = element->GetPosition();

				// Checks to see if the mouse location is within the bounds of the element.
				if(elementPos <= m_mouseLocation && elementPos + element->GetSize() >= m_mouseLocation)
				{
					// Returns a nullptr if the element doesn't have any children.
					GetHighestElement ( element->GetChildren() );

					// Returns the element child back to the previous function.
					if (m_highestElementInfo.HighestElement != nullptr )
					{
						m_highestElementInfo.HighestElement = element;
						m_highestElementInfo.IntersectingMouse = true;
						return;
					}

					//// Returns the element back to where the function was first called.
					//if (m_highestElementInfo.HighestElement == nullptr && element->GetHeight() > m_highestElementInfo.HighestElement->GetHeight())
					//{
					//	m_highestElementInfo.HighestElement = element;
					//	m_highestElementInfo.IntersectingMouse = true;
					//	return;
					//}
				}
			}
			m_highestElementInfo.Reset();
		}

		sf::Event m_event;
		IntVector m_mouseLocation{};
		Element * m_activeElement = nullptr;
		ClientWindow * m_activeClientWindow = nullptr;
		HighestElementInfo m_highestElementInfo = HighestElementInfo(nullptr,false);
		std::set<Element*,ElementComparerTree> m_hoveredElements;
	};
}
