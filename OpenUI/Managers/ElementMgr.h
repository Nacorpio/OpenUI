#pragma once
#include <unordered_map>

class Element;
class Button;

typedef std::unordered_map <uint64_t, Element*> ElementMap;

class ElementMgr
{
public:
	static ElementMgr* instance ()
	{
		static ElementMgr instance;
		return &instance;
	}

	Element* operator [] ( uint64_t id );

	void Add ( uint64_t id, Element* element );
	bool Exists ( uint64_t id ) const;

	Button* CreateButton( uint64_t id, const std::string& name);
	Element* GetElementByName ( const std::string& name );

	std::vector <Element*>& GetElements ();

private:
	ElementMap m_mappedObjects;
	std::vector <Element*> m_objects;
};

#define sElementMgr ElementMgr::instance()
