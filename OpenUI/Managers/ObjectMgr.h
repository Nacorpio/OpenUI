#pragma once
#include <unordered_map>

class ObjectMgr
{
public:
	static ObjectMgr* instance ()
	{
		static ObjectMgr instance;
		return &instance;
	}

};

#define sObjectMgr ObjectMgr::instance()
