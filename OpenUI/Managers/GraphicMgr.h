#pragma once
#include "GraphicMgr.h"

class GraphicMgr
{
public:
	static GraphicMgr* instance()
	{
		GraphicMgr instance;
		return &instance;
	}

	void Draw ();
};

#define sGraphicMgr GraphicMgr::instance()