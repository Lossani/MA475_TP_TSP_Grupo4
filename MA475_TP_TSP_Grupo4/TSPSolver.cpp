#include "TSPSolver.h"

int TSPSolver::brute_force(int init_point)
{
    // store all vertex apart from source vertex
    vector<int> vertex;
    for (int i = 0; i < nodes.size(); i++)
        if (i != init_point)
            vertex.push_back(i);

    // store minimum weight Hamiltonian Cycle.
    int min_path = INT_MAX;
    
    vector<int> currentRoute;
    do {
        currentRoute.clear();
        currentRoute.push_back(init_point);
        // store current Path weight(cost)
        int current_pathweight = 0;

        // compute current path weight
        int k = init_point;
        for (int i = 0; i < vertex.size(); i++) {
            current_pathweight += nodes[k][vertex[i]];
            k = vertex[i];
            currentRoute.push_back(k);
        }
        current_pathweight += nodes[k][init_point];

        // update minimum
        //min_path = min(min_path, current_pathweight);

        if (current_pathweight < min_path)
        {
            min_path = current_pathweight;
            optimal_routes.push_back(currentRoute);
        }
        else if (current_pathweight == min_path)
        {
            optimal_routes.push_back(currentRoute);
        }

    } while (
        next_permutation(vertex.begin(), vertex.end()));

    return min_path;
}

TSPSolver::TSPSolver()
{
}

TSPSolver::TSPSolver(vector<vector<int>> node_data) : nodes(node_data)
{

}

TSPSolver::~TSPSolver()
{
    nodes.clear();
}

void TSPSolver::set_nodes(vector<vector<int>> node_data)
{
    nodes = node_data;
    optimal_routes_cost = 0;
    optimal_routes = vector<vector<int>>();
}

void TSPSolver::solve_brute_force(int init_node)
{
    optimal_routes_cost = brute_force(init_node);
}

vector<vector<int>> TSPSolver::get_optimal_routes_result()
{
    return optimal_routes;
}

int TSPSolver::get_optimal_routes_cost()
{
    return optimal_routes_cost;
}
