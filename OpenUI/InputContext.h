#pragma once
#include "Common/Comparers/ElementComparer.h"
#include <set>
#include "Math/Vector2.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace OpenUI
{
	struct InputContext
	{
		
		Element * ActiveElement = nullptr;
		Element * HighestElement = nullptr;
		IntVector MousePosition;
		sf::Event & SfEvent;


		/// <summary>
		///		Pools the event to be used with input handling from a specified render window.
		/// </summary>
		/// <param name="p_renderWindow"></param>
		void PoolEvent(sf::RenderWindow & p_renderWindow) const
		{
			p_renderWindow.pollEvent(SfEvent);
		}

	private:
		std::set <Element*, ElementComparerHeight> m_hoveredElements;

		Element * GetHighestElement() const
		{
			if (m_hoveredElements.size() > 0)
			{
				return m_hoveredElements.begin()._Ptr->_Myval;
			}
			return nullptr;
		}

		
	};
}

