#include "Line2D.h"

Line2D::Line2D(float x1, float y1, float x2, float y2)
{
	point1 = Point2D(x1, y1);
	point2 = Point2D(x2, y2);
}

Line2D::~Line2D()
{
}

float Line2D::distance()
{
	return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

void Line2D::set_x1(float x1)
{
	point1.x = x1;
}

void Line2D::set_x2(float x2)
{
	point2.x = x2;
}

void Line2D::set_y1(float y1)
{
	point1.y = y1;
}

void Line2D::set_y2(float y2)
{
	point2.y = y2;
}

float Line2D::get_x1()
{
	return point1.x;
}

float Line2D::get_x2()
{
	return point2.x;
}

float Line2D::get_y1()
{
	return point1.y;
}

float Line2D::get_y2()
{
	return point2.y;
}

float Line2D::get_medium_x()
{
	if (point2.x > point1.x)
		return point1.x + abs(point2.x - point1.x) / 2;
	else
		return point2.x + abs(point2.x - point1.x) / 2;
}

float Line2D::get_medium_y()
{
	if (point2.y > point1.y)
		return point1.y + abs(point2.y - point1.y) / 2;
	else
		return point2.y + abs(point2.y - point1.y) / 2;
}

void Line2D::draw(Graphics^ graphics)
{
	graphics->DrawLine(gcnew Pen(Color::Aqua), point1.x, point1.y, point2.x, point2.y);
}

void Line2D::draw(Graphics^ graphics, String^ caption)
{
	graphics->DrawLine(gcnew Pen(Color::Aqua), point1.x, point1.y, point2.x, point2.y);
	graphics->DrawString(caption, gcnew System::Drawing::Font(L"Gill Sans MT", 8.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)), Brushes::Chocolate, Rectangle(get_medium_x(), get_medium_y(), 2000, 2000));
}
