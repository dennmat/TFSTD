#pragma once

#include "ShaderLoader.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

namespace Core {
	class GameProcessInterface {
	public:
		enum ProcessState {
			PreInit = 0,
			Initialized,
			Loading,
			Ready,
			Destroying,
			Destroyed
		};

		enum ProcessType {
			MainMenu = 0,
			Game,
			Pause
		};

		ProcessState state;
		ProcessType type;

		virtual void PreLoad(void) = 0;
		virtual void Load(void) = 0;
		virtual void Render(void) = 0;
		virtual void Update(void) = 0;
		virtual void Destroy(void) = 0;
		virtual void Event(void) = 0;
	};

	/*class BaseMenuProcess : GameProcessInterface {
	public:
		BaseMenuProcess();
		virtual ~BaseMenuProcess();

		virtual void PreLoad(void);
		virtual void Load(void);
		virtual void Render(void);
		virtual void Update(void);
		virtual void Destroy(void);
		virtual void Event(void);
	};*/

	class GameProcess : GameProcessInterface {
	private:
		GLuint program;

	public:
		GameProcess();
		virtual ~GameProcess();

		virtual void PreLoad(void);
		virtual void Load(void);
		virtual void Render(void);
		virtual void Update(void);
		virtual void Destroy(void);
		virtual void Event(void);
	};
}