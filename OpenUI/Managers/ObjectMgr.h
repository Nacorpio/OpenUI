#pragma once
#include <unordered_map>
#include <set>

class Object;

class ObjectMgr
{
public:
	static ObjectMgr* instance ()
	{
		static ObjectMgr instance;
		return &instance;
	}

	std::unordered_map<uint64_t, Object*> m_mappedObjects;
	std::set<Object*> m_objects;
};

#define sObjectMgr ObjectMgr::instance()
