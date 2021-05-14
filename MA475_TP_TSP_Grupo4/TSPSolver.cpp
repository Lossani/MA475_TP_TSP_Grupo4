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

vector<int> TSPSolver::get_valid_nodes(int init_point)
{
    vector<int> valid_nodes;

    int valid_exit_paths = 0;
    int valid_enter_paths = 0;

    for (int i = 0; i < nodes.size(); ++i)
    {
        if (i == init_point)
            continue;

        if (nodes[init_point][i] != -1 && nodes[init_point][i] != 0)
        {
            valid_enter_paths++;
        }
        if (nodes[i][init_point] != -1 && nodes[i][init_point] != 0)
        {
            valid_exit_paths++;
        }
    }

    if (valid_enter_paths != 0 && valid_exit_paths != 0)
        valid_nodes.push_back(init_point);
    else
        return valid_nodes;

    for (int i = 0; i < nodes.size(); ++i)
    {
        vector<int> helper_path;

        if (i != init_point)
            if (reaches_init_point(init_point, i, helper_path) && reaches_init_point(i, init_point, helper_path))
                valid_nodes.push_back(i);
    }

    //evaluate_nodes(nodes, valid_nodes, init_point, init_point);

    //for (int i = 0; i < nodes.size(); ++i)
    //{
    //    int valid_exit_paths = 0;
    //    int valid_enter_paths = 0;

    //    for (int j = 0; j < nodes.size(); ++j)
    //    {
    //        if (nodes[i][j] != -1 && nodes[i][j] != 0)
    //        {
    //            valid_enter_paths++;
    //        }
    //        if (nodes[j][i] != -1 && nodes[j][i] != 0)
    //        {
    //            valid_exit_paths++;
    //        }
    //    }

    //    if (valid_enter_paths != 0 && valid_exit_paths != 0)
    //        valid_nodes.push_back(i);

    //    /*vector<vector<int>> paths;

    //    for (int j = 0; j < nodes.size(); ++j)
    //    {
    //        if (j != i && nodes[i][j] != -1 && nodes[i][j] != 0)
    //        {
    //            paths.push_back(vector<int>());

    //            paths[paths.size() - 1].push_back(j);

    //            bool keep_searching = true;
    //            int origin = i;
    //            int target = j;

    //            while (keep_searching)
    //            {
    //                keep_searching = false;
    //                for (int k = 0; k < nodes.size(); ++k)
    //                {
    //                    if (origin != k && nodes[target][k] != -1 && nodes[target][k] != 0)
    //                    {
    //                        keep_searching = true;
    //                        origin = target;
    //                        target = k;
    //                        paths[paths.size() - 1].push_back(k);
    //                    }
    //                }
    //            }
    //        }
    //    }

    //    for (int j = 0; j < nodes.size(); ++j)
    //    {
    //        if (i != j && subtree[origin][i] != -1)
    //        {
    //            vector<int>::iterator it = find(path.begin(), path.end(), i);

    //            if (it == path.end())
    //                path.push_back(i);
    //            evaluate_branches(subtree, path, i, origin);

    //        }
    //    }*/

    //    /*if (i != init_point)
    //    {
    //        vector<int> path;
    //        evaluate_branches(nodes, path, i);
    //    }*/
    //    
    //}
    sort(valid_nodes.begin(), valid_nodes.end());

    return valid_nodes;
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

bool TSPSolver::reaches_init_point(int init_point, int node, vector<int>& helper_path,  int previous_node)
{
    if (nodes[node][init_point] != -1 && nodes[node][init_point] != 0)
        return true;

    for (int i = 0; i < nodes.size(); ++i)
    {
        if (node != i && previous_node != i && nodes[node][i] != -1 && nodes[node][i] != 0)
        {
            //if (i == init_point)
            //    return true;

            vector<int>::iterator it = find(helper_path.begin(), helper_path.end(), i);

            if (it == helper_path.end())
            {
                helper_path.push_back(i);
                return reaches_init_point(init_point, i, helper_path, node);
            }    
        }
    }

    return false;
}

bool TSPSolver::reaches_init_point(T_NODE* table, int init_point, int node, vector<int>& invalid_nodes, vector<int>& helper_path, int previous_node)
{
    if ((*table)[node][init_point] != -1 && (*table)[node][init_point] != 0)
        return true;

    for (int i = 0; i < table->size(); ++i)
    {
        vector<int>::iterator it = find(invalid_nodes.begin(), invalid_nodes.end(), i);

        if (it != invalid_nodes.end())
            continue;

        if (node != i && previous_node != i && (*table)[node][i] != -1 && (*table)[node][i] != 0)
        {
            vector<int>::iterator it2 = find(helper_path.begin(), helper_path.end(), i);

            if (it2 == helper_path.end())
            {
                helper_path.push_back(i);
                return reaches_init_point(table, init_point, i, invalid_nodes, helper_path, node);
            }
        }
    }

    return false;
}

T_NODE TSPSolver::get_valid_nodes_table(int init_point)
{
    vector<int> valid_nodes = get_valid_nodes(init_point);
    T_NODE new_table;

    for (int i = 0; i < valid_nodes.size(); ++i)
    {
        new_table.push_back(vector<int>());
        for (int j = 0; j < nodes[valid_nodes[i]].size(); ++j)
        {
            if (is_a_valid_node(init_point, j))
                new_table[i].push_back(nodes[valid_nodes[i]][j]);
        }
    }

    return new_table;
}

void TSPSolver::brute_force(int init_point)
{
    vector<int> vertex;

    for (int i = 0; i < nodes.size(); i++)
    {
        if (i != init_point)
        {
            if (is_a_valid_node(init_point, i))
                vertex.push_back(i);
        }   
    }
    
    do {
        evaluate_permutation(vertex, init_point, optimal_routes_cost, optimal_routes);
        if (!chrono_checker())
            return;
    } while (
        next_permutation(vertex.begin(), vertex.end()));

    optimal_routes.erase(unique(optimal_routes.begin(), optimal_routes.end()), optimal_routes.end());
}

bool TSPSolver::is_a_valid_node(int init_point, int node)
{
    vector<int> valid_nodes = get_valid_nodes(init_point);

    vector<int>::iterator it = find(valid_nodes.begin(), valid_nodes.end(), node);

    if (it != valid_nodes.end())
        return true;
    else
        return false;
}

//void TSPSolver::evaluate_permutation(vector<int> permutation, int init_point, int &current_min_path)
//{
//    vector<int> currentRoute;
//
//    currentRoute.push_back(init_point);
//
//    int current_pathweight = 0;
//
//    int k = init_point;
//    for (int i = 0; i < permutation.size(); i++) {
//        current_pathweight += nodes[k][permutation[i]];
//        k = permutation[i];
//        currentRoute.push_back(k);
//    }
//    current_pathweight += nodes[k][init_point];
//
//    currentRoute.push_back(init_point);
//
//    if (current_pathweight < current_min_path)
//    {
//        current_min_path = current_pathweight;
//        optimal_routes.clear();
//        optimal_routes.push_back(currentRoute);
//    }
//    else if (current_pathweight == current_min_path)
//    {
//        optimal_routes.push_back(currentRoute);
//    }
//}

void TSPSolver::evaluate_permutation(vector<int> permutation, int init_point, int& current_min_path, vector<vector<int>>& path_storage)
{
    vector<int> currentRoute;

    currentRoute.push_back(init_point);

    // Store current path cost
    int current_pathweight = 0;

    // Calculate current path weight
    int k = init_point;
    for (int i = 0; i < permutation.size(); i++) {
        if ((nodes[k][permutation[i]] == -1 || nodes[k][permutation[i]] == 0))
            continue;

        current_pathweight += nodes[k][permutation[i]];
        k = permutation[i];
        currentRoute.push_back(k);
    }
    if (nodes[k][init_point] == -1 || nodes[k][init_point] == 0)
        return;

    current_pathweight += nodes[k][init_point];

    currentRoute.push_back(init_point);

    if (path_storage.size() == 0 || currentRoute.size() > path_storage[path_storage.size() - 1].size() || (current_pathweight < current_min_path && currentRoute.size() == path_storage[path_storage.size() - 1].size()))
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
    vector<int> valid_nodes = get_valid_nodes(init_point);

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
        vector<int> original_permutation = nth_permutation(nodes.size() - 1, current_index);
        vector<int> current_permutation = original_permutation;

        for (int j = 0; j < original_permutation.size(); ++j)
        {
            if (original_permutation[j] >= init_point)
                original_permutation[j]++;
        }

        if (valid_nodes.size() - 1 < original_permutation.size())
        {
            current_permutation.clear();

            for (int j = 0; j < original_permutation.size(); ++j)
            {
                vector<int>::iterator it = find(valid_nodes.begin(), valid_nodes.end(), original_permutation[j]);

                if (it != valid_nodes.end())
                    current_permutation.push_back(original_permutation[j]);
            }
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

void TSPSolver::dynamic_programming_method(T_NODE* node_table, int init_point, int node)
{
    if (!chrono_checker())
        return;

    vector<int> helper_path;
    int ncity;

    if (reaches_init_point(node_table, init_point, node, optimal_routes[0], helper_path))
    {
        optimal_routes_cost += (*node_table)[optimal_routes[0][optimal_routes[0].size() - 1]][node];
        //completed[node] = 1;
        optimal_routes[0].push_back(node);
    }
    else
    {
        optimal_routes[0].push_back(init_point);
        optimal_routes_cost += (*node_table)[node][init_point];
        return;
    }

    ncity = min_path(node_table, init_point, node);

    if (ncity == INT_MAX || ncity == init_point)// || !reaches_init_point(init_point, ncity, optimal_routes[0], helper_path))
    {
        optimal_routes[0].push_back(init_point);
        optimal_routes_cost += (*node_table)[node][init_point];
        return;
    }

    dynamic_programming_method(node_table, init_point, ncity);
}

int TSPSolver::min_path(T_NODE* node_table, int init_point, int node)
{
    int nc = INT_MAX;
    int min = INT_MAX;//, kmin;

    for (int i = 0; i < node_table->size(); i++)
    {
        vector<int>::iterator it = find(optimal_routes[0].begin(), optimal_routes[0].end(), i);

        if (it == optimal_routes[0].end())
        if ((*node_table)[node][i] != 0 && (*node_table)[node][i] != -1 && (*node_table)[node][i] < min)
        {
            min = (*node_table)[node][i];
            //kmin = (*node_table)[node][i];
            nc = i;
        }
    }

    return nc;
}

int TSPSolver::first_min_path(T_NODE* node_table, int end)
{
    int min = INT_MAX;
    for (int k = 0; k < node_table->size(); k++)
        if ((*node_table)[end][k] != 0 && (*node_table)[end][k] != -1 && (*node_table)[end][k] < min && end != k)
            min = (*node_table)[end][k];
    return min;
}

int TSPSolver::second_min_path(T_NODE* node_table, int end)
{
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < node_table->size(); j++)
    {
        if (end == j)
            continue;

        if ((*node_table)[end][j] != 0 && (*node_table)[end][j] != -1 && (*node_table)[end][j] <= first)
        {
            second = first;
            first = (*node_table)[end][j];
        }
        else if ((*node_table)[end][j] != 0 && (*node_table)[end][j] != -1 && (*node_table)[end][j] <= second &&
            (*node_table)[end][j] != first)
            second = (*node_table)[end][j];
    }
    return second;
}
bool stop = false;
void TSPSolver::branch_and_bound_method(T_NODE* node_table, int current_bound, int current_weight, int level, vector<int> current_path)
{
    //if (level == node_table->size())

    //vector<int> valid_optimal_route;

    //for (int i = 0; i < current_path.size(); ++i)
    //{
    //    if (current_path[i] == -1)
    //    {
    //        break;
    //    }

    //    valid_optimal_route.push_back(current_path[i]);
    //}
    //current_path.erase(std::remove(current_path.begin(), current_path.end(), -1), current_path.end());

    vector<int>::iterator last_valid_element = std::find(current_path.begin(), current_path.end(), -1);
    int last_valid_element_index = distance(current_path.begin(), last_valid_element) - 1;

    int real_optimal_routes_size = distance(optimal_routes[0].begin(), find(optimal_routes[0].begin(), optimal_routes[0].end(), -1));

    if ((*node_table)[*(--last_valid_element)][current_path[0]] != 0)
    {
        int curr_res = current_weight +
            (*node_table)[current_path[last_valid_element_index]][current_path[0]];

        if ((optimal_routes[0].size() == 0 || last_valid_element_index + 1 > real_optimal_routes_size || (curr_res < optimal_routes_cost && last_valid_element_index + 1 == real_optimal_routes_size)))
        {
            optimal_routes[0] = current_path;
            //optimal_routes[0].push_back(current_path[0]);
            optimal_routes_cost = curr_res;

        }
    }

    //if (level == node_table->size() - current_path[0])
    //{
    //    if ((*node_table)[*(--last_valid_element)][current_path[0]] != 0)
    //    {
    //        int curr_res = current_weight +
    //            (*node_table)[current_path[last_valid_element_index]][current_path[0]];

    //        if ((curr_res < optimal_routes_cost))
    //        {
    //            optimal_routes[0] = current_path;
    //            //optimal_routes[0].push_back(current_path[0]);
    //            optimal_routes_cost = curr_res;
    //        }
    //            

    //    }
    //    return;
    //}


    for (int i = 0; i < node_table->size(); i++)
    {
        if ((*node_table)[current_path[level - 1]][i] != 0 && (*node_table)[current_path[level - 1]][i] != -1 &&
            visited[i] == false)
        {
            int temp = current_bound;
            current_weight += (*node_table)[current_path[level - 1]][i];

            if (level == 1)
                current_bound -= ((first_min_path(node_table, current_path[level - 1]) +
                    first_min_path(node_table, i)) / 2);
            else
                current_bound -= ((second_min_path(node_table, current_path[level - 1]) +
                    first_min_path(node_table, i)) / 2);

            if (current_bound + current_weight < optimal_routes_cost || level > real_optimal_routes_size)
            {
                current_path[level] = i;
                visited[i] = true;

                branch_and_bound_method(node_table, current_bound, current_weight, level + 1,
                    current_path);
            }

            current_weight -= (*node_table)[current_path[level - 1]][i];
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

    T_NODE* valid_nodes_table = new T_NODE(get_valid_nodes_table(init_node));
    vector<int> valid_nodes = get_valid_nodes(init_node);
    int valid_init_point = init_node;

    for (int i = 0; i < valid_nodes.size(); ++i)
    {
        if (valid_nodes[i] == init_node)
            valid_init_point = i;
    }

    completed = vector<int>(valid_nodes_table->size(), 0);

    completed[valid_init_point] = 1;
    optimal_routes[0].push_back(valid_init_point);
    int next_point = min_path(valid_nodes_table, valid_init_point, valid_init_point);

    vector<int> helper_path;
    if (next_point != INT_MAX && reaches_init_point(valid_nodes_table, valid_init_point, next_point, optimal_routes[0], helper_path))
    {
        dynamic_programming_method(valid_nodes_table, valid_init_point, next_point);
    }
    else
    {
        optimal_routes[0].push_back(valid_init_point);
    }

    for (int i = 0; i < optimal_routes[0].size(); ++i)
    {
        optimal_routes[0][i] = valid_nodes[optimal_routes[0][i]];
    }
}

void TSPSolver::solve_branch_and_bound_method(int init_point)
{
    stop = false;
    start_time = chrono::system_clock::now();

    optimal_routes_cost = INT_MAX;
    optimal_routes = vector<vector<int>>();

    T_NODE* valid_nodes_table = new T_NODE(get_valid_nodes_table(init_point));
    vector<int> valid_nodes = get_valid_nodes(init_point);
    int valid_init_point = init_point;

    for (int i = 0; i < valid_nodes.size(); ++i)
    {
        if (valid_nodes[i] == init_point)
            valid_init_point = i;
    }

    //optimal_routes.push_back(vector<int>(valid_nodes_table->size() + 1));
    optimal_routes.push_back(vector<int>());
    visited = vector<bool>(valid_nodes_table->size(), 0);
    vector<int> current_path(valid_nodes_table->size() + 1, -1);

    int current_bound = 0;

    for (int i = 0; i < valid_nodes_table->size(); i++)
        current_bound += (first_min_path(valid_nodes_table, i) +
            second_min_path(valid_nodes_table, i));

    current_bound = (current_bound & 1) ? current_bound / 2 + 1 :
        current_bound / 2;

    visited[valid_init_point] = true;
    current_path[0] = valid_init_point;

    branch_and_bound_method(valid_nodes_table, current_bound, 0, 1, current_path);

    optimal_routes[0].erase(std::remove(optimal_routes[0].begin(), optimal_routes[0].end(), -1), optimal_routes[0].end());

    //optimal_routes_cost += (*valid_nodes_table)[*(--optimal_routes[0].end())][valid_init_point];

    optimal_routes[0].push_back(valid_init_point);

    //optimal_routes[0] = valid_optimal_route;

    for (int i = 0; i < optimal_routes[0].size(); ++i)
    {
        optimal_routes[0][i] = valid_nodes[optimal_routes[0][i]];
    }
}

void TSPSolver::evaluate_nodes(T_NODE subtree, vector<int>& path, int init_node, int origin, int previous_origin)
{
    for (int i = 0; i < subtree.size(); ++i)
    {
        if (origin != i && previous_origin != i && subtree[origin][i] != -1)
        {
            if (i == init_node)
            {
                return;
            }

            evaluate_nodes(subtree, path, init_node, i, origin);
        }
    }


    /*for (int i = 0; i < subtree.size(); ++i)
    {
        vector<int>::iterator it = find(path.begin(), path.end(), i);

        if (origin != i && previous_origin != i && subtree[origin][i] != -1 && subtree[origin][i] != 0 && it == path.end())
        {   
            path.push_back(i);

            evaluate_branches(subtree, path, i, origin);
        }
    }*/
}

void TSPSolver::evaluate_branches(T_NODE* main_node_table, int init_point, T_NODE subtree, vector<int>& path, int origin, int previous_origin = -1)
{
    for (int i = 0; i < subtree.size(); ++i)
    {
        if (origin != i && previous_origin != i && subtree[origin][i] != -1)
        {
            evaluate_branches(main_node_table, init_point, subtree, path, i, origin);
            path.push_back(i);
        }
    }
}
//bool TSPSolver::evaluate_branches(T_NODE subtree, vector<int>& path, int init_point, int origin, int previous_origin)
//{
//    for (int i = 0; i < subtree.size(); ++i)
//    {
//        if (origin != i && previous_origin != i && subtree[origin][i] != -1 && subtree[origin][i] != 0)
//        {
//            if (i == init_point)
//                return true;
//
//            vector<int>::iterator it = find(path.begin(), path.end(), i);
//
//            if (it == path.end())
//                path.push_back(i);
//
//            return evaluate_branches(subtree, path, init_point, i, origin);
//        }
//    }
//
//    return false;
//}
void TSPSolver::solve_approximated_prim_method(int init_point)
{
    start_time = chrono::system_clock::now();

    T_NODE* valid_nodes_table = new T_NODE(get_valid_nodes_table(init_point));
    vector<int> valid_nodes = get_valid_nodes(init_point);
    int valid_init_point = init_point;

    for (int i = 0; i < valid_nodes.size(); ++i)
    {
        if (valid_nodes[i] == init_point)
            valid_init_point = i;
    }

    vector<vector<int>> tree = prim(valid_nodes_table, valid_init_point);
    vector<int> path;

    //for (int i = 0; i < valid_nodes_table.size(); ++i)
        evaluate_branches(valid_nodes_table, valid_init_point, tree, path, valid_init_point);

    optimal_routes.clear();
    optimal_routes.push_back(vector<int>());
    optimal_routes[0].push_back(valid_init_point);

    for (int node : path)
    {
        optimal_routes[0].push_back(node);
    }

    optimal_routes[0].push_back(valid_init_point);

    // Calculating final path cost

    optimal_routes_cost = 0;

    vector<int> final_route;
    final_route.push_back(valid_init_point);
    for (int i = 0; i < optimal_routes[0].size() - 2; ++i)
    {
        vector<int> helper_path;
        if ((*valid_nodes_table)[optimal_routes[0][i]][optimal_routes[0][i + 1]] != 0 && (*valid_nodes_table)[optimal_routes[0][i]][optimal_routes[0][i + 1]] != -1 && reaches_init_point(valid_init_point, optimal_routes[0][i + 1], helper_path))
            final_route.push_back(optimal_routes[0][i + 1]);
    }
    final_route.push_back(valid_init_point);

    optimal_routes[0] = final_route;

    for (int i = 1; i < optimal_routes[0].size() - 1; ++i)
    {
        optimal_routes[0][i] = valid_nodes[optimal_routes[0][i]];
    }

    for (int i = 0; i < optimal_routes[0].size() - 1; ++i)
    {
        optimal_routes_cost += nodes[optimal_routes[0][i]][optimal_routes[0][i + 1]];
    }

}

vector<vector<int>> TSPSolver::prim(T_NODE* node_table, int init_point)
{
    T_NODE table = *node_table;
    vector< vector<int> > tree(node_table->size());
    vector<int> markedLines;
    vector<int> ::iterator vectorIterator;

    for (int i = 0; i < node_table->size(); i++)
        tree[i] = vector<int>(node_table->size(), -1);

    int root = 0;
    int child = 0;
    while (markedLines.size() + 1 < node_table->size()) {
        root = child;
        markedLines.push_back(root);
        for (int i = 0; i < node_table->size(); i++)
            table[i][root] = INT_MAX;

        int min = INT_MAX;
        for (vectorIterator = markedLines.begin(); vectorIterator != markedLines.end(); vectorIterator++)
            for (int i = 0; i < node_table->size(); i++)
                if (min > table[*vectorIterator][i]) {
                    min = table[*vectorIterator][i];
                    root = *vectorIterator;
                    child = i;
                }

        tree[root][child] = min;
        tree[child][root] = min;
    }

    /*for (int i = 0; i < tree.size(); ++i)
    {
        for (int j = 0; j < tree.size(); ++j)
        {
            if (!is_a_valid_node(init_point, j))
                tree[i][j] = -1;
        }
    }*/
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

void TSPSolver::reset()
{
    nodes.clear();
    optimal_routes_cost = INT_MAX;
    optimal_routes = vector<vector<int>>();
}
