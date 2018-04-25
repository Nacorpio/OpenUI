#pragma once
#include <unordered_map>
#include <set>

class Element;

typedef std::set <Element*> ElementSet;
typedef std::unordered_map<uint64_t, Element*> ElementMap;

class ElementMgr
{
public:
	static ElementMgr* instance ()
	{
		static ElementMgr instance;
		return &instance;
	}

	Element* operator [] ( uint64_t id );

	void Add ( uint64_t id, Element* obj );
	bool Exists ( uint64_t id ) const;

	ElementSet& GetElements()
	{
		return m_objects;
	}

private:
	ElementMap m_mappedObjects;
	ElementSet m_objects;
};

#define sElementMgr ElementMgr::instance()
