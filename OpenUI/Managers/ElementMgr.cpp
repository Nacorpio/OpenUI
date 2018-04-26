#include "stdafx.h"
#include "ElementMgr.h"
#include <iostream>
#include "Entities/Elements/Element.h"
#include "Entities/Controls/Button.h"

namespace OpenUI
{
	ElementMgr::~ElementMgr ()
	{
		for ( const Element* element : m_elements )
		{
			delete element;
		}
	}

	Element* ElementMgr::operator[] ( const uint64_t id )
	{
		return m_mappedObjects[id];
	}

	void ElementMgr::Add ( const uint64_t id, Element* element )
	{
		if ( !element )
		{
			return;
		}

		if ( Exists ( id ) )
		{
			std::cout << "Element '" << element->GetName () << "' already exists." << std::endl;
			return;
		}

		element->Start();

		m_elements.emplace_back ( element );
		m_mappedObjects.insert_or_assign ( id, element );
	}

	bool ElementMgr::Exists ( const uint64_t id ) const
	{
		return m_mappedObjects.count ( id ) > 0;
	}

	Button* ElementMgr::CreateButton ( const uint64_t id, const std::string& name )
	{
		if ( auto* button = new Button ( name ) )
		{
			Add ( id, button );
			return button;
		}

		return nullptr;
	}

	Element* ElementMgr::GetElementByName ( const std::string& name )
	{
		for ( Element* element : m_elements )
		{
			if ( element->GetName () != name )
			{
				continue;
			}

			return element;
		}

		return nullptr;
	}

	std::vector <Element*>& ElementMgr::GetElements ()
	{
		return m_elements;
	}
}
