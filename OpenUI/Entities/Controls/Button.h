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

		void Start() const override;
		void Initialize() override;

	protected:
		void Update () override;
		void Draw ( const GraphicsContext& gContext ) override;

		void OnMouseEnter () override;
		void OnMouseLeave () override;
		void OnMouseMove () override;
		void OnMouseHover () override;

		void OnMouseUp () override;
		void OnMouseDown () override;
		void OnMouseClick () override;
		void OnMouseDoubleClick () override;

		void OnDrop ( const InputHandler::MouseDropEvent& event ) override;
		void OnDragDrop ( const InputHandler::MouseDragDropEvent& ) override;
		void OnDragBegin () override;

		void OnAscendingEvent ( const sf::Event& event ) override;
	};
}
