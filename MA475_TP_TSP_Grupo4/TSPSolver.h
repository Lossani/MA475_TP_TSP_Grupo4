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
	vector<int> optimalRoute;
	int routeCost = -1;

	int bruteForce(int initPoint);
public:
	TSPSolver(vector<vector<int>> nodeData);
	~TSPSolver();

	void setNodes(vector<vector<int>> nodeData);
	void solveBruteForce();

	vector<int> getOptimalRouteResult();
	int getRouteCostResult();
};

#endif

