#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "SFML/Window/Event.hpp"
#include "Common/Constants.h"
#include "Entities/Elements/Element.h"

namespace OpenUI
{
	struct RenderWindowSettings final
	{
		sf::VideoMode VideoMode = sf::VideoMode ( GLOBAL_RENDER_WINDOW_SIZE.X, GLOBAL_RENDER_WINDOW_SIZE.Y );
		sf::String Title = GLOBAL_WINDOW_TITLE;
		sf::Uint32 Style = sf::Style::Default;
		sf::ContextSettings ContextSettings = sf::ContextSettings ( 0, 0, 8 );

		RenderWindowSettings () = default;

		RenderWindowSettings (
			sf::VideoMode& p_videoMode,
			const sf::Uint32 p_style,
			sf::ContextSettings& p_contextSettings )
			: VideoMode ( p_videoMode )
			, Style ( p_style )
			, ContextSettings ( p_contextSettings )
		{
		}
	};

	class ClientWindow : public Element
	{
	public:
		explicit ClientWindow ( const std::string& name, const RenderWindowSettings& windowSettings );
		~ClientWindow ();

		void Start () override;
		void Initialize () override;
		void Update () override;
		void Draw ( const GraphicsContext& gContext ) override;

		sf::RenderWindow& GetRenderWindow () const;

	private:
		friend class Element;

		std::set<Element*> m_descendants { };
		sf::RenderWindow* m_renderWindow { };
	};
}
