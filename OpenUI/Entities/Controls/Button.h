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

		void Start () const override;
		void Initialize () override;

		void Update (const UpdateContext & p_updateContext) override;
		void Draw ( const GraphicsContext & gContext ) override;

		void OnMouseEnter () override;
		void OnMouseLeave() override;
		void OnMouseMove() override;
		void OnMouseHover () override;

		void OnMouseUp( const sf::Event::MouseButtonEvent& event) override;
		void OnMouseDown( const sf::Event::MouseButtonEvent& event) override;

		void OnMouseClick (const sf::Event::MouseButtonEvent& event ) override;
		void OnMouseDoubleClick ( const sf::Event::MouseButtonEvent& event ) override;

		void OnDrop (const InputHandler::MouseDropEvent& event) override;
		void OnDragDrop ( const InputHandler::MouseDragDropEvent& ) override;
		void OnDragBegin () override;
	};
}
