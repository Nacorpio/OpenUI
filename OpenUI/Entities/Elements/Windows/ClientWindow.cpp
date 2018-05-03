#include "stdafx.h"
#include "ClientWindow.h"
#include "Contexts.h"
#include "iostream"
#include "MouseInformation.h"

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

void OpenUI::ClientWindow::Start () const
{
	Element::Start();
}

void OpenUI::ClientWindow::Initialize ()
{
	Element::Initialize();
}

void OpenUI::ClientWindow::Update (const UpdateContext & p_updateContext)
{
	Element::Update(p_updateContext);
}

void OpenUI::ClientWindow::Draw ( const GraphicsContext& gContext )
{
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

		case sf::Event::Closed:
			{
				exit(0);
			}

		case sf::Event::Resized:
			{
				// Sets the view to the new resized view to that graphics doesn't scale with the client window.
				m_renderWindow->setView(*new sf::View(*new sf::FloatRect(0, 0, m_event.size.width, m_event.size.height)));			
			}

		default : ;
	}

	if ( !IsCursorInside () )
	{
		return;
	}

	for ( Element* element : m_descendants )
	{
		m_inputHandler.HandleElementEvent ( element);
	}
}
