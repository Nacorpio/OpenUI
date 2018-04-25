#pragma once

#include "ObjectGuid.h"

class Object
{
public:
	virtual ~Object () = default;

	Object ()
		: m_guid ( ObjectGuid::TypeId::Object, ObjectGuid::Detail::None )
	{
	}

	ObjectGuid& GetGuid () { return m_guid; }

protected:
	ObjectGuid m_guid;
};
