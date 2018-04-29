#pragma once
#include <unordered_map>
#include "Common/Enums.h"
#include <SFML/Graphics/Color.hpp>
#include "Common/Constants.h"
#include <iostream>

namespace OpenUI
{

#define UN_ORD_COLOR_MAP(name) std::unordered_map<MouseState, sf::Color> * name
	struct ColorScheme
	{

		ColorScheme()
		{
			m_backColors = new std::unordered_map<MouseState, sf::Color>{
				{ MouseState::Entered,sf::Color::Red },
				{ MouseState::None,sf::Color::Blue },
				{ MouseState::Released,sf::Color::Blue },
				{ MouseState::Moved,sf::Color::Red },
				{ MouseState::Pressed,sf::Color::Green }};
		}

		ColorScheme(UN_ORD_COLOR_MAP(p_backColor), UN_ORD_COLOR_MAP(p_foreColor), UN_ORD_COLOR_MAP(p_outlineColor))
			: m_backColors(p_backColor), m_foreColors(p_foreColor), m_outlineColors(p_outlineColor)
		{
			
		}

		bool ContainColor(ColorType p_type, MouseState p_state)
		{
			switch (p_type) { 
				case ColorType::BackgroundColor:
					{
					m_it = m_backColors->find(p_state);
					return m_it != m_backColors->end();
					}
				case ColorType::ForegroundColor:
					{
					m_it = m_foreColors->find(p_state);
					return m_it != m_foreColors->end();
					}
				case ColorType::OutlineColor:
					{
					m_it = m_outlineColors->find(p_state);
					return m_it != m_outlineColors->end();
					}
				default: ;
			}
			return false;
		}

		sf::Color * GetColor(ColorType p_type,MouseState p_state) 
		{
			if(ContainColor ( p_type,p_state ))
			{
				return &m_it._Ptr->_Myval.second;
			}

			LOG("A color with state:" << p_state << " was not found!");
			return new sf::Color(255,255,255);
		}
		
	private:
		std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<const MouseState, sf::Color>>>> m_it;
		std::unordered_map<MouseState, sf::Color> * m_backColors = nullptr;
		std::unordered_map<MouseState, sf::Color> * m_foreColors = nullptr;
		std::unordered_map<MouseState, sf::Color> * m_outlineColors = nullptr;
	};
}

