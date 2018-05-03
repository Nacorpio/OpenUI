#pragma once
#include "Entities/Elements/Windows/ClientWindow.h"
#include "Managers/ElementMgr.h"
#include "Common/Constants.h"
#include <iostream>
#include "Contexts.h"


namespace OpenUI
{
	class Controller
	{
	public:
		static Controller* instance()
		{
			static Controller instance;
			return &instance;
		}

		void Start()
		{
			m_clientWindows = &sElementMgr->m_clientWindows;

			// Starts the elements after they've been initialized.
			ClientWindow * clientWindow = nullptr;
			for (auto it = m_clientWindows->begin(); it != m_clientWindows->end(); ++it)
			{
				clientWindow = it._Ptr->_Myval;
				clientWindow->Start();
			}

			ProgramLoop();
		}

		std::set <ClientWindow*>::iterator GetClientWindows() const
		{
			return m_clientWindows->begin ();
		}

	private:
		UpdateContext m_updateContext;
		
		void ProgramLoop()
		{
			sf::Clock clock;

			static const int ticksPerSecond = 60;
			static const int skipTicks = 1000 / ticksPerSecond;
			static const int maxFrameSkips = 10;

			int nextTick = clock.getElapsedTime().asMilliseconds();
			int elapsedTime = 0;
			int loops = 0;
			long previousUpdate = 1, currentUpdate = 1, delta = 0,previousFPSUpdate = 0, nextFPSUpdate = nextTick + 1000;
			float interpolation = 0;

			static const bool enablePerformanceProfiler = false;
			static double frames = 0;
			static double frameTime = 0;

			while (true)
			{
				elapsedTime = clock.getElapsedTime().asMilliseconds();
				loops = 0;

				while (elapsedTime > nextTick && loops < maxFrameSkips)
				{
					m_updateContext.Delta = delta;
					m_updateContext.ElapsedTime = elapsedTime;
					Update();

					nextTick += skipTicks;
					++loops;
				}

				previousUpdate = currentUpdate;
				currentUpdate = elapsedTime;

				delta = currentUpdate - previousUpdate;

				Draw();

				if(enablePerformanceProfiler)
				{
					if (currentUpdate > nextFPSUpdate)
					{
						frameTime = 1000 / (frames);
						LOG("Frames: " << frames << " frameTime: " << frameTime << " SkipTicks: " << skipTicks << " loops: " << loops);
						frames = 0;
						nextFPSUpdate = currentUpdate + 1000;
					}
					++frames;
				}
			}
			
		}

		/// <summary>
		///		Input and update the client window(s).
		/// </summary>
		void Update() 
		{
			ClientWindow * clientWindow = nullptr;
			for (auto it = m_clientWindows->begin(); it != m_clientWindows->end(); ++it)
			{
				clientWindow = it._Ptr->_Myval;
				clientWindow->Input();
				clientWindow->Update(m_updateContext);
			}
		}

		void Draw() const
		{
			ClientWindow * clientWindow = nullptr;
			for (auto it = m_clientWindows->begin(); it != m_clientWindows->end(); ++it)
			{
				clientWindow = it._Ptr->_Myval;
				clientWindow->Draw(*m_graphicsContext);
			}
		}

		std::set <ClientWindow*> * m_clientWindows;
		GraphicsContext* m_graphicsContext;


	};
	
}
#define sController OpenUI::Controller::instance()
