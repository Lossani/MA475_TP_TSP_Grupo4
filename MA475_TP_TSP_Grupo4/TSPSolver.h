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
	vector<vector<int>> optimal_routes;
	int optimal_routes_cost;
	vector<int> completed;

	bool chrono_checker();
	chrono::system_clock::time_point start_time;
	chrono::system_clock::time_point finish_time;

	void evaluate_nodes(T_NODE subtree, vector<int>& path, int init_node, int origin, int previous_origin = -1);
	bool reaches_init_point(int init_point, int node, vector<int>& helper_path, int previous_node = -1);
	bool reaches_init_point(T_NODE* table, int init_point, int node, vector<int>& invalid_nodes, vector<int>& helper_path, int previous_node = -1);

	// BRUTE FORCE METHOD FUNCTIONS START
	vector<int> nth_permutation(const int i, int n);
	void brute_force(int init_point);
	//void evaluate_permutation(vector<int> permutation, int init_point, int &current_min_path);
	void evaluate_permutation(vector<int> permutation, int init_point, int& current_min_path, vector<vector<int>>&path_storage);
	void threaded_brute_force(int init_point);
	// BRUTE FORCE METHOD FUNCTIONS END

	// DYNAMIC PROGRAMMING METHOD FUNCTIONS START
	void dynamic_programming_method(T_NODE* node_table, int init_point, int node);
	int min_path(T_NODE* node_table, int init_point, int node);
	// DYNAMIC PROGRAMMING METHOD FUNCTIONS END

	// BRANCH AND BOUND FUNCTIONS START
	vector<bool> visited;

	int first_min_path(T_NODE* node_table, int end);
	int second_min_path(T_NODE* node_table, int end);
	void branch_and_bound_method(T_NODE* node_table, int current_bound, int current_weight, int level, vector<int> current_path);
	// BRANCH AND BOUND FUNCTIONS END

	// PRIM METHOD FUNCTIONS END
	void evaluate_branches(T_NODE* main_node_table, int init_point, T_NODE subtree, vector<int>& path, int origin, int previous_origin);
	//bool evaluate_branches(T_NODE subtree, vector<int>& path, int init_point, int origin, int previous_origin = -1);

	vector<vector<int>> prim(T_NODE* node_table, int init_node);
	// PRIM METHOD FUNCTIONS END
public:
	TSPSolver();
	TSPSolver(vector<vector<int>> node_data);
	~TSPSolver();

	vector<int> get_valid_nodes(int init_point);
	T_NODE get_valid_nodes_table(int init_point);
	bool is_a_valid_node(int init_point, int node);

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

	void reset();
};

#endif

