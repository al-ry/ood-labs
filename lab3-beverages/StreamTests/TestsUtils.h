#include "stdafx.h"

inline std::string GetFileContent(const std::string& fileName)
{
	std::ifstream istream;
	istream.open(fileName, std::ios::binary);
	//istream.seekg(0, istream.end);
	//auto len = istream.tellg();
	//istream.seekg(0, istream.beg);
	//char* buffer = (char*)malloc(len * sizeof(char));
	//istream.read(buffer, 1);
	//std::string copyOfStream(buffer);
	//free(buffer);
	//return copyOfStream;
	return std::string((std::istreambuf_iterator<char>(istream)), (std::istreambuf_iterator<char>()));
}


inline std::vector<uint8_t> PushIdenticalSymbolsToArray(size_t size, uint8_t byte)
{
	std::vector<uint8_t> arr;
	for (size_t i = 0; i < size; i++)
	{
		arr.push_back(byte);
	}
	return arr;
}