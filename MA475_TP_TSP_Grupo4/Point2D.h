#pragma once

#ifndef __POINT2D_H__
#define __POINT2D_H__

using namespace System;
using namespace System::Drawing;

class Point2D
{
public:
	float x = 0;
	float y = 0;

	Point2D(int x, int y);
	~Point2D();

	virtual void draw(Graphics^ graphics);
	virtual void draw(Graphics^ graphics, float radius);
	virtual void draw(Graphics^ graphics, float radius, String^ caption);
};

#endif