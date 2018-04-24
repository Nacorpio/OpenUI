#pragma once

#include "ObjectGuid.h"

class Object
{
public:
	Object ();
	~Object ();

	ObjectGuid& GetGuid () { return m_guid; }

protected:
	ObjectGuid m_guid;
};
