#include "NodePointer2D.h"

NodePointer2D::NodePointer2D(float x1, float y1) : Point2D(x1, y1)
{
}

NodePointer2D::~NodePointer2D()
{
}

void NodePointer2D::draw(Graphics^ graphics)
{
	graphics->FillRectangle(gcnew SolidBrush(Color::DarkGreen), x - 2.f, y - 20.f, 4.f, 15.f);

	for (int i = 4; i < 12; i++)
	{
		graphics->DrawLine(gcnew Pen(Color::DarkGreen), x - 10, y - i, x, y);
		graphics->DrawLine(gcnew Pen(Color::DarkGreen), x + 10, y - i, x, y);
	}
}

void NodePointer2D::draw(Graphics^ graphics, String^ text)
{
	graphics->DrawString(text, gcnew System::Drawing::Font(L"Gill Sans MT", 10.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)), Brushes::DarkSeaGreen, Rectangle(x - 16, y - 40, 2000, 2000));

	graphics->FillRectangle(gcnew SolidBrush(Color::DarkGreen), x - 2.f, y - 20.f, 4.f, 15.f);

	for (int i = 4; i < 12; i++)
	{
		graphics->DrawLine(gcnew Pen(Color::DarkGreen), x - 10.f, y - i, x, y);
		graphics->DrawLine(gcnew Pen(Color::DarkGreen), x + 10.f, y - i, x, y);
	}
}
