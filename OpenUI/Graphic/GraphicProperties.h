#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "Common/Enums.h"

namespace OpenUI
{
	/// <summary>
	///		Defines the distance the inheriting object should position its children located away from itself.
	/// </summary>
	struct Padding
	{
		union
		{
			struct
			{
				int Left;
				int Right;
				int Top;
				int Bottom;
			};

			int Values[4];
		};

		Padding () = default;

		explicit Padding ( const int left, const int right, const int top, const int bottom )
			: Left ( left )
			, Right ( right )
			, Top ( top )
			, Bottom ( bottom )
		{
		}

		bool operator == ( const Padding& rhs ) const
		{
			return Left == rhs.Left && Right == rhs.Right && Top == rhs.Top && Bottom == rhs.Bottom;
		}

		bool operator != ( const Padding& rhs ) const
		{
			return !( *this == rhs );
		}
	};

	/// <summary>
	///		Defines the edges of a child that will meet its parent edges
	/// </summary>
	struct Docking
	{
		struct DockStyleChangedInfo
		{
			DockStyleChangedInfo (
				sf::IntRect& p_childRectangle,
				sf::IntRect& p_parrentRectangle,
				sf::IntRect& p_childRectangleChanged,
				const DockStyle p_dockStyle )
				: ChildRectangle ( p_childRectangle )
				, ChildRectangleChanged ( p_childRectangleChanged )
				, ParentRectangle ( p_parrentRectangle )
				, DockStyleUsed ( p_dockStyle )
			{
			}

			sf::IntRect& ChildRectangle;
			sf::IntRect& ChildRectangleChanged;
			sf::IntRect& ParentRectangle;

			DockStyle DockStyleUsed;
		};

		/// <summary>
		///		Calculates the change in a child's bounds if a child was to dock with a parent using the specified dock-style. 
		/// </summary>
		/// <param name="p_parentBounds">The parent's bounds</param>
		/// <param name="p_childBounds">The child's bounds</param>
		/// <returns>Docking data</returns>
		static DockStyleChangedInfo CalculateDock (
			const DockStyle p_dockStyle,
			sf::IntRect& p_parentBounds,
			sf::IntRect& p_childBounds )
		{
			sf::IntRect childBoundsChanged = p_childBounds;

			switch ( p_dockStyle )
			{
				case DockStyle::Left :
				{
					childBoundsChanged.left = p_parentBounds.left;
					childBoundsChanged.top = p_parentBounds.top;
					childBoundsChanged.height = p_parentBounds.height;
					break;
				}

				case DockStyle::Right :
				{
					childBoundsChanged.left = p_parentBounds.left + p_parentBounds.width - p_childBounds.width;
					childBoundsChanged.top = p_parentBounds.top;
					childBoundsChanged.height = p_parentBounds.height;
					break;
				}

				case DockStyle::Top :
				{
					childBoundsChanged.left = p_parentBounds.left;
					childBoundsChanged.top = p_parentBounds.top;
					childBoundsChanged.width = p_parentBounds.width;
					break;
				}

				case DockStyle::Bottom :
				{
					childBoundsChanged.left = p_parentBounds.left;
					childBoundsChanged.top = p_parentBounds.top + p_parentBounds.height - p_childBounds.height;
					childBoundsChanged.width = p_parentBounds.width;
					break;
				}

				case DockStyle::Filled :
				{
					childBoundsChanged = p_parentBounds;
					break;
				}

				case DockStyle::None : break;
				default : break;
			}

			return DockStyleChangedInfo ( p_childBounds, p_parentBounds, childBoundsChanged, p_dockStyle );
		}
	};
}
