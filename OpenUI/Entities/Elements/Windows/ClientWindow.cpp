#include "stdafx.h"
#include "ClientWindow.h"
#include "Contexts.h"
#include "iostream"

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
	for (auto element : m_descendants)
	{
		delete element;
	}

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

void OpenUI::ClientWindow::Input ( const InputContext & inputContext )
{
	if ( !m_renderWindow->pollEvent ( m_event ) )
	{
		return;
	}

	m_lastEvent = m_event;

	switch ( m_event.type )
	{
		case sf::Event::MouseEntered :
		{
			OnMouseEnter ();
			return;
		}

		case sf::Event::MouseLeft :
		{
			OnMouseLeave ();
			return;
		}

		case sf::Event::MouseMoved :
		{
			m_inputHandler.Refresh ( m_event.mouseMove );
			break;
		}

		default : ;
	}

	if ( !IsCursorInside () )
	{
		return;
	}

	for ( Element* element : m_descendants )
	{
		m_inputHandler.HandleInput ( element, m_event, inputContext);
	}
}
