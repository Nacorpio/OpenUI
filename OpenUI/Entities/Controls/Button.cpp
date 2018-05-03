#include "stdafx.h"
#include "Button.h"

namespace OpenUI
{
	Button::Button ( const std::string& name )
		: Element ( name )
	{
		m_guidDetail = ObjectGuid::Detail::Button;
	}

	Button::~Button ()
	{
	}

	void Button::Start () const
	{
		Element::Start ();
	}

	void Button::Initialize ()
	{
		Element::Initialize ();
	}

	void Button::Update ( const UpdateContext& p_updateContext )
	{
		Element::Update ( p_updateContext );
	}

	void Button::Draw ( const GraphicsContext& gContext )
	{
		Element::Draw ( gContext );
	}

	void Button::OnMouseEnter ()
	{
		Element::OnMouseEnter ();
	}

	void Button::OnMouseLeave ()
	{
		Element::OnMouseLeave ();
	}

	void Button::OnMouseMove ()
	{
		Element::OnMouseMove ();
	}

	void Button::OnMouseHover ()
	{
		Element::OnMouseHover ();
	}

	void Button::OnMouseDown ( )
	{
		Element::OnMouseDown ( );
	}

	void Button::OnMouseClick ( )
	{
		Element::OnMouseClick ( event );
		LOG("SINGLE CLICK");
	}

	void Button::OnMouseDoubleClick ( const sf::Event::MouseButtonEvent& event )
	{
		Element::OnMouseDoubleClick ( event );
		LOG("DOUBLE CLICK");
	}

	void Button::OnMouseUp (  )
	{
		Element::OnMouseUp (  );
	}

	void Button::OnDrop ( const InputHandler::MouseDropEvent& event )
	{
		Element::OnDrop ( event );
	}

	void Button::OnDragDrop ( const InputHandler::MouseDragDropEvent& event )
	{
		Element::OnDragDrop ( event );

		if ( !event.DidHitTarget () )
		{
			SetPosition ( event.End );
		}
	}

	void Button::OnDragBegin ()
	{
		Element::OnDragBegin ();
	}
}
