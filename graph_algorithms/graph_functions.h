/*#pragma once*/
// Pragma shall be on when there will be prototyps of functions

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>

using namespace std;

const int INF = 1000000000;

void print(vector<int> mas) {
    // Prints vector into console
    for (int i = 0; i < mas.size(); i++) {
        cout << mas[i] << " ";
    }
    cout << endl;
}

vector<int> bfs(int s, vector<vector<pair<int, char>>>& graph) {
    // BFS which find distance to other verticles
    int n = graph.size();
    vector<int> dist(n, INF);
    dist[s] = 0;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (pair<int, int> u : graph[v]) {
            if (dist[u.first] > dist[v] + 1) {
                dist[u.first] = dist[v] + 1;
                q.push(u.first);
            }
        }
    }

    return dist;
}

bool is_3_colored_and_non_oriented(vector<vector<pair<int, char>>>& graph) {
    // Check graph on tricolor
    // 1 edge of each of 3 colors in one verticle

    // ENTERED GRAPH MUST BE INVOLVED IS SCTRICT REQUIREMENTS

    for (int i = 0; i < graph.size(); i++) {
        bool color_u = 0, color_s = 0, color_t = 0;
        for (int j = 0; j < graph[i].size(); j++) {
            if (graph[i][j].second == 'u') color_u += 1;
            if (graph[i][j].second == 's') color_s += 1;
            if (graph[i][j].second == 't') color_t += 1;
        }
        bool oriented = 1;
        for (int j = 0; j < graph[i].size(); j++) {
            if (graph[i][j].first != graph[graph[i][j].first][j].first) oriented == 0;
        }
        if (!(color_u == 1 && color_s == 1 && color_t == 1)) {
            cout << "Graph is not 3 colored" << endl;
            return false;
        }
        if (!(oriented)) {
            cout << "Graph is not oriented" << endl;
            return false;
        }
    }
    return true;
}

bool is_connected(vector<vector<pair<int, char>>>& graph) {
    // Check graph is connected or not
    vector<int> dist = bfs(0, graph);
    int max_dist = 0;
    for (int j = 0; j < dist.size(); j++) {
        max_dist = max(max_dist, dist[j]);
    }
    if (max_dist == INF) {
        return false;
    }
    return true;
}

vector<int> find_cycle(char color1, char color2, char prev_color, int cur_v, int prev_v, vector<vector<pair<int, char>>>& graph, vector<string>& color, vector<int>& parent) {
    // Standard cycle finding taking into account its bicolor
    color[cur_v] = "grey";
    for (int i = 0; i < graph[cur_v].size(); i++) {
        if (graph[cur_v][i].second != prev_color && (graph[cur_v][i].second == color1 || graph[cur_v][i].second == color2)) {
            if (color[graph[cur_v][i].first] == "white") {
                parent.push_back(cur_v);
                return find_cycle(color1, color2, graph[cur_v][i].second, graph[cur_v][i].first, cur_v, graph, color, parent);
            }
            if (color[graph[cur_v][i].first] == "grey" && graph[cur_v][i].first != prev_v && cur_v != prev_v) {
                parent.push_back(cur_v);
                /*int k = 0;
                for (int j = 0; j < parent.size(); j++) {
                    if (parent[j] == parent[parent.size() - 1]) {
                        k = j + 1;
                    } else {
                        break;
                    }            THIS COD MUST DESCREASE PARENT TREE TO CYCLE BUT WE DONT NEED IT BECAUSE OF GRAPH BUILDING
                }
                vector<int> cycle(parent.size() - k, 0);
                for (int i = k; i < parent.size(); i++) {
                    cycle[i - k] = parent[k];
                }*/
                return parent;
            }
        }
    }
    parent.push_back(cur_v);
    color[cur_v] = "black";
    return parent;
}

vector<vector<int>> find_cycles(vector<vector<pair<int, char>>>& graph, char color1, char color2) {
    // Find bicolored cycles in graph
    int n = graph.size();
    vector<int> used_v(n, 0);
    vector<vector<int>> cycles;
    for (int i = 0; i < n; i++) {
        if (!used_v[i]) {
            vector<string> color(n, "white");
            vector<int> parent;
            vector<int> cycle = find_cycle(color1, color2, 'o', i, i, graph, color, parent);
            if (cycle.empty()) {
                continue;
            }
            for (int j = 0; j < cycle.size(); j++) {
                used_v[cycle[j]] = 1;
            }
            cycles.push_back(cycle);
        }
    }
    return cycles;
}

bool is_acceptable(vector<vector<pair<int, char>>>& graph) {
    // Lenght of su-cycle is equal 4 and graph is connected
    vector<vector<int>> cycles = find_cycles(graph, 's', 'u');
    bool su_cycle_is_4 = 1;
    for (int i = 0; i < cycles.size(); i++) {
        if (cycles[i].size() != 4) {
            su_cycle_is_4 = 0;
        }
    }
    return su_cycle_is_4 && is_connected(graph) && is_3_colored_and_non_oriented(graph);
}

int count_euler_number(vector<vector<pair<int, char>>>& graph) {
    // Euler number = tu - su + st
    return find_cycles(graph, 'u', 't').size() - find_cycles(graph, 's', 'u').size() + find_cycles(graph, 's', 't').size();
}

bool is_oriented_surface(vector<vector<pair<int, char>>>& graph) {
    // Graph is on oriented surface <=> length of all cycles is even
    // WRONG CODE - ANY CYCLE MUST BE EVEN
    bool is_even = true;
    vector<vector<int>> cycles(0);
    vector<vector<int>> cycles_ut = find_cycles(graph, 'u', 't');
    vector<vector<int>> cycles_su = find_cycles(graph, 's', 'u');
    vector<vector<int>> cycles_st = find_cycles(graph, 's', 't');
    cycles.insert(cycles.end(), cycles_ut.begin(), cycles_ut.end());
    cycles.insert(cycles.end(), cycles_su.begin(), cycles_su.end());
    cycles.insert(cycles.end(), cycles_st.begin(), cycles_st.end());
    for (int i = 0; i < cycles.size(); i++) {
        if (cycles[i].size() % 2 != 0) {
            is_even = false;
        }
    }
    return is_even;
}

void print_dynamical_system_info(vector<vector<pair<int, char>>>& graph) {
    // Print dynamical system info
    cout << "Is acceptable graph?\t" << is_acceptable(graph) << "\n";
    cout << "Is oriented surface?\t" << is_oriented_surface(graph) << "\n";
    cout << "Euler Number\t\t" << count_euler_number(graph) << "\n";
    cout << "Number of sources\t" << find_cycles(graph, 's', 't').size() << "\n";
    cout << "Number of saddles\t" << find_cycles(graph, 'u', 's').size() << "\n";
    cout << "Number of drains\t" << find_cycles(graph, 'u', 't').size() << "\n";
    // TODO: isomorphism & python and c++ connection & drawing on sphere
}

vector<vector<vector<pair<int, char>>>> graph_generator(int euler_number, int saddles) {
    vector<vector<vector<pair<int, char>>>> graphs(0);
    // Generating primal graph
    vector<vector<pair<int, char>>> graph(0);
    for (int i = 0; i < saddles * 4; i++) {
        vector<pair<int, char>> neighbours;
        if (i == 0) { // first verticle
            neighbours = { {i + 1, 't'}, {i + 2, 's'}, {i + 1, 'u'} };
        } else if (i == 1) { // second verticle
            neighbours = { {i - 1, 't'}, {i + 2, 's'}, {i - 1, 'u'} };
        } else if (i == saddles * 4 - 1) { // last verticle
            neighbours = { {i - 1, 't'}, {i - 2, 's'}, {i - 1, 'u'} };
        } else if (i == saddles * 4 - 2) { // penultimate verticle
            neighbours = { {i + 1, 't'}, {i - 2, 's'}, {i + 1, 'u'} };
        } else if (i % 4 == 0) {
            neighbours = { {i - 2, 't'}, {i + 2, 's'}, {i + 1, 'u'} };
        } else if (i % 4 == 1) {
            neighbours = { {i - 2, 't'}, {i + 2, 's'}, {i - 1, 'u'} };
        } else if (i % 4 == 2) {
            neighbours = { {i + 2, 't'}, {i - 2, 's'}, {i + 1, 'u'} };
        } else if (i % 4 == 3) {
            neighbours = { {i + 2, 't'}, {i - 2, 's'}, {i - 1, 'u'} };
        }
        graph.push_back(neighbours);
    }
    // operating with euler number
    if (2 - euler_number > saddles) {
        cout << "Uncorrect input: number of saddles must be lower or equal than (2 - euler_number)\n";
        return graphs;
    }
    for (int i = euler_number; i < 2; i += 2) {
        int j = 8 * (i - euler_number) / 2;
        if (euler_number == 0 && saddles == 2) { // usual torus
            graph[j][0].first = j + 1;
            graph[j + 1][0].first = (j + 1) - 1;
            graph[j + 2][0].first = (j + 2) + 4;
            graph[j + 3][0].first = (j + 3) + 1;
            graph[j + 4][0].first = (j + 4) - 1;
            graph[j + 5][0].first = (j + 5) + 2;
            graph[j + 6][0].first = (j + 6) - 4;
            graph[j + 7][0].first = (j + 7) - 2;
        } else if (i == euler_number) { // First step
            if (2 - euler_number < saddles) {
                graph[j][0].first = 8 * (2 - euler_number) / 2 + 1;
            } else {
                graph[j][0].first = 8 * (2 - euler_number) / 2 - 1;
            }
            graph[j + 1][0].first = (j + 1) + 4;
            graph[j + 2][0].first = (j + 2) + 4;
            graph[j + 3][0].first = (j + 3) + 1;
            graph[j + 4][0].first = (j + 4) - 1;
            graph[j + 5][0].first = (j + 5) - 4;
            graph[j + 6][0].first = (j + 6) - 4;
            graph[j + 7][0].first = (j + 7) + 1; // non-oriented graph
            graph[(j + 7) + 1][0].first = j + 7; // non-oriented graph
        } else if (i == 2 - 2 && 2 - euler_number == saddles) { // Last step
            graph[j][0].first = j - 1;
            graph[j + 1][0].first = (j + 1) + 4;
            graph[j + 2][0].first = (j + 2) + 4;
            graph[j + 3][0].first = (j + 3) + 1;
            graph[j + 4][0].first = (j + 4) - 1;
            graph[j + 5][0].first = (j + 5) - 4;
            graph[j + 6][0].first = (j + 6) - 4;
            graph[j + 7][0].first = 0;
        } else {
            graph[j][0].first = j - 1;
            graph[j + 1][0].first = (j + 1) + 4;
            graph[j + 2][0].first = (j + 2) + 4;
            graph[j + 3][0].first = (j + 3) + 1;
            graph[j + 4][0].first = (j + 4) - 1;
            graph[j + 5][0].first = (j + 5) - 4;
            graph[j + 6][0].first = (j + 6) - 4;
            graph[j + 7][0].first = (j + 7) + 1; // non-oriented graph
            graph[(j + 7) + 1][0].first = j + 7; // non-oriented graph
        }
    }
    graphs.push_back(graph);
    for (int i = (2 - euler_number) + 1; i < saddles; i += 2) {
        int j = i * 4;
        if (i == saddles - 1) {
            graph[j][0].first = j - 1;
            graph[j - 1][0].first = j;

            graph[j + 1][0].first = (j + 1) + 2; //equal
            graph[(j + 1) + 2][0].first = j + 1;


            graph[j + 2][0].first = (j + 2) - 4;
            graph[(j + 2) - 4][0].first = j + 2;

            graph[j + 3][0].first = (j + 3) - 2; // equal
            graph[(j + 3) - 2][0].first = j + 3;
        } else {
            graph[j][0].first = j - 1;
            graph[j - 1][0].first = j;

            graph[j + 1][0].first = (j + 1) + 4;
            graph[(j + 1) + 4][0].first = j + 1;


            graph[j + 2][0].first = (j + 2) - 4;
            graph[(j + 2) - 4][0].first = j + 2;

            graph[j + 3][0].first = (j + 3) + 1;
            graph[(j + 3) + 1][0].first = j + 3;
        }
        graphs.push_back(graph);
    }
    int fixed_size = graphs.size();
    for (int i = 0; i < fixed_size; i++) {
        vector<vector<pair<int, char>>> graph_reverse(0);
        graph_reverse.assign(graphs[i].begin(), graphs[i].end());
        for (int j = 0; j < graph_reverse.size(); j++) {
            int c = graph_reverse[j][1].first;
            graph_reverse[j][1].first = graph_reverse[j][2].first;
            graph_reverse[j][2].first = c;
        }
        graphs.push_back(graph_reverse);
    }
    return graphs;
}

vector<pair<char, vector<int>>> find_neighbors(vector<vector<pair<int, char>>>& graph) {
    vector<pair<char, vector<int>>> cycles(0);
    // Sourses
    vector<vector<int>> cycles_st = find_cycles(graph, 's', 't');
    vector<pair<char, vector<int>>> a_cycles(0);
    for (int i = 0; i < cycles_st.size(); i++) {
        a_cycles.push_back(make_pair('a', cycles_st[i]));
    }
    // Drains
    vector<vector<int>> cycles_ut = find_cycles(graph, 'u', 't');
    vector<pair<char, vector<int>>> o_cycles(0);
    for (int i = 0; i < cycles_ut.size(); i++) {
        a_cycles.push_back(make_pair('o', cycles_ut[i]));
    }
    // Saddles
    vector<vector<int>> cycles_su = find_cycles(graph, 's', 'u');
    vector<pair<char, vector<int>>> s_cycles(0);
    for (int i = 0; i < cycles_su.size(); i++) {
        a_cycles.push_back(make_pair('s', cycles_su[i]));
    }
    // Uniting
    cycles.insert(cycles.end(), a_cycles.begin(), a_cycles.end());
    cycles.insert(cycles.end(), o_cycles.begin(), o_cycles.end());
    cycles.insert(cycles.end(), s_cycles.begin(), s_cycles.end());
    for (int i = 0; i < cycles.size(); i++) {
        cout << i << " " << cycles[i].first << " ";
        for (int j = 0; j < cycles[i].second.size(); j++) {
            cout << cycles[i].second[j] << " ";
        }
        cout << "\n";
    }
    // Cycles-neighbors finding
    int alphas = cycles_st.size();
    int omegas = cycles_ut.size();
    int sigmas = cycles_su.size();
    vector<pair<char, vector<int>>> neighbors(0);
    for (int i = 0; i < cycles.size(); i++) { // O(n^2) cycles
        vector<int> empty_vector(0);
        neighbors.push_back(make_pair(cycles[i].first, empty_vector));
        char i_cycle_type = cycles[i].first;
        for (int j = 0; j < cycles[i].second.size(); j++) {
            int a1 = cycles[i].second[j];
            int a2 = cycles[i].second[(j + 1) % cycles[i].second.size()];
            bool is_found = false;
            for (int k = 0; k < cycles.size(); k++) {
                char k_cycle_type = cycles[k].first;
                if ((i_cycle_type == 'a' && k_cycle_type == 's') || (i_cycle_type == 'o' && k_cycle_type == 's') || (i_cycle_type == 's' && ((k_cycle_type == 'a' && graph[a1][1].first == a2) || (k_cycle_type == 'o' && graph[a1][2].first == a2)))) {
                    if (k == i) {
                        continue;
                    }
                    for (int t = 0; t < cycles[k].second.size(); t++) {
                        int b1 = cycles[k].second[t];
                        int b2 = cycles[k].second[(t + 1) % cycles[k].second.size()];
                        if ((a1 == b1 && a2 == b2) || (a1 == b2 && a2 == b1)) {
                            neighbors[i].second.push_back(k);
                            is_found == true;
                            break;
                        }
                    }
                }
                if (is_found) {
                    break;
                }
            }
        }
    }
    return neighbors;
}
