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

	enum class Detail
	{
		Panel,
		Button,
		Label
	};

	ObjectGuid ( const TypeId typeId, const Detail detail )
		: m_typeId ( typeId )
		, m_detail ( detail )
	{
	}

	ObjectGuid ( const ObjectGuid& other )
		: m_typeId ( other.m_typeId )
		, m_detail ( other.m_detail )
	{
	}

	TypeId GetTypeId () const
	{
		return m_typeId;
	}

	Detail GetDetail () const
	{
		return m_detail;
	}

	bool IsObject () const { return m_typeId == TypeId::Object; }
	bool IsElement () const { return m_typeId == TypeId::Element; }
	bool IsControl () const { return m_typeId == TypeId::Control; }

	bool IsPanel() const { return m_detail == Detail::Panel; }
	bool IsButton() const { return m_detail == Detail::Button; }
	bool IsLabel() const { return m_detail == Detail::Label; }

	bool operator == ( const ObjectGuid& rhs ) const
	{
		return m_typeId == rhs.m_typeId && m_detail == rhs.m_detail;
	}

	bool operator != ( const ObjectGuid& rhs ) const
	{
		return !( *this == rhs );
	}

private:
	TypeId m_typeId;
	Detail m_detail;
};
