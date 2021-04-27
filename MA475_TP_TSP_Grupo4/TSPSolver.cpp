#include "TSPSolver.h"

int TSPSolver::bruteForce(int initPoint)
{
    // store all vertex apart from source vertex
    vector<int> vertex;
    for (int i = 0; i < nodes.size(); i++)
        if (i != initPoint)
            vertex.push_back(i);

    // store minimum weight Hamiltonian Cycle.
    int min_path = INT_MAX;
    
    vector<int> currentRoute;
    do {
        currentRoute.clear();
        currentRoute.push_back(initPoint);
        // store current Path weight(cost)
        int current_pathweight = 0;

        // compute current path weight
        int k = initPoint;
        for (int i = 0; i < vertex.size(); i++) {
            current_pathweight += nodes[k][vertex[i]];
            k = vertex[i];
            currentRoute.push_back(k);
        }
        current_pathweight += nodes[k][initPoint];

        // update minimum
        //min_path = min(min_path, current_pathweight);

        if (current_pathweight < min_path)
        {
            min_path = current_pathweight;
            optimalRoute = currentRoute;
        }

    } while (
        next_permutation(vertex.begin(), vertex.end()));

    return min_path;
}

TSPSolver::TSPSolver(vector<vector<int>> nodeData) : nodes(nodeData)
{

}

TSPSolver::~TSPSolver()
{
    nodes.clear();
}

void TSPSolver::setNodes(vector<vector<int>> nodeData)
{
    nodes = nodeData;
}

void TSPSolver::solveBruteForce()
{
    routeCost = bruteForce(0);
}

vector<int> TSPSolver::getOptimalRouteResult()
{
    return optimalRoute;
}

int TSPSolver::getRouteCostResult()
{
    return routeCost;
}
