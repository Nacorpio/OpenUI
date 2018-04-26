#include "stdafx.h"
#include "GraphicsContext.h"

OpenUI::GraphicsContext::GraphicsContext ( const ClientWindow& clientWindow )
	: m_clientWindow ( clientWindow )
{
}

const OpenUI::ClientWindow& OpenUI::GraphicsContext::GetClientWindow () const
{
	return m_clientWindow;
}
