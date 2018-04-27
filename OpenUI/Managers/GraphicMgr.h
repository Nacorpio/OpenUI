#pragma once
#include <set>
#include "ElementMgr.h"

namespace OpenUI
{
	class GraphicsContext;
	class ClientWindow;

	class GraphicMgr
	{
	public:
		static GraphicMgr* instance ()
		{
			static GraphicMgr instance;
			return &instance;
		}

		GraphicMgr ()
		{
			m_clientWindows = &sElementMgr->m_clientWindows;
		}

		void Draw ();

	private:
		std::set <ClientWindow*>* m_clientWindows { };
		GraphicsContext* m_graphicsContext { };
	};
}

#define sGraphicMgr OpenUI::GraphicMgr::instance()
