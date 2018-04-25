#include "stdafx.h"
#include "ElementMgr.h"
#include "../Entities/Elements/Element.h"

Element* ElementMgr::operator[] ( const uint64_t id )
{
	return m_mappedObjects[id];
}

void ElementMgr::Add ( const uint64_t id, Element* obj )
{
	if ( !obj )
	{
		return;
	}

	if ( Exists ( id ) )
	{
		return;
	}

	m_objects.insert ( m_objects.end (), obj );
	m_mappedObjects.insert_or_assign ( id, obj );
}

bool ElementMgr::Exists ( const uint64_t id ) const
{
	return m_mappedObjects.count ( id ) > 0;
}
