#pragma once

#ifndef __TSPSOLVER_H__
#define __TSPSOLVER_H__

#include <vector>
#include <algorithm>

using namespace std;

class TSPSolver
{
private:
	vector<vector<int>> nodes;
	vector<vector<int>> optimal_routes = vector<vector<int>>();
	int optimal_routes_cost = 0;

	int brute_force(int initPoint);
public:
	TSPSolver();
	TSPSolver(vector<vector<int>> node_data);
	~TSPSolver();

	void set_nodes(vector<vector<int>> node_data);
	void solve_brute_force(int init_point);

	vector<vector<int>> get_optimal_routes_result();
	int get_optimal_routes_cost();
};

#endif

