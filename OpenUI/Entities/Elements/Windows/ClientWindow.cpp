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
}

void OpenUI::ClientWindow::Initialize ()
{
}

void OpenUI::ClientWindow::Update ()
{
}

void OpenUI::ClientWindow::Draw ( const GraphicsContext& gContext )
{
}



sf::RenderWindow& OpenUI::ClientWindow::GetRenderWindow () const
{
	return *m_renderWindow;
}
