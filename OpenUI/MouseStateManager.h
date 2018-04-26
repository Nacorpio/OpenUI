#pragma once
#include "Math/Vector2.h"
#include "Entities/Elements/Windows/ClientWindow.h"
#include <iostream>

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
			m_activeClientWindow = p_clientWindow;
			sf::Event myEvent;
			p_clientWindow->GetRenderWindow().pollEvent ( myEvent );
			m_mouseLocation = IntVector(60, 61);
			//m_mouseLocation = IntVector(myEvent.mouseMove.x, myEvent.mouseMove.y);
			MouseMoved(m_activeClientWindow->GetChildren());
			switch (myEvent.type)
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
				case sf::Event::MouseMoved :
					break;
				case sf::Event::MouseEntered :
					break;
				case sf::Event::MouseLeft :
					break;
				default : ;
			}
			return nullptr;
		}

	private:
		Element * MouseMoved (const std::vector<Element*> & p_elements)
		{
			for (Element * element: p_elements)
			{
				IntVector & elementPos = element->GetPosition();
				IntVector & elementSize = element->GetSize();

				// Checks to see if the mouse location is within the bounds of the element.
				if(elementPos <= m_mouseLocation && elementPos + elementSize >= m_mouseLocation)
				{
					// Returns a nullptr if the element doesn't have any children.
					Element *const elementChild = MouseMoved ( element->GetChildren() );

					if (elementChild == nullptr && !m_interactedElement)
					{
						m_interactedElement = element;
						std::cout << "Interacted element found: " << element->GetName() << std::endl;
						return element;
					}
				}
			}
			return nullptr;
		}


		IntVector m_mouseLocation = IntVector(0,0);
		Element * m_interactedElement = nullptr;
		ClientWindow * m_activeClientWindow = nullptr;
	};
}
