#include "stdafx.h"
#include "ClientWindow.h"
#include "iostream"
#include "Common/Global.h"

OpenUI::ClientWindow::ClientWindow ( const std::string& name, const RenderWindowSettings& windowSettings )
	: Element ( name )
	, m_renderWindow
	(
	 new sf::RenderWindow

	 		   
	 ( windowSettings.VideoMode, windowSettings.Title, windowSettings.Style, windowSettings.ContextSettings ) )
{
	m_guidDetail = ObjectGuid::Detail::ClientWindow;
	SetBounds({ 0,0,600,600 });	
}

OpenUI::ClientWindow::~ClientWindow ()
{
	delete m_renderWindow;
	m_renderWindow = nullptr;
}

void OpenUI::ClientWindow::Start ()
{
	Element::Start();
}

void OpenUI::ClientWindow::Initialize ()
{
	Element::Initialize();
}

void OpenUI::ClientWindow::Update ()
{
	Element::Update();
}

void OpenUI::ClientWindow::Draw ( const GraphicsContext& gContext )
{
	glDisable(GL_SCISSOR_TEST);
	m_renderWindow->clear ( sf::Color(43,43,43));
	
	Element::Draw(gContext);

	m_renderWindow->display ();
}

sf::RenderWindow& OpenUI::ClientWindow::GetRenderWindow () const
{
	return *m_renderWindow;
}

void OpenUI::ClientWindow::Input ()
{
	if ( !m_renderWindow->pollEvent ( m_event ) )
	{
		return;
	}


	sInputInformation->LastEvent = m_event.type;

	switch (m_event.type)
	{
		case sf::Event::MouseButtonPressed :
			{
				sInputInformation->MouseIsDown = true;
				sInputInformation->LastActiveMouseButton = m_event.mouseButton.button;
				break;
			}

		case sf::Event::MouseButtonReleased :
			{
				sInputInformation->MouseIsDown = false;
				sInputInformation->LastActiveMouseButton = m_event.mouseButton.button;
				break;
			}

		case sf::Event::MouseEntered :
			{
				OnMouseEnter();
				return;
			}

		case sf::Event::MouseLeft :
			{
				OnMouseLeave();
				return;
			}

		case sf::Event::MouseMoved :
			{
				sInputInformation->MousePosition.X = m_event.mouseMove.x;
				sInputInformation->MousePosition.Y = m_event.mouseMove.y;
				break;
			}
		case sf::Event::KeyPressed:
			{
				sInputInformation->KeyIsDown = true;
				sInputInformation->LastKeyEvent = m_event.key;
				break;
			}
		case sf::Event::KeyReleased :
			{
				sInputInformation->KeyIsDown = false;
				sInputInformation->LastKeyEvent = m_event.key;
				break;
			}
		case sf::Event::TextEntered :
			{
				sInputInformation->LastTextEvent = m_event.text;
				break;
			}
		case sf::Event::MouseWheelScrolled :
			{
				sInputInformation->MouseWheelDelta = m_event.mouseWheelScroll.delta;
				break;
			}
		case sf::Event::Closed:
			{
				exit(0);
			}

		case sf::Event::Resized:
			{
				// Sets the view to the new resized view to that graphics doesn't scale with the client window.
				m_renderWindow->setView(sf::View(sf::FloatRect(0, 0, m_event.size.width, m_event.size.height)));			
			}

		default : ;
	}

	if ( !IsCursorInside () )
	{
		return;
	}

	for ( Element* element : m_descendants )
	{
		m_inputHandler.HandleInput ( element );
	}
}
