#pragma once

#ifndef __TSPSOLVER_H__
#define __TSPSOLVER_H__

#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

#define T_NODE vector<vector<int>>

using namespace std;

class TSPSolver
{
private:
	vector<vector<int>> nodes;
	vector<vector<int>> optimal_routes = vector<vector<int>>();
	int optimal_routes_cost = 0;
	vector<int> completed;

	bool chrono_checker();
	chrono::system_clock::time_point start_time;
	chrono::system_clock::time_point finish_time;

	// BRUTE FORCE METHOD FUNCTIONS START
	vector<int> nth_permutation(const int i, int n);
	void brute_force(int init_point);
	void evaluate_permutation(vector<int> permutation, int init_point, int &current_min_path);
	void evaluate_permutation(vector<int> permutation, int init_point, int& current_min_path, vector<vector<int>>&path_storage);
	void threaded_brute_force(int init_point);
	// BRUTE FORCE METHOD FUNCTIONS END

	// DYNAMIC PROGRAMMING METHOD FUNCTIONS START
	void dynamic_programming_method(int init_point);
	int min_path(int node);
	// DYNAMIC PROGRAMMING METHOD FUNCTIONS END

	// BRANCH AND BOUND FUNCTIONS START
	vector<bool> visited;

	int first_min_path(int end);
	int second_min_path(int end);
	void branch_and_bound_method(int current_bound, int current_weight, int level, vector<int> current_path);
	// BRANCH AND BOUND FUNCTIONS END

	// PRIM METHOD FUNCTIONS END
	vector<vector<int>> prim();
	// PRIM METHOD FUNCTIONS END
public:
	TSPSolver();
	TSPSolver(vector<vector<int>> node_data);
	~TSPSolver();

	bool limit_computing_time = false;
	int limit_time = 0;

	bool use_multithreading = false;
	int threads = 1;

	void set_nodes(vector<vector<int>> node_data);
	T_NODE get_nodes();

	void solve_brute_force(int init_node);
	void solve_dynamic_programming_method(int init_node);
	void solve_branch_and_bound_method(int init_point);

	void solve_approximated_prim_method(int init_point);

	vector<vector<int>> get_optimal_routes_result();
	int get_optimal_routes_cost();
	int get_computing_timme_taken();
};

#endif

