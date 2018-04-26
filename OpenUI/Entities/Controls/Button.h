#pragma once
#include "Control.h"

namespace OpenUI
{
	class Button : public Control
	{
	public:
		explicit Button ( const std::string& name );
		~Button ();

		void Start () override;
		void Initialize () override;
		void Update () override;
		void Draw () override;
	};
}
