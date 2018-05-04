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
		OnStateChanged ( state );
	}

	void Control::SetState ( const int state )
	{
		SetState ( ControlState ( state ) );
	}

	void Control::AddState ( const ControlState state )
	{
		SetState ( m_st | state );
	}

	void Control::RemoveState ( const ControlState state )
	{
		SetState ( m_st & ~state );
	}

	void Control::ToggleState ( const ControlState state )
	{
		SetState ( m_st ^ state );
	}

	bool Control::HasState ( const ControlState state ) const
	{
		return m_st & state;
	}
}
