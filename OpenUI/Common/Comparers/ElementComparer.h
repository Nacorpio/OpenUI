#pragma once

namespace OpenUI
{
	class Element;

	struct ElementComparerDrawOrder
	{
		bool operator () ( const Element* lhs, const Element* rhs ) const;
	};

	struct ElementComparerHeight
	{
		bool operator () (const Element* lhs, const Element* rhs) const;
	};
}
