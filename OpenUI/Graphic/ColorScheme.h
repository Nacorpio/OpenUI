#pragma once
#include <unordered_map>
#include "Common/Enums.h"
#include <SFML/Graphics/Color.hpp>

namespace OpenUI
{
	struct ColorState
	{
		sf::Color BackColor;
		sf::Color ForeColor;
		sf::Color OutlineColor;

		ColorState ( const sf::Color & p_backColor, const sf::Color & p_foreColor, const sf::Color & p_outlineColor );
	};

	struct ColorScheme
	{
		const ColorState& operator [] ( MouseState p_state );

		ColorScheme ();

		/// <summary>
		///		Checks whether a color state using the specified state exists within this color scheme.
		/// </summary>
		/// <param name="p_state">The state.</param>
		/// <returns>Returns true if a color state exists.</returns>
		bool ContainColorState ( MouseState p_state );

		/// <summary>
		///		Gets a color with a specified state. 
		/// </summary>
		/// <param name="p_state">The input state to get the color state from.</param>
		/// <returns>If found, returns a color. If not found returns default sf::color(White).</returns>
		const ColorState& GetColor ( const MouseState p_state );

	private:
		std::unordered_map<MouseState, ColorState> m_colors;
		std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<const MouseState, ColorState>>>> m_it;

	};
}

