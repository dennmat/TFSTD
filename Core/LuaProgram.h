#pragma once

#include "types.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <string>

namespace Core {
	class LuaProgram {
	private:
		std::string compiledFileName;
		lua_State* L;

	public:
		LuaProgram(void);
		~LuaProgram(void);

		void InitializeProgram(std::string compiledFileName);

		void Run();

		TFSint GetIntFromLua(std::string name);
		std::string GetStrFromLua(std::string name);
		bool GetBoolFromLua(std::string name);
		double GetDoubleFromLua(std::string name);
	};
}