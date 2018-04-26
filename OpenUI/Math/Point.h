#pragma once
#include <type_traits>
#include "SFML/System/Vector2.hpp"

namespace OpenUI
{
	template < class T, typename = std::enable_if_t <std::is_arithmetic_v <T>, T> >
	struct Point
	{
		T X, Y;

		sf::Vector2i ToVector() const
		{
			return sf::Vector2i(X, Y);
		}

		Point()
			: X(0)
			, Y(0)
		{
		}

		Point(const T p_x, const T p_y)
			: X(p_x)
			, Y(p_y)
		{
		}

		Point(const Point& p_other)
			: X(p_other.X)
			, Y(p_other.Y)
		{
		}

		bool operator == (Point p_other) const
		{
			return X == p_other.X & Y == p_other.Y;
		}

		bool operator != (Point p_other) const
		{
			return !(*this == p_other);
		}
	};
}
