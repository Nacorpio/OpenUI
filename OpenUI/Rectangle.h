#pragma once
#include <type_traits>
#include <cstdint>
#include <SFML/Graphics/Rect.hpp>
#include "Math/Vector2.h"

namespace OpenUI
{

	template < class _Ty, typename = std::enable_if_t <std::is_integral_v <_Ty>, _Ty> >
	struct Rectangle
	{
		union
		{
			struct { _Ty X, Y; };
			struct { Vector2<_Ty> Position;	};
		};

		union
		{
			struct { _Ty Width, Height; };
			struct { Vector2<_Ty> Size; };
		};

		Rectangle()
			: X(0),Y(0), Width(0), Height(0)
		{			
		}
		
		Rectangle(const _Ty p_x, const _Ty p_y, const _Ty p_width, const _Ty p_height)
			: X(p_x)
			, Y(p_y)
			, Width(p_width)
			, Height(p_height)
		{
		}

		explicit Rectangle(const sf::IntRect & p_sfIntRect)
			: X(p_sfIntRect.left)
			, Y(p_sfIntRect.top)
			, Width(p_sfIntRect.width)
			, Height(p_sfIntRect.height)
		{
		}

		bool Contains(const IntVector & p_value)
		{
			return X <= p_value.X && Y <= p_value.Y && X + Width >= p_value.X && Y + Height > - p_value.Y;
		}

		//bool Intersects(const Rectangle& p_rhs, Rectangle& p_intersection)
		//{
		//	Rectangle intersection;
		//	_Ty xIntersection = p_rhs.X - X;
		//	_Ty yIntersection = p_rhs.Y - Y;
		//	_Ty widthIntersection = p_rhs.Width - Width;
		//	_Ty heightIntersection = p_rhs.Height - Height;
		//}

		bool operator == (const Rectangle& rhs)
		{
			return X == rhs.X && Y == rhs.Y && Width == rhs.Width && Height == rhs.Height;
		}

		bool operator != (const Rectangle& rhs)
		{
			return !(*this == rhs);
		}

		bool operator > (const Rectangle& rhs)
		{
			return X > rhs.X && Y > rhs.Y && Width > rhs.Width && Height > rhs.Height;
		}

		bool operator < (const Rectangle& rhs)
		{
			return X < rhs.X && Y < rhs.Y && Width < rhs.Width && Height < rhs.Height;
		}

		bool operator >= (const Rectangle& rhs)
		{
			return X >= rhs.X && Y >= rhs.Y && Width >= rhs.Width && Height >= rhs.Height;
		}

		bool operator <= (const Rectangle& rhs)
		{
			return X <= rhs.X && Y <= rhs.Y && Width <= rhs.Width && Height <=rhs.Height;
		}

		Rectangle <_Ty>& operator ++ ()
		{
			++X;
			++Y;
			++Width;
			++Height;

			return *this;
		}

		Rectangle <_Ty>& operator -- ()
		{
			--X;
			--Y;
			--Width;
			--Height;

			return *this;
		}

		Rectangle <_Ty>& operator += (const _Ty rhs)
		{
			X += rhs;
			Y += rhs;
			Width += rhs;
			Height += rhs;

			return { X + rhs, Y + rhs, Width + rhs, Height + rhs};
		}

		Rectangle <_Ty>& operator -= (const _Ty rhs)
		{
			X -= rhs;
			Y -= rhs;
			Width -= rhs;
			Height -= rhs;

			return *this;
		}

		Rectangle <_Ty>& operator *= (const _Ty rhs)
		{
			X *= rhs;
			Y *= rhs;
			Width *= rhs;
			Height *= rhs;

			return *this;
		}

		Rectangle <_Ty>& operator /= (const _Ty rhs)
		{
			X /= rhs;
			Y /= rhs;
			Width /= rhs;
			Height /= rhs;

			return *this;
		}

		Rectangle <_Ty> operator + (const Rectangle <_Ty> & rhs)
		{
			return Rectangle <_Ty>(X + rhs.X, Y + rhs.Y, Width + rhs.Width, Height + rhs.Height);
		}

		Rectangle <_Ty> operator - (const Rectangle <_Ty> & rhs)
		{
			return Rectangle <_Ty>(X - rhs.X, Y - rhs.Y, Width - rhs.Width,Height - rhs.Height);
		}

		Rectangle <_Ty> operator * (const Rectangle <_Ty> & rhs)
		{
			return Rectangle <_Ty>(X * rhs.X, Y * rhs.Y, Width * rhs.Width, Height * rhs.Height);
		}

		Rectangle <_Ty> operator / (const Rectangle <_Ty> & rhs)
		{
			return Rectangle <_Ty>(X / rhs.X, Y / rhs.Y, Width / rhs.Width, Height / rhs.Height);
		}


	};
	typedef Rectangle <int32_t> IntRect;
	typedef Rectangle <uint32_t> UIntRect;

	struct ResizeInformation
	{
		ResizeInformation(IntRect & p_rectangle) : ResizedRectangle(p_rectangle)
		{
		}

		IntRect ResizedRectangle;
	};

	static IntRect & GetIntersection(const IntRect & p_container,IntRect & p_intersectingRectangle)
	{
		auto const containerBottom = p_container.Y + p_container.Height;
		auto const containerRight = p_container.X + p_container.Width;
		auto const interBottom = p_intersectingRectangle.Y + p_intersectingRectangle.Height;
		auto const interRight = p_intersectingRectangle.X + p_intersectingRectangle.Width;

		bool const intersectsBottom = interBottom > containerBottom;
		bool const intersectsTop = p_intersectingRectangle.Y < p_container.Y;
		bool const intersectsLeft = p_intersectingRectangle.X < p_container.X;
		bool const intersectsRight = interRight > containerRight;

		bool const resized = intersectsBottom || intersectsLeft || intersectsRight || intersectsTop;

		auto const topIntersection = p_intersectingRectangle.Y - p_container.Y;
		auto const bottomIntersection = containerBottom - interBottom;
		auto const leftIntersection = p_container.X - p_intersectingRectangle.X;
		auto const rightIntersection = containerRight - interRight;

		if (intersectsTop)
		{
			p_intersectingRectangle.Y = p_intersectingRectangle.Y - p_container.Y;
		}

		if (intersectsBottom)
		{
			p_intersectingRectangle.Height = containerBottom - interBottom;
		}

		if (intersectsLeft)
		{
			p_intersectingRectangle.X = p_container.X - p_intersectingRectangle.X;
		}

		if (intersectsRight)
		{
			p_intersectingRectangle.Width = containerRight - interRight;
		}

		return p_intersectingRectangle;
	}

	/* Resizes a p_rectangle to fit inside another p_rectangle*/
	static ResizeInformation * ResizeToFit(IntRect & p_resizingRectangle, IntRect & p_rectangleToFit)
	{
		auto const rectangleToFitBottom = p_rectangleToFit.Y + p_rectangleToFit.Height;
		auto const rectangleToFitRight = p_rectangleToFit.X + p_rectangleToFit.Width;
		auto const resizingRectangleBottom = p_resizingRectangle.Y + p_resizingRectangle.Height;
		auto const resizingRectangleRight = p_resizingRectangle.X + p_resizingRectangle.Width;

		bool const intersectsBottom = resizingRectangleBottom > rectangleToFitBottom;
		bool const intersectsTop = p_resizingRectangle.Y < p_rectangleToFit.Y;
		bool const intersectsLeft = p_resizingRectangle.X < p_rectangleToFit.X;
		bool const intersectsRight = resizingRectangleRight > rectangleToFitRight;

		bool const resized = intersectsBottom || intersectsLeft || intersectsRight || intersectsTop;

		

		if (intersectsTop)
		{
			p_resizingRectangle.Y = p_rectangleToFit.Y;
			p_resizingRectangle.Height = rectangleToFitBottom - p_resizingRectangle.Y;
		}

		if (intersectsBottom)
		{
			p_resizingRectangle.Height = rectangleToFitBottom - p_resizingRectangle.Y;
		}

		if (intersectsLeft)
		{
			p_resizingRectangle.X = p_rectangleToFit.X;
			p_resizingRectangle.Width -= p_rectangleToFit.X;
		}

		if (intersectsRight)
		{
			p_resizingRectangle.Width = rectangleToFitRight - p_resizingRectangle.X;
		}

		return new ResizeInformation(p_resizingRectangle);
	}
}


