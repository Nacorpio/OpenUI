#include "stdafx.h"
#include <iostream>
#include "ElementMgr.h"
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
			std::cout << "Element with identifier '" << id << "' already exists." << std::endl;
			return;
		}

		element->Start ();

		m_elements.emplace_back ( element );
		m_mappedObjects.insert_or_assign ( id, element );
	}

	bool ElementMgr::Exists ( const uint64_t id ) const
	{
		return m_mappedObjects.count ( id ) > 0;
	}

	ClientWindow* ElementMgr::CreateClientWindow (
		const uint64_t id,
		const std::string& name,
		const RenderWindowSettings& settings )
	{
		if ( Exists ( id ) )
		{
			return nullptr;
		}

		if ( auto* clientWindow = new ClientWindow ( name, settings ) )
		{
			Add ( id, clientWindow );
			m_clientWindows.insert ( clientWindow );

			return clientWindow;
		}

		return nullptr;
	}

	Button* ElementMgr::CreateButton ( const uint64_t id, const std::string& name )
	{
		if ( Exists ( id ) )
		{
			return nullptr;
		}

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

	const std::vector <Element*>& ElementMgr::GetElements () const
	{
		return m_elements;
	}

	const std::set <ClientWindow*>& ElementMgr::GetClientWindows () const
	{
		return m_clientWindows;
	}
}
