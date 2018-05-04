#include "stdafx.h"
#include "ElementComparer.h"
#include "Entities/Elements/Element.h"

namespace OpenUI
{
	bool ElementComparerDrawOrder::operator() ( const Element* lhs, const Element* rhs ) const
	{
		return lhs->GetDrawOrder () < rhs->GetDrawOrder ();
	}

	bool ElementComparerHeight::operator() ( const Element* lhs, const Element* rhs ) const
	{
		return lhs->GetHeight () > rhs->GetHeight ();
	}
}
