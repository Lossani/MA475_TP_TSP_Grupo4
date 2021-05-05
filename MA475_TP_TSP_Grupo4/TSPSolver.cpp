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

    // compute factorial numbers
    fact[k] = 1;
    while (++k < i)
        fact[k] = fact[k - 1] * k;

    // compute factorial code
    for (k = 0; k < i; ++k)
    {
        permutation[k] = n / fact[i - 1 - k];
        n = n % fact[i - 1 - k];
    }

    // readjust values to obtain the permutation
    // start from the end and check if preceding values are lower
    for (k = i - 1; k > 0; --k)
        for (j = k - 1; j >= 0; --j)
            if (permutation[j] <= permutation[k])
                permutation[k]++;

    return permutation;
}

void TSPSolver::brute_force(int init_point)
{
    // store all vertex apart from source vertex
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

    // store current Path weight(cost)
    int current_pathweight = 0;

    // compute current path weight
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

    // store current Path weight(cost)
    int current_pathweight = 0;

    // compute current path weight
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
    int total_permutations = 1;
    for (int i = 1; i <= nodes.size() - 1; ++i)
        total_permutations *= i;

    int times_per_thread = total_permutations / threads;
    int last_thread = times_per_thread;

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

        int current_thread_times;
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
        // check if there is an edge from last vertex in
        // path back to the first vertex
        if (nodes[current_path[level - 1]][current_path[0]] != 0)
        {
            // curr_res has the total weight of the
            // solution we got
            int curr_res = current_weight +
                nodes[current_path[level - 1]][current_path[0]];

            // Update final result and final path if
            // current result is better.
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

    // for any other level iterate for all vertices to
    // build the search space tree recursively
    for (int i = 0; i < nodes.size(); i++)
    {
        // Consider next vertex if it is not same (diagonal
        // entry in adjacency matrix and not visited
        // already)
        if (nodes[current_path[level - 1]][i] != 0 &&
            visited[i] == false)
        {
            int temp = current_bound;
            current_weight += nodes[current_path[level - 1]][i];

            // different computation of curr_bound for
            // level 2 from the other levels
            if (level == 1)
                current_bound -= ((first_min_path(current_path[level - 1]) +
                    first_min_path(i)) / 2);
            else
                current_bound -= ((second_min_path(current_path[level - 1]) +
                    first_min_path(i)) / 2);

            // curr_bound + curr_weight is the actual lower bound
            // for the node that we have arrived on
            // If current lower bound < final_res, we need to explore
            // the node further
            if (current_bound + current_weight < optimal_routes_cost)
            {
                current_path[level] = i;
                visited[i] = true;

                // call TSPRec for the next level
                branch_and_bound_method(current_bound, current_weight, level + 1,
                    current_path);
            }

            // Else we have to prune the node by resetting
            // all changes to curr_weight and curr_bound
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

    // Calculate initial lower bound for the root node
    // using the formula 1/2 * (sum of first min +
    // second min) for all edges.
    // Also initialize the curr_path and visited array
    int current_bound = 0;

    // Compute initial bound
    for (int i = 0; i < nodes.size(); i++)
        current_bound += (first_min_path(i) +
            second_min_path(i));

    // Rounding off the lower bound to an integer
    current_bound = (current_bound & 1) ? current_bound / 2 + 1 :
        current_bound / 2;

    // We start at vertex 1 so the first vertex
    // in curr_path[] is 0
    visited[init_point] = true;
    current_path[init_point] = 0;

    // Call to TSPRec for curr_weight equal to
    // 0 and level 1
    branch_and_bound_method(current_bound, 0, 1, current_path);
}

void TSPSolver::solve_approximated_prim_method(int init_point)
{
    start_time = chrono::system_clock::now();

    vector<vector<int>> tree = prim();
    vector<vector<int>> paths;

    for (int i = 0; i < tree.size(); ++i)
    {
        if (i != 0 && tree[init_point][i] != -1)
        {
            paths.push_back(vector<int>());

            paths[paths.size() - 1].push_back(i);

            bool keep_searching = true;
            int origin = init_point;
            int target = i;

            while (keep_searching)
            {
                keep_searching = false;
                for (int j = 0; j < tree.size(); ++j)
                {
                    if (origin != j && tree[target][j] != -1)
                    {
                        keep_searching = true;
                        origin = target;
                        target = j;
                        paths[paths.size() - 1].push_back(j);
                    }
                }
            }
        }
    }

    optimal_routes.clear();
    optimal_routes.push_back(vector<int>());
    optimal_routes[0].push_back(init_point);

    // Si tenemos varios caminos debemos fusionarlos para dar el camino final.
    if (paths.size() > 1)
    {
        for (int j = 0; j < paths[0].size(); ++j)
        {
            optimal_routes[0].push_back(paths[0][j]);
        }
        for (int i = 1; i < paths.size(); ++i)
        {
            for (int j = paths[i].size() - 1; j >= 0; --j)
            {
                optimal_routes[0].push_back(paths[i][j]);
            }
        }

        optimal_routes[0].push_back(init_point);
    }
    else
    {
        optimal_routes.clear();
        optimal_routes.push_back(vector<int>());
        optimal_routes[0].push_back(init_point);
        for (int path : paths[0])
        {
            optimal_routes[0].push_back(path);
        }
        optimal_routes[0].push_back(init_point);
    }

    // Calculating final path cost

    optimal_routes_cost = 0;

    for (int i = 0; i < optimal_routes[0].size() - 1; ++i)
    {
        optimal_routes_cost += nodes[optimal_routes[0][i]][optimal_routes[0][i + 1]];
    }
}

vector<vector<int>> TSPSolver::prim()
{
    // uso una copia de adyacencia porque necesito eliminar columnas
    vector< vector<int> > adyacencia = nodes;
    vector< vector<int> > arbol(nodes.size());
    vector<int> markedLines;
    vector<int> ::iterator vectorIterator;

    // Inicializo las distancias del arbol en INF.
    for (int i = 0; i < nodes.size(); i++)
        arbol[i] = vector<int>(nodes.size(), -1);

    int padre = 0;
    int hijo = 0;
    while (markedLines.size() + 1 < nodes.size()) {
        padre = hijo;
        // Marco la fila y elimino la columna del nodo padre.
        markedLines.push_back(padre);
        for (int i = 0; i < nodes.size(); i++)
            adyacencia[i][padre] = INT_MAX;

        // Encuentro la menor distancia entre las filas marcadas.
        // El nodo padre es la linea marcada y el nodo hijo es la columna del minimo.
        int min = INT_MAX;
        for (vectorIterator = markedLines.begin(); vectorIterator != markedLines.end(); vectorIterator++)
            for (int i = 0; i < nodes.size(); i++)
                if (min > adyacencia[*vectorIterator][i]) {
                    min = adyacencia[*vectorIterator][i];
                    padre = *vectorIterator;
                    hijo = i;
                }

        arbol[padre][hijo] = min;
        arbol[hijo][padre] = min;
    }
    return arbol;
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
