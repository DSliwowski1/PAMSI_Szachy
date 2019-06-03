#include "Graphic.h"

void Graphic::DrawLine(int x1, int y1, int x2, int y2)
{
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}

//void Graphic::DrawCircle(int x, int y, int r)
//{
//}

void Graphic::DrawRec(int x, int y, int width, int height)
{
	glBegin(GL_QUADS);
	glVertex2i(x - width / 2, y - height / 2);
	glVertex2i(x + width / 2, y - height / 2);
	glVertex2i(x + width / 2, y + height / 2);
	glVertex2i(x - width / 2, y + height / 2);
	glEnd();
}

void Graphic::DrawPolygon(Point * arr, int size)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < size; ++i)
	{
		glVertex2i(arr[i].GetX(), arr[i].GetY());
	}
	glEnd();
}

void Graphic::DrawImage(Image &img, int x, int y)
{
	GLuint tex;
	glGenTextures(1, &tex); //Tworzymy teksture pod RenderedID
	glBindTexture(GL_TEXTURE_2D, tex);  //Powiazujemy nasza teksture z typem 2D

	//Parametry tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //W momencie nalkadania obarzu na mniejszy kwadrat, tekstuare bedzie skaoana liniowo
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //W momencie nalkadania obarzu na wiêkszy kwadrat, tekstuare bedzie skaoana liniowo
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); //Nie chcemy aby obraz powieszkal pole wzdluz x
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); //Nie chcemy aby obraz powieszkal pole  wzdluz y

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img.GetWidth(), img.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.GetBuffer()); //Przes³anie obrazu do karty graficznej
	glBindTexture(GL_TEXTURE_2D, 0);  //Powiazujemy nasza teksture z typem 2D

	glBindTexture(GL_TEXTURE_2D, tex);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex2i(x - img.GetWidth() /2, y - img.GetHeight() /2);
	glTexCoord2i(0, 1); glVertex2i(x - img.GetWidth() / 2, y + img.GetHeight() / 2);
	glTexCoord2i(1, 1); glVertex2i(x + img.GetWidth() / 2, y + img.GetHeight() / 2);
	glTexCoord2i(1, 0); glVertex2i(x + img.GetWidth() / 2, y - img.GetHeight() / 2);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDeleteTextures(1, &tex);
}

void Graphic::FillRec(int x, int y, int width, int height, int r, int g, int b)
{
	glColor3ub(r, g, b);
	glBegin(GL_QUADS);

	glVertex2i(x - width / 2, y - height / 2);
	glVertex2i(x + width / 2, y - height / 2);
	glVertex2i(x + width / 2, y + height / 2);
	glVertex2i(x - width / 2, y + height / 2);
	glEnd();
	glColor4f(1, 1, 1, 1);
}