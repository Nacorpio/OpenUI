#include "stdafx.h"
#include "Control.h"

namespace OpenUI
{
	Control::Control ( const std::string& name )
	{
	}

	ControlState Control::GetState () const
	{
		return ControlState ( m_st );
	}

	void Control::SetState ( const ControlState state )
	{
		m_state = state;
	}

	void Control::OnMouseEnter ()
	{
		AddState ( Entered );
	}

	void Control::OnMouseLeave ()
	{
		RemoveState ( Entered );
	}

	void Control::OnMouseHover ()
	{
		AddState ( Hovered );
	}

	void Control::OnMouseMove ()
	{
	}

	void Control::OnMouseDown ()
	{
		AddState ( Pressed );
	}

	void Control::OnMouseClick (  )
	{
		RemoveState ( Pressed );
	}

	void Control::OnMouseUp ()
	{
		RemoveState ( Pressed );
	}

	void Control::OnDrop ( const InputHandler::MouseDropEvent& event )
	{
	}

	void Control::OnDragDrop ( const InputHandler::MouseDragDropEvent& event )
	{
		RemoveState ( Dragged );
		RemoveState ( Pressed );

	}

	void Control::OnDragBegin ()
	{
		AddState ( Dragged );
	}

	void Control::OnDragEnter ( Element* )
	{
		AddState ( Entered );
	}

	void Control::OnDragMove ( Element* source )
	{
	}
}
