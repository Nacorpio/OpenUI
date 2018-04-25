#include "stdafx.h"
#include "GraphicMgr.h"
#include "ElementMgr.h"
#include "../Entities/Elements/Element.h"

void GraphicMgr::Draw ()
{
	for ( auto it = sElementMgr->GetElements ().begin () ; it != sElementMgr->GetElements ().end () ; ++it )
	{
		it._Ptr->_Myval->Draw ();
	}
}
