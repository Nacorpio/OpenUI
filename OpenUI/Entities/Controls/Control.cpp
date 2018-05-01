#include "stdafx.h"
#include "Control.h"
#include "Common/Constants.h"
#include <iostream>

namespace OpenUI
{
	Control::Control ( const std::string& name )
	{
	}

	Control::ControlState Control::GetState () const
	{
		return (ControlState) m_st;
	}

	void Control::SetState ( const ControlState state )
	{
		m_state = state;
	}

	void Control::OnMouseEnter ()
	{
		AddState ( Entered );
		LOG("");
	}

	void Control::OnMouseLeave ()
	{
		RemoveState ( Entered );
		LOG("");
	}

	void Control::OnMouseHover ()
	{
		AddState ( Hovered );
		LOG("");
	}

	void Control::OnMouseMove ()
	{
	}

	void Control::OnMouseDown ( const sf::Event::MouseButtonEvent& event )
	{
		AddState ( Pressed );
		LOG("");
	}

	void Control::OnMouseClick ( const sf::Event::MouseButtonEvent& event )
	{
		RemoveState ( Pressed );
		LOG("");
	}

	void Control::OnMouseUp (const sf::Event::MouseButtonEvent& event )
	{
		RemoveState ( Pressed );
		LOG("");
	}

	void Control::OnDrop ( const InputContext::MouseDropEvent& event )
	{
		LOG("");
	}

	void Control::OnDragDrop ( const InputContext::MouseDragDropEvent& event )
	{
		RemoveState ( Dragged );
		RemoveState ( Pressed );

		LOG("");
	}

	void Control::OnDragBegin ()
	{
		AddState ( Dragged );
		LOG("");
	}

	void Control::OnDragEnter ( Element* )
	{
		AddState ( Entered );
		LOG("");
	}

	void Control::OnDragMove ( Element* source )
	{
	}
}
