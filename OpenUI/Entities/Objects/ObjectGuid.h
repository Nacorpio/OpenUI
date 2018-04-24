#pragma once
class ObjectGuid
{
public:
	enum class TypeId
	{
		Object,
		Element,
		Control
	};

	enum class Low
	{
		Panel,
		Button,
		Label
	};

	ObjectGuid ( const TypeId typeId, const Low low )
		: m_typeId ( typeId )
		, m_low ( low )
	{
	}

	ObjectGuid ( const ObjectGuid& other )
		: m_typeId ( other.m_typeId )
		, m_low ( other.m_low )
	{
	}

	bool operator == ( const ObjectGuid& rhs ) const
	{
		return m_typeId == rhs.m_typeId && m_low == rhs.m_low;
	}

	bool operator != ( const ObjectGuid& rhs ) const
	{
		return !( *this == rhs );
	}

	TypeId GetTypeId () const
	{
		return m_typeId;
	}

	Low GetLow () const
	{
		return m_low;
	}

private:
	TypeId m_typeId;
	Low m_low;
};
