#include "stdafx.h"
#include "Element.h"
#include <algorithm>
#include "Common/Comparers/ElementComparer.h"
#include "Entities/Elements/Windows/ClientWindow.h"
#include "Graphic/GraphicsContext.h"
#include "Graphic/Scheme.h"
#include <iostream>

namespace OpenUI
{
	Element::Element ( const std::string& name )
		: Control ( name )
		, m_name ( name )
	{
		m_guidTypeId = ObjectGuid::TypeId::Element;

		AddFlag ( uint32_t ( ElementFlags::CaptureMouse ) );
		AddFlag ( uint32_t ( ElementFlags::CaptureKeyboard ) );
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

	void Element::SetBounds ( const IntRect& value )
	{
		IntRect delta = m_bounds - value;
		m_bounds = value;
		for ( sf::RectangleShape* shape : m_shapes )
		{
			shape->setSize
					( sf::Vector2f ( value.Size.sfVector ) ); //((p_value.Size - m_bounds.Size + shape->getSize()).sfVector2f);
			shape->setPosition
					( sf::Vector2f ( value.Position.sfVector ) );
		}
		OnBoundsChanged ( delta );
	}

	void Element::SetSize ( const IntVector& value )
	{
		m_bounds.Size = value;
		m_background.setSize ( sf::Vector2f ( value.X, value.Y ) );

		for ( sf::RectangleShape* shape : m_shapes )
		{
			auto x = ( value - m_bounds.Size + shape->getSize () ).sfVector2f;
			shape->setSize ( sf::Vector2f ( value.sfVector ) ); //((p_value - m_bounds.Size + shape->getSize()).sfVector2f);
		}
	}

	void Element::SetPosition ( const IntVector& value )
	{
		m_bounds.Position = value;
		m_background.setPosition ( (int) value.X, (int) value.Y );

		for ( sf::RectangleShape* shape : m_shapes )
		{
			shape->setPosition
					( sf::Vector2f ( value.sfVector ) ); //((p_value - m_bounds.Position + shape->getPosition()).sfVector2f);
		}
	}

	sf::RectangleShape* Element::GetShape ( const int& index )
	{
		if ( sf::RectangleShape* rect = m_shapes[index] )
		{
			return rect;
		}

		return nullptr;
	}

	void Element::AddShape ( sf::RectangleShape* rectangle )
	{
		if ( !rectangle || HasShape ( rectangle ) )
		{
			return;
		}

		m_drawables.insert ( rectangle );
		m_shapes.emplace_back ( rectangle );
	}

	void Element::RemoveShape ( const int& index )
	{
		if ( !HasShape ( index ) )
		{
			return;
		}

		m_shapes.erase ( m_shapes.begin () + index );
	}

	bool Element::HasShape ( const int& index )
	{
		return m_shapes[index] != nullptr;
	}

	bool Element::HasShape ( sf::RectangleShape* rectangle )
	{
		return find ( m_shapes.begin (), m_shapes.end (), rectangle ) != m_shapes.end ();
	}

	void Element::AddChild ( Element* element )
	{
		if ( HasChild ( element ) )
		{
			std::cout << "Element '" << element->GetName () << " is already a child of '" << GetName () << "'" << std::endl;
			return;
		}

		element->m_parent = this;
		element->m_drawOrder = uint16_t ( m_children.size () );
		element->m_height = uint16_t ( m_height + m_children.size () + 1 );
		element->m_level = m_level + 1;

		if ( m_clientWindow )
		{
			element->m_clientWindow = m_clientWindow;
		}
		else
		{
			element->m_clientWindow = this->ToClientWindow ();
		}

		element->m_clientWindow->m_descendants.insert ( element );
		m_children.emplace_back ( element );

		// Invoke the OnChildAdded callback.
		OnChildAdded ( *element );
	}

	void Element::RemoveChild ( Element* element )
	{
		const auto it = find ( m_children.begin (), m_children.end (), element );

		if ( it == m_children.end () )
		{
			std::cout << "Element '" << element->GetName () << "' is not a child of '" << GetName () << "'" << std::endl;
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

		return find ( m_children.begin (), m_children.end (), element ) != m_children.end ();
	}

	void Element::Start () const
	{
		for ( auto element : m_children )
		{
			element->Start ();
		}
	}

	void Element::Initialize ()
	{
		m_background.setSize ( sf::Vector2f ( m_bounds.Size.sfVector ) );
		m_background.setPosition ( sf::Vector2f ( m_bounds.Position.sfVector ) );
		m_background.setFillColor ( m_scheme->Colors.BackColor.Default );

		for ( auto element : m_children )
		{
			element->Initialize ();
		}
	}

	void Element::Draw ( const GraphicsContext& gContext )
	{
		m_scissorTest.SetScissorTest ();

		if ( m_clientWindow )
		{
			sf::RenderWindow& renderWindow = m_clientWindow->GetRenderWindow ();
			renderWindow.draw ( m_background );

			for ( auto it = m_drawables.begin () ; it != m_drawables.end () ; ++it )
			{
				renderWindow.draw ( *it._Ptr->_Myval, sf::RenderStates::Default );
			}
		}

		for ( auto element : m_children )
		{
			element->Draw ( gContext );
		}

		m_scissorTest.RestorePreviousScissorTest ();
	}

	void Element::OnMouseEnter ()
	{
		Control::OnMouseEnter ();
		m_background.setFillColor ( m_scheme->Colors.BackColor.Entered );
	}

	void Element::OnMouseLeave ()
	{
		Control::OnMouseLeave ();
		m_background.setFillColor ( m_scheme->Colors.BackColor.Default );
	}

	void Element::OnMouseHover ()
	{
		Control::OnMouseHover ();
	}

	void Element::OnMouseMove ()
	{
		Control::OnMouseMove ();
	}

	void Element::OnMouseDown ( const sf::Event::MouseButtonEvent& event )
	{
		Control::OnMouseDown ( event );
		m_background.setFillColor ( m_scheme->Colors.BackColor.Pressed );
	}

	void Element::OnMouseUp ( const sf::Event::MouseButtonEvent& event )
	{
		Control::OnMouseUp ( event );
		m_background.setFillColor ( m_scheme->Colors.BackColor.Default );
	}

	void Element::OnMouseClick ( const sf::Event::MouseButtonEvent& event )
	{
		Control::OnMouseClick ( event );
		m_background.setFillColor ( m_scheme->Colors.BackColor.Entered );
	}

	void Element::OnMouseDoubleClick ( const sf::Event::MouseButtonEvent& event )
	{
		Control::OnMouseDoubleClick ( event );
		m_background.setFillColor(m_scheme->Colors.BackColor.Entered);
	}

	void Element::OnDrop ( const InputHandler::MouseDropEvent& event )
	{
		Control::OnDrop ( event );
	}

	void Element::OnDragBegin ()
	{
		Control::OnDragBegin ();
		m_background.setFillColor ( m_scheme->Colors.BackColor.Pressed );
	}

	void Element::OnDragDrop ( const InputHandler::MouseDragDropEvent& event )
	{
		Control::OnDragDrop ( event );
		m_background.setFillColor ( m_scheme->Colors.BackColor.Default );
	}

	void Element::Update ( const UpdateContext& updateContext )
	{
		for ( auto element : m_children )
		{
			element->Update ( updateContext );
		}
	}

	void Element::OnBoundsChanged ( IntRect& delta )
	{
		OnParentBoundsChanged ( delta );
	}

	void Element::OnParentBoundsChanged ( IntRect& delta )
	{
		m_scissorTest.UpdateScissorRectangle ( m_bounds );
		for ( Element* child : m_children )
		{
			child->OnParentBoundsChanged ( delta );
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
		sort ( m_parent->m_children.begin (), m_parent->m_children.end (), ElementComparerDrawOrder () );
	}

	void Element::SortDrawOrder () const
	{
		sort ( m_parent->m_children.begin (), m_parent->m_children.end (), ElementComparerDrawOrder () );
	}

	void Element::OnStateChanged ( const ControlState state )
	{
	}
}
