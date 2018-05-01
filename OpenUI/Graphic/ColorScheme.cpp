#include "stdafx.h"
#include "ColorScheme.h"

namespace OpenUI
{
	ColorState::ColorState ( const sf::Color & p_backColor, const sf::Color & p_foreColor,
									 const sf::Color & p_outlineColor )
		: BackColor ( p_backColor )
		, ForeColor ( p_foreColor )
		, OutlineColor ( p_outlineColor )
	{
	}

	const ColorState& ColorScheme::operator[] ( MouseState p_state )
	{
		return GetColor ( p_state );
	}

	ColorScheme::ColorScheme ()
	{
		m_colors = std::unordered_map <MouseState, ColorState> {
			{ MouseState::Entered, ColorState ( sf::Color ( 63, 63, 63 ), sf::Color ( 63, 63, 63 ), sf::Color ( 63, 63, 63 ) ) },
			{ MouseState::None,ColorState ( sf::Color ( 43, 43, 43 ), sf::Color ( 43, 43, 43 ), sf::Color ( 43, 43, 43 ) ) },
			{ MouseState::Pressed,ColorState ( sf::Color ( 94, 94, 94 ), sf::Color ( 94, 94, 94 ), sf::Color ( 94, 94, 94 ) ) }
		};
	}

	bool ColorScheme::ContainColorState ( MouseState p_state )
	{
		if (m_colors.empty())
		{
			return false;
		}

		m_it = m_colors.find ( p_state );
		return m_it != m_colors.end();
	}

	const ColorState& ColorScheme::GetColor ( const MouseState p_state )
	{
		if (ContainColorState ( p_state ))
		{
			return m_it._Ptr->_Myval.second;
		}

		return m_it._Ptr->_Myval.second;
	}
}