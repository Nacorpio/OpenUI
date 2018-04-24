#pragma once

#include "../Objects/Object.h"
#include <string>

class Element : public Object
{
protected:
	~Element () = default;

public:
	explicit Element () = default;

	void SetName ( const std::string& name ) { m_name = name; }
	std::string& GetName () { return m_name; }

	virtual void Initialize () = 0;
	virtual void Update () = 0;
	virtual void Draw () = 0;

	bool operator == ( const Element& rhs ) const
	{
		return m_name == rhs.m_name;
	}

	bool operator != ( const Element& rhs ) const
	{
		return !( *this == rhs );
	}

private:
	std::string m_name = "Element";
};
