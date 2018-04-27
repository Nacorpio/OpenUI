#include "stdafx.h"
#include "ClientWindow.h"

OpenUI::ClientWindow::ClientWindow ( const std::string& name, const RenderWindowSettings& windowSettings )
	: Element ( name )
	, m_renderWindow
	(
	 new sf::RenderWindow

	 		   
	 ( windowSettings.VideoMode, windowSettings.Title, windowSettings.Style, windowSettings.ContextSettings ) )
{
	m_guidDetail = ObjectGuid::Detail::ClientWindow;
}

OpenUI::ClientWindow::~ClientWindow ()
{
	delete m_renderWindow;
	m_renderWindow = nullptr;
}

void OpenUI::ClientWindow::Start ()
{
	for (Element* element : m_children)
	{
		element->Start();
	}
}

void OpenUI::ClientWindow::Initialize ()
{
	for (Element* element : m_children)
	{
		element->Initialize();
	}
}

void OpenUI::ClientWindow::Update ()
{
	for (Element* element : m_children)
	{
		element->Update();
	}
}

void OpenUI::ClientWindow::Draw ( const GraphicsContext& gContext )
{
	m_renderWindow->clear ( sf::Color::Cyan );

	for ( Element* element : m_children )
	{
		element->Draw ( gContext );
	}

	m_renderWindow->display ();
}

sf::RenderWindow& OpenUI::ClientWindow::GetRenderWindow () const
{
	return *m_renderWindow;
}
