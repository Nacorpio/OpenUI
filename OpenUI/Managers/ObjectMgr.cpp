#include "stdafx.h"
#include "ObjectMgr.h"

Object* ObjectMgr::operator[] ( const uint64_t id )
{
	return m_mappedObjects[id];
}

void ObjectMgr::Add ( const uint64_t id, Object* obj )
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

bool ObjectMgr::Exists ( const uint64_t id ) const
{
	return m_mappedObjects.count ( id ) > 0;
}
