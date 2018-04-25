#pragma once
#include "Control.h"

class Button : public Control
{
public:
	explicit Button ( const std::string& name );
	~Button ();

	void Initialize () override;
	void Update () override;
	void Draw () override;
};
