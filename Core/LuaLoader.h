#pragma once

#include "types.h"
#include "LuaProgram.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace Core {
	class LuaLoader {
	private:
		std::ofstream CurrentFileHandle;

		std::string ReadScript(char* fileName);

		bool NeedsRecompile(char* fileName);
		bool CompileToByteCode(char* fileName);

		std::string GetCompiledFileName(std::string);
	public:
		static std::vector<LuaProgram> LuaPrograms;

		bool WriteChunk(const void* data, size_t size);

		TFSint LoadProgram(char* fileName);

		LuaLoader(void);
		~LuaLoader(void); 
	};
}