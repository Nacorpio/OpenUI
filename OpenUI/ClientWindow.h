#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Entities/Elements/Element.h"
#include "SFML/Window/Event.hpp"
#include "Constants.h"

namespace OpenUI
{
	struct RenderWindowSettings
	{
		sf::VideoMode Size = sf::VideoMode(GLOBAL_RENDER_WINDOW_SIZE.X, GLOBAL_RENDER_WINDOW_SIZE.Y);
		sf::String Title = GLOBAL_WINDOW_TITLE;
		sf::Uint32 Style = sf::Style::Default;
		sf::ContextSettings ContextSettings = sf::ContextSettings(0, 0, 8);
		unsigned FrameRateLimit = 0;

		RenderWindowSettings()
		{
		}

		RenderWindowSettings(sf::VideoMode& p_size, sf::String& p_title, sf::Uint32 p_style, sf::ContextSettings& p_contextSettings,
							 unsigned p_frameRateLimit)
			: Size(p_size), Title(p_title), Style(p_style), ContextSettings(p_contextSettings), FrameRateLimit(p_frameRateLimit)
		{
		}
	};

	class ClientWindow
	{
	public:
		explicit ClientWindow(sf::RenderWindow * p_renderWindow)
			: m_renderwindow(p_renderWindow)
		{
		}
		~ClientWindow();

		/* Start the render window.*/
		void Start()
		{
			DrawElements();
			while (m_renderwindow->isOpen())
			{
				sf::Event event;
				while (m_renderwindow->waitEvent(event))
				{
					switch (event.type) {
						case sf::Event::Closed: break;
						case sf::Event::Resized: break;
						case sf::Event::LostFocus: break;
						case sf::Event::GainedFocus: break;
						case sf::Event::TextEntered: break;
						case sf::Event::KeyPressed: break;
						case sf::Event::KeyReleased: break;
						case sf::Event::MouseWheelScrolled:
							{
								//if (mouseStateManger->MouseWheelScrollEventPtr == nullptr)
								//{
								//	mouseStateManger->MouseWheelScrollEventPtr = &event.mouseWheelScroll;
								//}

								//for (auto & control : GetChildren ())
								//{
								//	mouseStateManger->OnMouseScroll(control);
								//}

								break;
							};
						case sf::Event::MouseButtonPressed:
							{
								//m_mouseStateManager->SetMouseButton(event.mouseButton.button);
								//m_mouseStateManager->OnMouseDown();
								break;
							}

						case sf::Event::MouseButtonReleased:
							{
								//m_mouseStateManager->SetMouseButton(event.mouseButton.button);
								//m_mouseStateManager->OnMouseReleased();
								break;
							}

						case sf::Event::MouseMoved:
							{
								//m_mouseStateManager->SetMouseLocation(event.mouseMove);
								//for (auto element : m_elements)
								//{
								//	m_mouseStateManager->OnMouseMove(*element);
								//}
								break;
							}

						case sf::Event::MouseEntered: break;
						case sf::Event::MouseLeft: break;
						default:;
					}

					if (event.type == sf::Event::Closed)
					{
						m_renderwindow->close();
					}
					DrawElements();
				}
			}
		}

		sf::RenderWindow * GetRenderWindow() const
		{
			return m_renderwindow;
		}

		std::vector<Element*> & GetElements()
		{
			return m_elements;
		}

		void AddElement(Element* p_element)
		{
			m_elements.emplace_back(p_element);
		}

		void SetRenderWindow(sf::RenderWindow * p_renderWindow)
		{
			m_renderwindow = p_renderWindow;
		}

	private:
		void DrawElements()
		{
			m_renderwindow->clear(m_clearColor);

			for (auto element : m_elements)
			{
				element->Draw();
			}

			m_renderwindow->display();
		}

		sf::RenderWindow * m_renderwindow;
		std::vector<Element*> m_elements;
		sf::Color m_clearColor = sf::Color(43,43,43);
	};

	
}
