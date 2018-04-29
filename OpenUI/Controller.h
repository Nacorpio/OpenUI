#pragma once
#include "Entities/Elements/Windows/ClientWindow.h"
#include "Managers/ElementMgr.h"
#include "Managers/StateManager.h"
#include "InputContext.h"
#include <iso646.h>

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
			StartAndInitWindows();
			InputAndUpdateWindows();
			ProgramLoop();
		}

		std::set <ClientWindow*> & GetClientWindows() const
		{
			return *m_clientWindows;
		}

	private:

		void ProgramLoop() const
		{
			sf::Clock clock;
			static const int ticksPerSecond = 60;
			const int skipTicks = 1000 / ticksPerSecond;
			const int maxFrameSkips = 10;

			int nextTick = clock.getElapsedTime().asMilliseconds();
			int elapsedTime = 0;
			int loops = 0;
			long previousUpdate = 1, currentUpdate = 1, delta = 0,previousFPSUpdate = 0, nextFPSUpdate = nextTick + 1000;
			float interpolation = 0;

			double frames = 0;
			double frameTime = 0;
			const bool enablePerformanceProfiler = false;

			while (true)
			{
				elapsedTime = clock.getElapsedTime().asMilliseconds();

				loops = 0;

				while (elapsedTime > nextTick && loops < maxFrameSkips)
				{
					InputAndUpdateWindows();
					nextTick += skipTicks;
					++loops;
				}

				previousUpdate = currentUpdate;
				currentUpdate = elapsedTime;

				DrawWindows();

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
		///		Starts and initializes the windows which will start and initialize the elements.
		/// </summary>
		void StartAndInitWindows() const
		{
			ClientWindow * clientWindow = nullptr;
			for (auto it = m_clientWindows->begin(); it != m_clientWindows->end(); ++it)
			{
				clientWindow = it._Ptr->_Myval;
				clientWindow->Start();
				clientWindow->Initialize();
			}
		}

		/// <summary>
		///		Input and update the clientwindow(s).
		/// </summary>
		void InputAndUpdateWindows() const
		{
			ClientWindow * clientWindow = nullptr;
			for (auto it = m_clientWindows->begin(); it != m_clientWindows->end(); ++it)
			{
				clientWindow = it._Ptr->_Myval;
				clientWindow->Input();
				clientWindow->Update();
			}
		}

		void DrawWindows() const
		{
			ClientWindow * clientWindow = nullptr;
			for (auto it = m_clientWindows->begin(); it != m_clientWindows->end(); ++it)
			{
				clientWindow = it._Ptr->_Myval;
				clientWindow->Draw(*m_graphicsContext);
			}
		}

		std::set <ClientWindow*> * m_clientWindows = nullptr;
		GraphicsContext* m_graphicsContext = nullptr;
	};
	
}
#define sController OpenUI::Controller::instance()
