#include "TSPSolver.h"

bool TSPSolver::chrono_checker()
{
    if (limit_computing_time)
    {
        std::chrono::duration<float, std::milli> duration = chrono::system_clock::now() - start_time;

        if (duration.count() >= limit_time)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
        return true;
}

vector<int> TSPSolver::nth_permutation(const int i, int n)
{
    int j, k = 0;
    vector<int> fact(i);
    vector<int> permutation(i);

    fact[k] = 1;
    while (++k < i)
        fact[k] = fact[k - 1] * k;

    for (k = 0; k < i; ++k)
    {
        permutation[k] = n / fact[i - 1 - k];
        n = n % fact[i - 1 - k];
    }

    for (k = i - 1; k > 0; --k)
        for (j = k - 1; j >= 0; --j)
            if (permutation[j] <= permutation[k])
                permutation[k]++;

    return permutation;
}

void TSPSolver::brute_force(int init_point)
{
    vector<int> vertex;
    for (int i = 0; i < nodes.size(); i++)
        if (i != init_point)
            vertex.push_back(i);
    
    vector<int> currentRoute;
    do {
        evaluate_permutation(vertex, init_point, optimal_routes_cost);
        if (!chrono_checker())
            return;
    } while (
        next_permutation(vertex.begin(), vertex.end()));
}

void TSPSolver::evaluate_permutation(vector<int> permutation, int init_point, int &current_min_path)
{
    vector<int> currentRoute;

    currentRoute.push_back(init_point);

    int current_pathweight = 0;

    int k = init_point;
    for (int i = 0; i < permutation.size(); i++) {
        current_pathweight += nodes[k][permutation[i]];
        k = permutation[i];
        currentRoute.push_back(k);
    }
    current_pathweight += nodes[k][init_point];

    currentRoute.push_back(init_point);

    if (current_pathweight < current_min_path)
    {
        current_min_path = current_pathweight;
        optimal_routes.clear();
        optimal_routes.push_back(currentRoute);
    }
    else if (current_pathweight == current_min_path)
    {
        optimal_routes.push_back(currentRoute);
    }
}

void TSPSolver::evaluate_permutation(vector<int> permutation, int init_point, int& current_min_path, vector<vector<int>>& path_storage)
{
    vector<int> currentRoute;

    currentRoute.push_back(init_point);

    // Store current path cost
    int current_pathweight = 0;

    // Calculate current path weight
    int k = init_point;
    for (int i = 0; i < permutation.size(); i++) {
        current_pathweight += nodes[k][permutation[i]];
        k = permutation[i];
        currentRoute.push_back(k);
    }
    current_pathweight += nodes[k][init_point];

    currentRoute.push_back(init_point);

    if (current_pathweight < current_min_path)
    {
        current_min_path = current_pathweight;
        path_storage.clear();
        path_storage.push_back(currentRoute);
    }
    else if (current_pathweight == current_min_path)
    {
        path_storage.push_back(currentRoute);
    }
}


void TSPSolver::threaded_brute_force(int init_point)
{
    vector<thread> threads_list;

    uint64_t current_index = 0;
    // Simple factorial to get total permutations number
    uint64_t total_permutations = 1;
    for (int i = 1; i <= nodes.size() - 1; ++i)
        total_permutations *= i;

    uint64_t times_per_thread = total_permutations / threads;
    uint64_t last_thread = times_per_thread;

    if (times_per_thread * threads != total_permutations)
    {
        last_thread = total_permutations - (times_per_thread * (threads - 1));
    }

    int nodes_count = nodes.size();
    vector<int> threads_min_path(threads, INT_MAX);
    vector<vector<vector<int>>> threads_paths(threads);

    for (int i = 0; i < threads; ++i)
    {
        vector<int> current_permutation = nth_permutation(nodes.size() - 1, current_index);

        for (int j = 0; j < current_permutation.size(); ++j)
        {
            if (current_permutation[j] >= init_point)
                current_permutation[j]++;
        }

        uint64_t current_thread_times;
        if (i != threads - 1)
        {
            current_thread_times = times_per_thread;
        }
        else
        {
            current_thread_times = last_thread;
        }
        
        threads_list.push_back(thread([current_permutation, current_thread_times, nodes_count, init_point, &threads_min_path, &threads_paths, i, this]() mutable {
            evaluate_permutation(current_permutation, init_point, threads_min_path[i], threads_paths[i]);
            for (size_t j = 1; j < current_thread_times; ++j)
            {
                next_permutation(current_permutation.begin(), current_permutation.end());
                evaluate_permutation(current_permutation, init_point, threads_min_path[i], threads_paths[i]);
                if (!chrono_checker())
                    return;
            }
            }));

        current_index += current_thread_times;

        if (!chrono_checker())
            return;
    }

    for (thread& single_thread : threads_list)
    {
        single_thread.join();
    }

    for (int i = 0; i < threads; ++i)
    {
        if (threads_min_path[i] < optimal_routes_cost)
        {
            optimal_routes_cost = threads_min_path[i];
            optimal_routes = threads_paths[i];
        }
    }
}

void TSPSolver::dynamic_programming_method(int init_point)
{
    if (!chrono_checker())
        return;

    int ncity;

    completed[init_point] = 1;
    optimal_routes[0].push_back(init_point);
    ncity = min_path(init_point);

    if (ncity == INT_MAX)
    {
        ncity = 0;
        optimal_routes[0].push_back(ncity);
        optimal_routes_cost += nodes[init_point][ncity];

        return;
    }

    dynamic_programming_method(ncity);
}

int TSPSolver::min_path(int node)
{
    int nc = INT_MAX;
    int min = INT_MAX, kmin;

    for (int i = 0; i < nodes.size(); i++)
    {
        if ((nodes[node][i] != 0) && (completed[i] == 0))
           
            if (nodes[node][i] + nodes[i][node] < min)
            {
                min = nodes[i][0] + nodes[node][i];
                kmin = nodes[node][i];
                nc = i;
            }
    }

    if (min != INT_MAX)
        optimal_routes_cost += kmin;

    return nc;
}

int TSPSolver::first_min_path(int end)
{
    int min = INT_MAX;
    for (int k = 0; k < nodes.size(); k++)
        if (nodes[end][k] < min && end != k)
            min = nodes[end][k];
    return min;
}

int TSPSolver::second_min_path(int end)
{
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < nodes.size(); j++)
    {
        if (end == j)
            continue;

        if (nodes[end][j] <= first)
        {
            second = first;
            first = nodes[end][j];
        }
        else if (nodes[end][j] <= second &&
            nodes[end][j] != first)
            second = nodes[end][j];
    }
    return second;
}

void TSPSolver::branch_and_bound_method(int current_bound, int current_weight, int level, vector<int> current_path)
{
    if (level == nodes.size())
    {
        if (nodes[current_path[level - 1]][current_path[0]] != 0)
        {
            int curr_res = current_weight +
                nodes[current_path[level - 1]][current_path[0]];

            if (curr_res < optimal_routes_cost)
            {
                for (int i = 0; i < nodes.size(); i++)
                    optimal_routes[0][i] = current_path[i];
                optimal_routes[0][nodes.size()] = current_path[0];
                optimal_routes_cost = curr_res;
            }
        }
        return;
    }

    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[current_path[level - 1]][i] != 0 &&
            visited[i] == false)
        {
            int temp = current_bound;
            current_weight += nodes[current_path[level - 1]][i];

            if (level == 1)
                current_bound -= ((first_min_path(current_path[level - 1]) +
                    first_min_path(i)) / 2);
            else
                current_bound -= ((second_min_path(current_path[level - 1]) +
                    first_min_path(i)) / 2);

            if (current_bound + current_weight < optimal_routes_cost)
            {
                current_path[level] = i;
                visited[i] = true;

                branch_and_bound_method(current_bound, current_weight, level + 1,
                    current_path);
            }

            current_weight -= nodes[current_path[level - 1]][i];
            current_bound = temp;

            // Also reset the visited array
            visited = vector<bool>(visited.size());
            for (int j = 0; j <= level - 1; j++)
                visited[current_path[j]] = true;

            if (!chrono_checker())
                return;
        }
    }
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
    optimal_routes_cost = INT_MAX;
    optimal_routes = vector<vector<int>>();
}

void TSPSolver::solve_brute_force(int init_node)
{
    start_time = chrono::system_clock::now();

    optimal_routes_cost = INT_MAX;
    optimal_routes = vector<vector<int>>();

    if (use_multithreading)
    {
        if (threads < 0 || threads > thread::hardware_concurrency())
        {
            threads = 1;
        }

        threaded_brute_force(init_node);
    }
    else
    { 
        brute_force(init_node);
    } 
}

T_NODE TSPSolver::get_nodes()
{
    return nodes;
}

void TSPSolver::solve_dynamic_programming_method(int init_node)
{
    start_time = chrono::system_clock::now();

    optimal_routes_cost = 0;
    optimal_routes = vector<vector<int>>();
    optimal_routes.push_back(vector<int>());
    completed = vector<int>(nodes.size(), 0);
    dynamic_programming_method(init_node);
}

void TSPSolver::solve_branch_and_bound_method(int init_point)
{
    start_time = chrono::system_clock::now();

    optimal_routes_cost = INT_MAX;
    optimal_routes = vector<vector<int>>();
    optimal_routes.push_back(vector<int>(nodes.size() + 1));
    visited = vector<bool>(nodes.size(), 0);
    vector<int> current_path(nodes.size() + 1, -1);

    int current_bound = 0;

    for (int i = 0; i < nodes.size(); i++)
        current_bound += (first_min_path(i) +
            second_min_path(i));

    current_bound = (current_bound & 1) ? current_bound / 2 + 1 :
        current_bound / 2;

    visited[init_point] = true;
    current_path[0] = init_point;

    branch_and_bound_method(current_bound, 0, 1, current_path);
}

void evaluate_branches(T_NODE subtree, vector<int>& path, int origin, int previous_origin = -1)
{
    for (int i = 0; i < subtree.size(); ++i)
    {
        if (origin != i && previous_origin != i && subtree[origin][i] != -1)
        {      
            path.push_back(i);
            evaluate_branches(subtree, path, i, origin);
        }
    }
}
void TSPSolver::solve_approximated_prim_method(int init_point)
{
    start_time = chrono::system_clock::now();

    vector<vector<int>> tree = prim();
    vector<vector<int>> paths;
    vector<int> path(1);

    evaluate_branches(tree, path, init_point);

    optimal_routes.clear();
    optimal_routes.push_back(vector<int>());

    for (int node : path)
    {
        optimal_routes[0].push_back(node);
    }
    optimal_routes[0].push_back(init_point);

    // Calculating final path cost

    optimal_routes_cost = 0;

    for (int i = 0; i < optimal_routes[0].size() - 1; ++i)
    {
        optimal_routes_cost += nodes[optimal_routes[0][i]][optimal_routes[0][i + 1]];
    }
}

vector<vector<int>> TSPSolver::prim()
{
    vector< vector<int> > adyacencia = nodes;
    vector< vector<int> > tree(nodes.size());
    vector<int> markedLines;
    vector<int> ::iterator vectorIterator;

    for (int i = 0; i < nodes.size(); i++)
        tree[i] = vector<int>(nodes.size(), -1);

    int root = 0;
    int child = 0;
    while (markedLines.size() + 1 < nodes.size()) {
        root = child;
        markedLines.push_back(root);
        for (int i = 0; i < nodes.size(); i++)
            adyacencia[i][root] = INT_MAX;

        int min = INT_MAX;
        for (vectorIterator = markedLines.begin(); vectorIterator != markedLines.end(); vectorIterator++)
            for (int i = 0; i < nodes.size(); i++)
                if (min > adyacencia[*vectorIterator][i]) {
                    min = adyacencia[*vectorIterator][i];
                    root = *vectorIterator;
                    child = i;
                }

        tree[root][child] = min;
        tree[child][root] = min;
    }
    return tree;
}

vector<vector<int>> TSPSolver::get_optimal_routes_result()
{
    return optimal_routes;
}

int TSPSolver::get_optimal_routes_cost()
{
    return optimal_routes_cost;
}

int TSPSolver::get_computing_timme_taken()
{
    chrono::duration<float, std::milli> duration = chrono::system_clock::now() - start_time;

    return duration.count();
}
