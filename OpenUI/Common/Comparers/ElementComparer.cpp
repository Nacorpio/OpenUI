#include "stdafx.h"
#include "ElementComparer.h"
#include "Entities/Elements/Element.h"

namespace OpenUI
{
	bool ElementComparer::operator() ( const Element* lhs, const Element* rhs ) const
	{
		return lhs->GetDrawOrder () < rhs->GetDrawOrder ();
	}
}
