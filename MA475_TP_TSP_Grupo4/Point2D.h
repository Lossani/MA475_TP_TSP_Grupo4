#pragma once

#ifndef __POINT2D_H__
#define __POINT2D_H__

using namespace System::Drawing;

class Point2D
{
private:
	float x = 0;
	float y = 0;

public:
	Point2D(int x, int y);
	~Point2D();

	void set_position(float x, float y);
	void set_x(float x);
	void set_y(float y);

	int get_x();
	float get_y();

	void draw(System::Drawing::Graphics^ graphics);
};

#endif