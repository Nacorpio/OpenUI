#include "stdafx.h"
#include "ElementComparer.h"
#include "Entities/Elements/Element.h"

namespace OpenUI
{
	bool ElementComparerDrawOrder::operator() ( const Element* lhs, const Element* rhs ) const
	{
		return lhs->GetDrawOrder () < rhs->GetDrawOrder ();
	}

	bool ElementComparerTree::operator() ( const Element* lhs, const Element* rhs ) const
	{
		if ( lhs->GetLevel () == rhs->GetLevel () )
		{
			return lhs->GetDrawOrder () < rhs->GetDrawOrder ();
		}

		return lhs->GetLevel () < rhs->GetLevel ();
	}
}
