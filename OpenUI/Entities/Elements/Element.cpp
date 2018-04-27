#include "stdafx.h"
#include "Element.h"
#include <algorithm>
#include "Common/Comparers/ElementComparer.h"
#include "Managers/ElementMgr.h"
#include "Entities/Elements/Windows/ClientWindow.h"
#include "Graphic/GraphicsContext.h"
#include <iostream>
#include <iso646.h>

namespace OpenUI
{
	Element::Element ( const std::string& name )
		: Control(name)
		, m_name ( name )
	{
		m_guidTypeId = ObjectGuid::TypeId::Element;

		SetFlag ( uint32_t ( ElementFlags::CaptureMouse ), true );
		SetFlag ( uint32_t ( ElementFlags::CaptureKeyboard ), true );
	}

	std::vector <sf::RectangleShape *>& Element::GetShapes ()
	{
		return m_shapes;
	}

	std::vector <sf::Text *>& Element::GetTexts ()
	{
		return m_texts;
	}

	void Element::SetParent ( Element* element )
	{
		if ( !element )
		{
			return;
		}

		if ( m_parent )
		{
			m_parent->RemoveChild ( element );
		}

		m_parent = element;
		OnParentChanged ( *m_parent );
	}

	sf::RectangleShape* Element::GetShape (const int & p_index )
	{
		if (sf::RectangleShape * rect = m_shapes[p_index])
		{
			return rect;
		}

		return nullptr;
	}

	void Element::AddShape ( sf::RectangleShape * p_rectangle )
	{
		if (!p_rectangle or HasShape ( p_rectangle ))
		{
			return;
		}

		m_drawables.insert(p_rectangle);
		m_shapes.emplace_back ( p_rectangle );
	}

	void Element::RemoveShape (const int & p_index )
	{
		if (!HasShape ( p_index ))
		{
			return;
		}

		m_shapes.erase ( m_shapes.begin() + p_index );
	}

	bool Element::HasShape (const int & p_index )
	{
		return m_shapes[p_index] != nullptr;
	}

	bool Element::HasShape(sf::RectangleShape * p_rectangle)
	{
		return find(m_shapes.begin(), m_shapes.end(), p_rectangle) != m_shapes.end();
	}

	void Element::AddChild ( Element* element )
	{
		if ( HasChild ( element ) )
		{
			std::cout << "Element '" << element->GetName () << " is already a child of '" << GetName () << "'" << std::endl;
			return;
		}

		element->SetParent ( this );
		element->SetDrawOrder ( m_children.size () );

		// If there is no client window, the current element must be the client window.
		//if ( !m_clientWindow )
		//{
		//	// Set the element's client window to this element.
		//	element->m_clientWindow = this->ToClientWindow ();
		//} 
		//else
		//{
		//	element->m_clientWindow = m_clientWindow;
		//}

		if (m_clientWindow)
		{
			element->m_clientWindow = m_clientWindow;
		}
		else
		{
			element->m_clientWindow = this->ToClientWindow();
		}

		element->m_clientWindow->m_descendants.insert(element);

		m_children.emplace_back ( element );

		// Invoke the OnChildAdded callback.
		OnChildAdded ( *element );
	}

	void Element::RemoveChild ( Element* element )
	{
		const auto it = std::find ( m_children.begin (), m_children.end (), element );

		if (it == m_children.end ())
		{
			std::cout << "Element '" << element->GetName() << "' is not a child of '" << GetName() << "'" << std::endl;
			return;
		}

		element->m_clientWindow->m_descendants.erase ( element );
		m_children.erase ( it );

		m_parent = nullptr;
		m_clientWindow = nullptr;

		OnChildRemoved ( *element );
	}

	bool Element::HasChild ( const Element* element )
	{
		if ( !element )
		{
			return false;
		}

		return std::find ( m_children.begin (), m_children.end (), element ) != m_children.end ();
	}

	void Element::Draw ( const GraphicsContext& gContext )
	{
		for (auto it = m_drawables.begin(); it != m_drawables.end();++it)
		{
			m_clientWindow->GetRenderWindow().draw(*it._Ptr->_Myval, sf::RenderStates::Default);
		}
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
