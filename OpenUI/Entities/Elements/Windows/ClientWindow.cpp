#include "stdafx.h"
#include "ClientWindow.h"

void OpenUI::ClientWindow::Start ()
{
	m_renderWindow->create (
						    m_renderWindowSettings.VideoMode,
						    m_renderWindowSettings.Title,
						    m_renderWindowSettings.Style,
						    m_renderWindowSettings.ContextSettings );
}

void OpenUI::ClientWindow::Initialize ()
{
}

void OpenUI::ClientWindow::Update ()
{
}

void OpenUI::ClientWindow::Draw ()
{
}
