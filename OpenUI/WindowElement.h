#pragma once
#include "Entities/Elements/Element.h"

namespace OpenUI
{
	class WindowElement : public OpenUI::Element
	{
	public:
		WindowElement(const std::string& p_name, const uint16_t & p_headerSize);
		~WindowElement();

	protected:
		void OnMouseClick ( const sf::Event::MouseButtonEvent & event ) override;

	public:
		void Start () const override;

		void Initialize () override;

		void Update ( const OpenUI::UpdateContext & p_updateContext ) override;

		void OnBoundsChanged ( OpenUI::IntRect & p_delta ) override;

		void Draw ( const OpenUI::GraphicsContext & gContext ) override;

		void OnMouseDown ( const sf::Event::MouseButtonEvent & event ) override;

		void OnMouseUp ( const sf::Event::MouseButtonEvent & event ) override;

		void OnChildAdded ( Element & child ) override;

	private:
		uint16_t m_headerSize = 30;
	};

	
}
