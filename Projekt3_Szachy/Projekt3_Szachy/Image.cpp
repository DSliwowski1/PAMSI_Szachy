#include "Image.h"

#include "stb_image.h"

Image::Image(const std::string & path) :
	 FilePath(path), LocalBuffer(nullptr), width(0), height(0), BPP(0)
{
//	stbi_set_flip_vertically_on_load(1); //Nale�y odwr�cic "teksture do g�ry nogami" aby wy�wietla�a sie prawid�owo
	LocalBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4); //�adujemy plik

}

Image::~Image()
{
	if (LocalBuffer)
		stbi_image_free(LocalBuffer); //Zwalniamy buffer z CPU
//	glDeleteTextures(1, &RendererID); //Zwolnienie tekstury z karty graficznej
}

void Image::Load(const std::string & path)
{
	FilePath = path;
//	stbi_set_flip_vertically_on_load(1); //Nale�y odwr�cic "teksture do g�ry nogami" aby wy�wietla�a sie prawid�owo
	LocalBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4); //�adujemy plik
}