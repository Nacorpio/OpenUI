#pragma once
#include "../Elements/Element.h"

class Control : public Element
{
public:
	explicit Control ( const std::string& name );

	void Initialize () override;
	void Update () override;
	void Draw () override;
};
