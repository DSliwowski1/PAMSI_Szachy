#pragma once

#include "GLFW/glfw3.h"
#include <string>

class Image {
private:
	std::string FilePath;
	unsigned char* LocalBuffer;
	int  width, height, BPP;
public:
	Image(const std::string& path);
	Image() : FilePath(""), LocalBuffer(nullptr), width(0), height(0), BPP(0) {}
	~Image();
public:
	void Load(const std::string& path);
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	unsigned char* GetBuffer() { return LocalBuffer; }
};