#include "stdafx.h"
#include "GraphicMgr.h"
#include "Entities/Elements/Windows/ClientWindow.h"

namespace OpenUI
{
	void GraphicMgr::Draw ()
	{
		for ( auto it = m_clientWindows->begin () ; it != m_clientWindows->end () ; ++it )
		{
			it._Ptr->_Myval->Draw ( *m_graphicsContext );
		}
	}
}
