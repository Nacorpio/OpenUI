#pragma once
#include "Math/Vector2.h"
//#include "Entities/Elements/Windows/ClientWindow.h"
#include <iostream>
#include "Entities/Elements/Windows/ClientWindow.h"

namespace OpenUI
{

	class MouseStateManager
	{
	public:

		MouseStateManager ()
		{
		}

		Element* CheckMouseIntersection (ClientWindow * p_clientWindow ) 
		{
			//m_activeClientWindow = p_clientWindow;
			//sf::Event myEvent;
			//p_clientWindow->GetRenderWindow().pollEvent ( myEvent );
			m_mouseLocation = IntVector(110, 60);
			//m_mouseLocation = IntVector(myEvent.mouseMove.x, myEvent.mouseMove.y);

			GetHighestElement(p_clientWindow->GetChildren())->OnMouseEnter();
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
					Element * const elementChild = GetHighestElement ( element->GetChildren() );

					if (elementChild == nullptr )
					{
						std::cout << "Interacted element found: " << element->GetName() << std::endl;
						return element;
					}
				}
			}
			return nullptr;
		}


		IntVector m_mouseLocation;
		Element * m_interactedElement;
		ClientWindow * m_activeClientWindow = nullptr;
	};
}
