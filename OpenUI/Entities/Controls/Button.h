#pragma once
#include "Entities/Elements/Element.h"

namespace OpenUI
{
	class GraphicsContext;

	class Button : public Element
	{
	public:
		explicit Button ( const std::string& name );
		~Button ();

		void Start () override;
		void Initialize () override;
		void Update () override;
		void Draw ( const GraphicsContext& gContext ) override
		{
			Element::Draw(gContext);
		}


		void OnMouseEnter () override
		{
			Control::OnMouseEnter();
		}

		void OnMouseHover () override
		{
			Control::OnMouseHover();
		}

		void OnMouseDown () override
		{
			Control::OnMouseDown();
		}

		void OnMouseUp () override
		{
			Control::OnMouseUp();
		}

		void OnMouseClick () override
		{
			Control::OnMouseClick();
		}
	};
}
