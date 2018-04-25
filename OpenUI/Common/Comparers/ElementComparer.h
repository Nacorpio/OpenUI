#pragma once

class Element;

struct ElementComparer
{
	bool operator () ( const Element* lhs, const Element* rhs ) const;
};

