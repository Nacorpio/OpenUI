#pragma once

#include "ObjectGuid.h"

class Object
{
public:
	Object ();

protected:
	~Object ();

public:
	ObjectGuid& GetGuid () { return m_guid; }

protected:
	ObjectGuid m_guid;
};
