#pragma once

namespace OpenUI
{
	class GraphicsContext;

	class GraphicMgr
	{
	public:
		static GraphicMgr* instance()
		{
			GraphicMgr instance;
			return &instance;
		}

		static void Draw ( const GraphicsContext& gContext );
	};
}

#define sGraphicMgr GraphicMgr::instance()