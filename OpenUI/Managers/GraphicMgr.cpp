#include "stdafx.h"
#include "GraphicMgr.h"
#include "ElementMgr.h"
#include "../Entities/Elements/Element.h"

void GraphicMgr::Draw ()
{
	for ( Element* element : sElementMgr->GetElements () )
	{
		element->Draw ();
	}
}
