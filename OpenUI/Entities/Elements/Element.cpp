#include "stdafx.h"
#include "Element.h"
#include <algorithm>
#include "Common/Comparers/ElementComparer.h"
#include "Managers/ElementMgr.h"
#include "Entities/Elements/Windows/ClientWindow.h"
#include <iostream>

namespace OpenUI
{
	void Element::SetParent ( Element* element )
	{
		if ( element->GetParent () )
		{
			element->GetParent ()->RemoveChild ( element );
		}

		m_parent = element;
	}

	void Element::AddChild ( Element* element )
	{
		if ( HasChild ( element ) )
		{
			std::cout << "Element " << std::endl;
			return;
		}

		element->SetParent ( this );
		element->SetDrawOrder ( m_children.size () );

		if ( !m_clientWindow )
		{
			element->m_clientWindow = dynamic_cast <ClientWindow*> (this);
		}

		m_children.emplace_back ( element );
		OnChildAdded ( *element );
	}

	void Element::RemoveChild ( Element* element )
	{
		if ( !HasChild ( element ) )
		{
			return;
		}

		const auto it = std::find ( m_children.begin (), m_children.end (), element );
		m_children.erase ( it );

		m_parent = nullptr;

		OnChildRemoved ( *element );
	}

	bool Element::HasChild ( const Element* element )
	{
		return std::find ( m_children.begin (), m_children.end (), element ) != m_children.end ();
	}

	bool Element::operator== ( const Element& rhs ) const
	{
		return m_name == rhs.m_name;
	}

	bool Element::operator!= ( const Element& rhs ) const
	{
		return !( *this == rhs );
	}

	void Element::SetDrawOrder ( const uint16_t value )
	{
		m_drawOrder = value;
		std::sort ( m_parent->m_children.begin (), m_parent->m_children.end (), ElementComparer () );
	}

	void Element::Sort () const
	{
		std::sort ( m_parent->m_children.begin (), m_parent->m_children.end (), ElementComparer () );
	}
}
