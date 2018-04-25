#pragma once

class GraphicMgr
{
public:
	static GraphicMgr* instance()
	{
		GraphicMgr instance;
		return &instance;
	}

	static void Draw ();
};

#define sGraphicMgr GraphicMgr::instance()