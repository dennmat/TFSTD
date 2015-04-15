#include "LuaLoader.h"

#include <fstream>
#include <iostream>

#include <Windows.h>

using namespace Core;

LuaLoader::LuaLoader(void) {}
LuaLoader::~LuaLoader(void) {
	if (this->CurrentFileHandle.is_open())  {
		this->CurrentFileHandle.close();
	}
}

std::string LuaLoader::ReadScript(char * fileName) {
	std::string scriptCode;
	std::ifstream file(fileName, std::ios::in);

	if (!file.good()) {
		std::cout << "Can't load script " << fileName << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	scriptCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&scriptCode[0], scriptCode.size());
	file.close();

	return scriptCode;
}

std::string LuaLoader::GetCompiledFileName(std::string fileName) {
	std::string result;

	result = fileName.substr(0, fileName.size() - 4); //strip .lua
	result += ".tfsb"; //add custom extension

	return result;
}

bool LuaLoader::NeedsRecompile(char * fileName) {
	WIN32_FIND_DATAA findData;
	HANDLE fileResult;
	
	WIN32_FIND_DATAA compiledFindData;
	HANDLE compiledFileResult;

	LPCWSTR longFileName = LPCWSTR(fileName);
	std::string compiledFileName = this->GetCompiledFileName(std::string(fileName)).c_str();
	
	fileResult = FindFirstFileA(fileName, &findData);
	
	if (fileResult == INVALID_HANDLE_VALUE) {
		std::cout << "Invalid file handle for script: " << fileName << std::endl;
		std::terminate();
	}
	
	compiledFileResult = FindFirstFileA(compiledFileName.c_str(), &compiledFindData);
	
	if (compiledFileResult == INVALID_HANDLE_VALUE) {
		return true;
	}
	
	return (CompareFileTime(&findData.ftLastWriteTime, &compiledFindData.ftLastWriteTime) > 0);
}

//Callback for lua dump
int luaDumpCallback(lua_State *L, const void* p, size_t sz, void* ud) {
	LuaLoader* loader = (LuaLoader*)ud;

	if (!loader->WriteChunk(p, sz)) {
		return 1;
	}

	return 0;
}

bool LuaLoader::WriteChunk(const void* p, size_t sz) {
	if (!this->CurrentFileHandle.is_open()) {
		return false; //This isn't good
	}

	this->CurrentFileHandle.write((const char*)p, sz);

	return true;
}

bool LuaLoader::CompileToByteCode(char * fileName) {
	std::string compiledFileName = this->GetCompiledFileName(std::string(fileName));

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_loadfile(L, fileName);

	this->CurrentFileHandle = std::ofstream(compiledFileName, std::ofstream::binary);

	lua_dump(L, luaDumpCallback, (void *)this, true);

	this->CurrentFileHandle.close();

	lua_close(L);

	return true;
}

TFSint LuaLoader::LoadProgram(char * fileName) {
	LuaProgram program;
	
	if (this->NeedsRecompile(fileName)) {
		this->CompileToByteCode(fileName);
	}
	
	std::string compiledFileName = this->GetCompiledFileName(std::string(fileName));
	
	lua_State* L = luaL_newstate();
	
	luaL_openlibs(L);
	
	luaL_loadfile(L, compiledFileName.c_str());
	
	lua_close(L);

	return 0;
}