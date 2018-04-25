#pragma once

#include <string>
#include <vector>
#include "../Objects/Object.h"
#include "../../Structures.h"

class Element : public Object
{
protected:
	~Element () = default;

public:
	explicit Element (const std::string& name)
		: m_name ( name )
	{
	}

	const std::string& GetName () const { return m_name; }
	Element* GetParent () const { return m_parent; }
	uint16_t GetDrawOrder () const { return m_drawOrder; }

	void SetParent(Element* element);

	void AddChild ( Element* element );
	void RemoveChild ( Element* element );
	bool HasChild ( const Element* element );

	virtual void Initialize () = 0;
	virtual void Update () = 0;

	virtual void Draw () {}

	virtual void OnChildAdded ( const Element& child ) {}
	virtual void OnChildRemoved ( const Element& child ) {}

	bool operator == ( const Element& rhs ) const;
	bool operator != ( const Element& rhs ) const;

protected:
	void SetDrawOrder ( uint16_t value );

private:
	void Sort() const;

	const std::string m_name = "Element";

	uint16_t m_drawOrder = 0;
	std::vector <Element*> m_children { };
	OpenUI::IntVector m_position { };
	Element* m_parent = nullptr;
};
