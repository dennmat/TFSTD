#include "Core/Engine.h"
#include "Core/ShaderLoader.h"

#include "Core/LuaLoader.h"
#include "Core/LuaProgram.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

//Use nVidia Card
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

Core::Engine E;

void renderScene(void) {
	E.Render();
}

int main(int argc, char** argv) {

	E.SetProcess(Core::GameProcessInterface::ProcessType::Game);

	E.Load(argc, argv);
	
	glutDisplayFunc(renderScene);
	
	E.Start();

	return 0;
}