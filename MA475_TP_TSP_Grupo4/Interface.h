#pragma once

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <iostream>
#include <functional>
#include <vector>
#include <math.h>
#include "TSPSolver.h"

#include "Point2D.h"
#include "Line2D.h"
#include "NodePointer2D.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace std;

#define node_radius 10

public ref class Interface
{
private:
	vector<vector<int>>* node_table = new vector<vector<int>>(0, vector<int>(0, 0));

	vector<Point2D*>* nodes;
	vector<Line2D*>* routes;

	NodePointer2D* init_node_pointer;
	NodePointer2D* finish_node_pointer;
	String^ texto;

	bool following_node_on = false;
	int node_to_follow = -1;

	TSPSolver* solver;

public:
	Interface();
	Interface(TSPSolver* solver_instance);
	~Interface();

	void draw(Graphics^ graphics);

	//void cursor_click(int x, int y);

	void new_node(int x, int y);

	Line2D* new_route(int x1, int y1, int x2, int y2);

	void draw_routes();

	void drawer_iterator(Graphics^ graphics, int x, int y, bool is_click);

	void new_node();

	void delete_node(int index);

	void delete_last_node();

	void solve_with_brute_force();

	void solve_with_dynamic_programming_method();

	void solve_with_branch_and_bound_method();

	void solve_test();

	void set_node_position(int node_index, float x, float y);

	vector<vector<int>> get_nodes();

	void reset_nodes();
};

#endif