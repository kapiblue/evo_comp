#include "hea.h"
#include "local_search_solver.h"
#include "solution.h"
#include "random_solution.h"
#include "utils.h"

#include <random>
#include <iostream>
#include <chrono>

using namespace std;
using namespace N;

HEA::HEA(string instance_filename,
         double fraction_nodes,
         int population_size)
{
    RandomSolution initial_solution = RandomSolution();
    initial_solution.generate(200, 100);
    this->solver = new LocalSearchSolver(instance_filename,
                                         fraction_nodes,
                                         initial_solution);
    this->population_size = population_size;
}

void HEA::init_population()
{
    int total_nodes = this->solver->get_total_nodes();
    int n_nodes = this->solver->get_n_nodes();
    int counter = 0;
    while (counter < this->population_size)
    {
        // Generate a random solution
        RandomSolution new_solution = RandomSolution();
        new_solution.generate(total_nodes, n_nodes);
        // Run greedy local search on the solution
        this->solver->set_initial_solution_copy(new_solution);
        this->solver->run_basic("TWO_EDGES", "GREEDY");
        int new_solution_eval = this->solver->get_best_solution_eval();
        if (!this->population.contains(new_solution_eval))
        {
            this->population[new_solution_eval] = this->solver->get_best_full_solution();
            counter++;
        }
    }
}

void HEA::print_population()
{
    cout << "POPULATION" << endl;
    int i = 0;
    for (auto &[key, value] : this->population)
    {
        cout << i << " : " << key << endl;
        // value.print();
        i++;
    }
}

void HEA::run(double time, bool local_search)
{

    auto start = std::chrono::steady_clock::now();
    // Initialize population
    this->init_population();
    this->print_population();
    int counter = 0;
    while (true)
    {
        auto end = std::chrono::steady_clock::now();
        double so_far = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        if (so_far > time)
        {
            break;
        }
        // Randomly select parents
        pair<int, int> parent_keys = this->select_parent_keys();

        int random_operator = rand() % 2; // tutaj tak ustawiłem bo ten operator 1 w zasadzie nie pomaga wgl
        if (random_operator == 0)
        {
            this->operator1(parent_keys.first,
                                      parent_keys.second); // ten operator dodaje randomowe nody na końcu rozwiązania
        }
        else
        {
            this->operator2(parent_keys.first,
                                      parent_keys.second, local_search); // ten operator uzupełnia rozwiązanie heurystyką
        }

        // this->population[parent_keys.first].print();
        // this->population[parent_keys.second].print();
        // tmp_sol.print();

        int new_solution_eval = this->solver->get_best_solution_eval();
        if (!this->population.contains(new_solution_eval))
        {
            this->population[new_solution_eval] = this->solver->get_best_full_solution();
            // this->print_population();
            this->population.erase(prev(this->population.end())); // remove the worst solution
            // this->print_population();
        }
        counter++;
    }
    this->print_population();
    this->iter_count.push_back(counter);
    cout << "ITER COUNT " << counter << endl;
}

void HEA::operator1(int parent1_key, int parent2_key)
{
    Solution parent1 = this->population[parent1_key];
    Solution parent2 = this->population[parent2_key];

    int idx = 0;
    while (idx < parent1.get_nodes().size())
    {
        bool is_part_of_edge = this->is_part_of_any_edge(parent1, parent2, idx);

        if (!is_part_of_edge)
        {
            parent1.remove_node(idx);
        }
        else
        {
            idx++;
        }
    } // tutaj usuwamy z parent 1 niepowtarzające się krawędzie a co za tym idzie nody

    int node_id;
    while (parent1.get_nodes().size() < 100)
    {
        node_id = rand() % 200;

        if (!parent1.contains(node_id))
        {
            parent1.add_node(node_id);
        }
    }
    this->solver->set_initial_solution_copy(parent1);
}

void HEA::operator2(int parent1_key, int parent2_key, bool local_search)
{
    Solution parent1 = this->population[parent1_key];
    Solution parent2 = this->population[parent2_key];
    int idx = 0;
    while (idx < parent1.get_nodes().size())
    {
        bool is_part_of_edge = this->is_part_of_any_edge(parent1, parent2, idx);

        if (!is_part_of_edge)
        {
            parent1.remove_node(idx);
        }
        else
        {
            idx++;
        }
    } // tutaj usuwamy z parent 1 niepowtarzające się krawędzie a co za tym idzie nody

    vector<int> tmp_sol;
    this->solver->set_initial_solution_copy(parent1);
    this->solver->greedy_cycle_repair(&tmp_sol);

    parent1.set_nodes(tmp_sol);
    parent1.update_selected();

    this->solver->set_initial_solution_copy(parent1);
    if (local_search)
    {
        this->solver->run_basic("TWO_EDGES", "GREEDY");
    }
}

// sprawdzamy czy wierzchołek o podanym indeksie w rodzicu1 jest częścią pewnej krawędzi
// występującyj również w rodzicu2, jeżeli nie będziemy chcieli go usunąć
bool HEA::is_part_of_any_edge(Solution parent1, Solution parent2, int idx)
{

    int prev_idx = parent1.get_prev_node_idx(idx);
    int next_idx = parent2.get_next_node_idx(idx);

    if (this->contain_edge(parent1, parent2, prev_idx, idx) ||
        this->contain_edge(parent1, parent2, idx, next_idx))
    {
        return true;
    }
    return false;
}

// sprawdzamy czy krawędź występująca w rodzicu1 (z wierzchołkami o podanych indeksach), występuje również w rodzicu2 na dowolnej pozycji
bool HEA::contain_edge(Solution parent1, Solution parent2, int begin_edge_idx, int end_edge_idx)
{
    int edge_begin = parent1.get_node_at_idx(begin_edge_idx);
    int edge_end = parent1.get_node_at_idx(end_edge_idx);

    if (parent2.contains(edge_begin) && parent2.contains(edge_end))
    {
        for (int idx = 0; idx < parent2.get_nodes().size(); idx++)
        {
            int next_idx = parent2.get_next_node_idx(idx);
            int prev_idx = parent2.get_prev_node_idx(idx);

            if (
                (edge_begin == parent2.get_node_at_idx(prev_idx) && edge_end == parent2.get_node_at_idx(idx)) ||
                (edge_end == parent2.get_node_at_idx(prev_idx) && edge_begin == parent2.get_node_at_idx(idx)) ||
                (edge_begin == parent2.get_node_at_idx(idx) && edge_end == parent2.get_node_at_idx(next_idx)) ||
                (edge_end == parent2.get_node_at_idx(idx) && edge_begin == parent2.get_node_at_idx(prev_idx)))
            {
                return true;
            }
        }
    }

    return false;
}

pair<int, int> HEA::select_parent_keys()
{
    int population_size = this->population.size();
    int first_parent_idx = rand() % population_size;
    int second_parent_idx = rand() % population_size;
    while (first_parent_idx == second_parent_idx)
    {
        second_parent_idx = rand() % population_size;
    }
    return make_pair(next(this->population.begin(), first_parent_idx)->first,
                     next(this->population.begin(), second_parent_idx)->first);
}

void HEA::reset()
{
    this->population.clear();
}

vector<int> HEA::get_iter_count()
{
    return this->iter_count;
}