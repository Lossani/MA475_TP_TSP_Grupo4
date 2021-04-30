#pragma once

#ifndef __NODEPOINTER2D_H__
#define __NODEPOINTER2D_H__

#include "Point2D.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;
using namespace System;

class NodePointer2D : public Point2D
{
public:
	NodePointer2D(float x, float y);
	~NodePointer2D();

	void draw(Graphics^ graphics) override;
	void draw(Graphics^ graphics, String^ text);
};

#endif