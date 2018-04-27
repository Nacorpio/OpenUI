#include "stdafx.h"
#include "GraphicsContext.h"

OpenUI::GraphicsContext::GraphicsContext ()
{
}

OpenUI::ClientWindow& OpenUI::GraphicsContext::GetClientWindow () const
{
	return *m_clientWindow;
}
