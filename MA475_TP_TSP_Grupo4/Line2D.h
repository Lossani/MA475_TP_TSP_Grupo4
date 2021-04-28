#pragma once

#ifndef __LINE2D_H__
#define __LINE2D_H__

#include "Point2D.h"

class Line2D
{
private:
	Point2D point1;
	Point2D point2;

public:
	Line2D(float x1, float y1, float x2, float y2);
	~Line2D();

	float distance();

	void set_x1(float x1);
	void set_x2(float x2);
	void set_y1(float y1);
	void set_y2(float y2);

	float get_x1();
	float get_x2();
	float get_y1();
	float get_y2();

	float get_medium_x();
	float get_medium_y();

	virtual void draw();
};

#endif