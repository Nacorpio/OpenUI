#pragma once
#include <unordered_map>
#include "Common/Enums.h"
#include <SFML/Graphics/Color.hpp>
#include "Common/Constants.h"
#include <iostream>

namespace OpenUI
{
	struct ColorState
	{
		sf::Color BackColor;
		sf::Color ForeColor;
		sf::Color OutlineColor;

		ColorState(const sf::Color & p_backColor,const sf::Color & p_foreColor,const sf::Color & p_outlineColor)
			  : BackColor(p_backColor),
				ForeColor(p_foreColor),
				OutlineColor(p_outlineColor)
		{			
		}
	};

	struct ColorScheme
	{
		const ColorState & operator [] (MouseState p_state)
		{
			return GetColor(p_state);
		}

		ColorScheme()
		{
			m_colors = std::unordered_map<MouseState, ColorState>{
				{ MouseState::Entered, ColorState(sf::Color(63, 63, 63), sf::Color(63, 63, 63), sf::Color(63, 63, 63))},
				{ MouseState::None,ColorState(sf::Color(43,43,43), sf::Color(43, 43, 43), sf::Color(43, 43, 43))},
				{ MouseState::Released, ColorState(sf::Color(63, 63, 63), sf::Color(63, 63, 63), sf::Color(63, 63, 63))},
				{ MouseState::Moved, ColorState(sf::Color(63, 63, 63), sf::Color(63, 63, 63), sf::Color(63, 63, 63))},
				{ MouseState::Clicked,ColorState(sf::Color(94, 94, 94), sf::Color(94, 94, 94), sf::Color(94, 94, 94))},
				{ MouseState::Pressed,ColorState(sf::Color(94, 94, 94), sf::Color(94, 94, 94), sf::Color(94, 94, 94))}};
		}

		/// <summary>
		///		Checks whether a color state using the specified state exists within this color scheme.
		/// </summary>
		/// <param name="p_state">The state.</param>
		/// <returns>Returns true if a color state exists.</returns>
		bool ContainColorState(MouseState p_state)
		{
			if(m_colors.empty())
			{
				LOG("This color scheme contains no color states!");
				return false;
			}

			m_it = m_colors.find(p_state);
			return m_it != m_colors.end();
		}

		/// <summary>
		///		Gets a color with a specified state. 
		/// </summary>
		/// <param name="p_state">The input state to get the color state from.</param>
		/// <returns>If found, returns a color. If not found returns default sf::color(White).</returns>
		const ColorState & GetColor(MouseState p_state)
		{
			if(ContainColorState (p_state ))
			{
				return m_it._Ptr->_Myval.second;
			}

			LOG("A color state with input state:" << p_state << " was not found!");
			return m_it._Ptr->_Myval.second;
		}

	private:
		std::unordered_map<MouseState, ColorState> m_colors;
		std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<const MouseState, ColorState>>>> m_it;

	};
}

