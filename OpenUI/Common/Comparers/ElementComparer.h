#pragma once

namespace OpenUI
{
	class Element;

	struct ElementComparer
	{
		bool operator () ( const Element* lhs, const Element* rhs ) const;
	};
}
