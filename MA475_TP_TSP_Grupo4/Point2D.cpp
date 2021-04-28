#include "Point2D.h"

Point2D::Point2D(int x, int y) : x(x), y(y)
{
}

Point2D::~Point2D()
{
}

void Point2D::set_position(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Point2D::set_x(float x)
{
	this->x = x;
}

void Point2D::set_y(float y)
{
	this->y = y;
}

int Point2D::get_x()
{
	return x;
}

float Point2D::get_y()
{
	return y;
}

void Point2D::draw(Graphics^ graphics)
{
	graphics->DrawLine(gcnew Pen(Color::Aqua), x, y, x, y);
}

