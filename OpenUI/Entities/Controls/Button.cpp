#include "stdafx.h"
#include "Button.h"
#include <iostream>

namespace OpenUI
{
	Button::Button ( const std::string& name )
		: Element ( name )
	{
		m_guidDetail = ObjectGuid::Detail::Button;
		AddShape ( new sf::RectangleShape ( { 100, 100 } ) );
	}

	Button::~Button ()
	{
	}

	void Button::Start () const
	{
		Element::Start ();
	}

	void Button::Initialize () const
	{
		Element::Initialize ();
	}

	void Button::Update ()
	{
		Element::Update ();
	}

	void Button::Draw ( const GraphicsContext& gContext )
	{
		Element::Draw ( gContext );
	}

	void Button::OnMouseEnter ()
	{
		Element::OnMouseEnter ();
		GetShape ( 0 )->setFillColor ( sf::Color ( 75, 75, 75 ) );
	}

	void Button::OnMouseLeave ()
	{
		Element::OnMouseLeave ();
		GetShape ( 0 )->setFillColor ( sf::Color ( 45, 45, 45 ) );
	}

	void Button::OnMouseMove ()
	{
		Element::OnMouseMove ();
	}

	void Button::OnMouseHover ()
	{
		Element::OnMouseHover ();
	}

	void Button::OnMouseDown ( const sf::Event::MouseButtonEvent& event )
	{
		Element::OnMouseDown ( event );
		GetShape ( 0 )->setFillColor ( sf::Color ( 125, 125, 125 ) );
	}

	void Button::OnMouseClick ( const sf::Event::MouseButtonEvent& event )
	{
		Element::OnMouseClick ( event );
		GetShape ( 0 )->setFillColor ( sf::Color ( 75, 75, 75 ) );
	}

	void Button::OnMouseUp ( const sf::Event::MouseButtonEvent& event )
	{
		Element::OnMouseUp ( event );
	}

	void Button::OnDrop ( const InputContext::MouseDropEvent& event )
	{
		Element::OnDrop ( event );
	}

	void Button::OnDragBegin ()
	{
		Element::OnDragBegin ();
	}
}
