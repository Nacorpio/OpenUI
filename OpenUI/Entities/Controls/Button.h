#pragma once
#include "Control.h"

class Button : public Control
{
public:
	Button ();
	~Button ();

	void Initialize () override;
	void Update () override;
	void Draw () override;
};
