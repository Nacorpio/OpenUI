#pragma once
#include "Entities/Elements/Element.h"

namespace OpenUI
{
	class Control : public Element
	{
	public:
		explicit Control ( const std::string& name );

		void Initialize () override;
		void Update () override;
		void Draw ( const GraphicsContext& gContext ) override;
	};
}
