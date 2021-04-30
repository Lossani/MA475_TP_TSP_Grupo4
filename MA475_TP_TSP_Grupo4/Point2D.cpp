#include "Point2D.h"

Point2D::Point2D(int x, int y) : x(x), y(y)
{
}

Point2D::~Point2D()
{
}

void Point2D::draw(Graphics^ graphics)
{
	graphics->DrawLine(gcnew Pen(Color::Aqua), x, y, x, y);
}

void Point2D::draw(Graphics^ graphics, float radius)
{
	graphics->FillEllipse(gcnew SolidBrush(Color::DarkOrange), System::Drawing::Rectangle(x - (radius / 2), y - (radius / 2), radius, radius));
}

void Point2D::draw(Graphics^ graphics, float radius, String^ caption)
{
	graphics->FillEllipse(gcnew SolidBrush(Color::DarkOrange), System::Drawing::Rectangle(x - (radius / 2), y - (radius / 2), radius, radius));
	graphics->DrawString(caption, gcnew System::Drawing::Font(L"Gill Sans MT", 8.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)), Brushes::Black, Rectangle(x - 5.f, y - 18.f, 1000, 1000));
}