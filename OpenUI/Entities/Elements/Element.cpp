#include "stdafx.h"
#include "Element.h"
#include <algorithm>
#include "Common/Comparers/ElementComparer.h"
#include "Entities/Elements/Windows/ClientWindow.h"
#include "Graphic/GraphicsContext.h"
#include "Graphic/Scheme.h"
#include <iostream>
#include "Common/Global.h"

namespace OpenUI
{
	Element::Element ( const std::string& name )
		: Control ( name )
		, m_name ( name )
	{
		m_guidTypeId = ObjectGuid::TypeId::Element;

		AddFlag ( uint32_t ( ElementInputFlags::CaptureMouse ) );
		AddFlag ( uint32_t ( ElementInputFlags::CaptureKeyboard ) );

		m_background = new sf::RectangleShape ();
		AddShape ( m_background );
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
		SetPosition ( value.Position );
		SetSize ( value.Size );

		if ( m_bounds == value )
		{
			return; // Return if value is the same as the current bounds.
		}

		const IntRect delta = m_bounds - value;

		SetPosition ( value.Position );
		SetSize ( value.Size );

		OnBoundsChanged ( delta );
	}

	void Element::SetSize ( const IntVector& value )
	{
		const IntVector delta = m_bounds.Position - value;

		if ( delta.X == 0 && delta.Y == 0 )
		{
			return;
		}

		m_bounds.Size = value;
		m_background->setSize ( sf::Vector2f ( value.sfVector ) );

		for ( Element* child : m_children )
		{
			child->SetSize ( child->GetSize () - delta );
		}

		//for ( sf::RectangleShape* shape : m_shapes )
		//{
		//	auto x = ( value - m_bounds.Size + shape->getSize () ).sfVector2f;
		//	shape->setSize ( sf::Vector2f ( value.sfVector ) );
		//}

		OnSizeChanged ( delta );
	}

	void Element::SetPosition ( const IntVector& value )
	{
		const IntVector delta = m_bounds.Position - value;

		if ( delta.X == 0 && delta.Y == 0 )
		{
			return;
		}

		m_bounds.Position = value;
		m_background->setPosition ( sf::Vector2f ( value.sfVector ) );

		for ( Element* child : m_children )
		{
			child->SetPosition ( child->GetPosition () - delta );
		}

		for ( sf::RectangleShape* shape : m_shapes )
		{
			shape->setPosition
					( sf::Vector2f ( value.sfVector ) );
		}
		OnPositionChanged ( delta );
	}

	void Element::SetContainerRectangle ( const IntRect& p_value )
	{
		m_containerRectangle = p_value;
	}

	void Element::SetBackgroundColor ( const sf::Color& p_color ) const
	{
		m_background->setFillColor ( p_color );
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

		element->SetPosition ( m_containerRectangle.Position + element->GetPosition () );
		element->m_bounds.ResizeToFit ( m_bounds );

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
		m_background->setFillColor ( m_scheme->Colors.BackColor.Default );

		for ( auto element : m_children )
		{
			element->Start ();
		}
	}

	void Element::Initialize ()
	{
		m_background->setSize ( sf::Vector2f ( m_bounds.Size.sfVector ) );
		m_background->setPosition ( sf::Vector2f ( m_bounds.Position.sfVector ) );

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
			for ( auto shape : m_shapes )
			{
				renderWindow.draw ( *shape );
			}
		}

		for ( auto element : m_children )
		{
			element->Draw ( gContext );
		}

		m_scissorTest.RestoreParentsScissorTest ();
	}

	void Element::OnMouseEnter ()
	{
		LOG("MOUSE ENTER");
		m_background->setFillColor ( m_scheme->Colors.BackColor.Entered );
	}

	void Element::OnMouseClick ()
	{
		LOG("MOUSE CLICK");
		m_background->setFillColor ( m_scheme->Colors.BackColor.Entered );
	}

	void Element::OnMouseDoubleClick ()
	{
		LOG("MOUSE DOUBLE CLICK");
		m_background->setFillColor ( m_scheme->Colors.BackColor.Entered );
	}

	void Element::OnMouseLeave ()
	{
		LOG("MOUSE LEAVE");
		m_background->setFillColor ( m_scheme->Colors.BackColor.Default );
	}

	void Element::OnMouseHover ()
	{
		LOG("MOUSE HOVER");
		m_background->setFillColor ( m_scheme->Colors.BackColor.Hovered );
	}

	void Element::OnMouseMove ()
	{
	}

	void Element::OnMouseDown ()
	{
		m_background->setFillColor ( m_scheme->Colors.BackColor.Pressed );
	}

	void Element::OnMouseUp ()
	{
	}

	void Element::OnDrop ( const InputHandler::MouseDropEvent& event )
	{
	}

	void Element::OnDragBegin ()
	{
		m_background->setFillColor ( m_scheme->Colors.BackColor.Pressed );
	}

	void Element::OnDragDrop ( const InputHandler::MouseDragDropEvent& event )
	{
		m_background->setFillColor ( m_scheme->Colors.BackColor.Default );
	}

	void Element::OnFocusGained ()
	{
		LOG("GAINED FOCUS FOR " << GetName());
	}

	void Element::OnFocusLost ()
	{
		LOG("LOST FOCUS FOR " << GetName());
	}

	void Element::Update ()
	{
		if ( IsCursorInside () && !IsBeingHovered () && sTimeInformation->ElapsedTime - m_lastMoveTime >= 1000 )
		{
			AddState ( Hovered );
			OnMouseHover ();
		}

		for ( auto element : m_children )
		{
			element->Update ();
		}
	}

	void Element::OnBoundsChanged ( const IntRect& delta )
	{
		for ( Element* child : m_children )
		{
			child->OnParentBoundsChanged ( delta );
		}
	}

	void Element::OnPositionChanged ( const IntVector& delta )
	{
		m_scissorTest.UpdateScissorRectangle ( m_bounds );
		for ( Element* child : m_children )
		{
			child->OnParentPositionChanged ( delta );
		}
	}

	void Element::OnSizeChanged ( const IntVector& delta )
	{
		m_scissorTest.UpdateScissorRectangle ( m_bounds );
		for ( Element* child : m_children )
		{
			child->OnParentSizeChanged ( delta );
		}
	}

	void Element::OnParentBoundsChanged ( const IntRect& delta )
	{
		m_scissorTest.ParentScissorTest = m_parent->m_scissorTest.ScissorRectangle;
	}

	void Element::OnParentPositionChanged ( const IntVector& delta )
	{
		m_scissorTest.ParentScissorTest = m_parent->m_scissorTest.ScissorRectangle;
	}

	void Element::OnParentSizeChanged ( const IntVector& delta )
	{
		m_scissorTest.ParentScissorTest = m_parent->m_scissorTest.ScissorRectangle;
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

	void Element::GiveFocus ()
	{
		if ( HasFocus () )
		{
			return;
		}

		AddState ( Focused );

		OnFocusGained ();
		OnFocusChanged ();
	}

	void Element::LoseFocus ()
	{
		if ( ! HasFocus () )
		{
			return;
		}

		RemoveState ( Focused );

		OnFocusLost ();
		OnFocusChanged ();
	}

	void Element::SortDrawOrder () const
	{
		sort ( m_parent->m_children.begin (), m_parent->m_children.end (), ElementComparerDrawOrder () );
	}

	void Element::OnStateChanged ( const ControlState state )
	{
	}
}
