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

		virtual void Start () override;

		virtual void Initialize () override;

		virtual void Update () override;

		virtual void Draw ( const GraphicsContext & gContext ) override;

		void OnMouseEnter () override;
		void OnMouseLeave() override;

		void OnMouseMove() override;

		void OnMouseHover () override;

		void OnMouseDown () override;

		void OnMouseUp () override;

		void OnMouseClick () override;
	};
}
