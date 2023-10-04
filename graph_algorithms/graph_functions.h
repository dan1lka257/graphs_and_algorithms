/*#pragma once*/
// Прагму включить тогда, когда здесь будут только прототипы функций, а сами функции будут в отдельном файле

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>

using namespace std;

const int INF = 1000000000;

void print(vector<int> mas) {
    // Выводит вектор в консоль
    for (int i = 0; i < mas.size(); i++) {
        cout << mas[i] << " ";
    }
    cout << endl;
}

vector<int> bfs(int s, vector<vector<pair<int, char>>>& graph) {
    // БФС, ищет расстояние от вершины s до остальных 
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

bool is_3_colored(vector<vector<pair<int, char>>>& graph) {
    // Проверяет граф на трёхцветность
    // По одному ребру каждого из 3-х цветов из каждой вершины
    for (int i = 0; i < graph.size(); i++) {
        bool color_u = 0, color_s = 0, color_t = 0;
        for (int j = 0; j < graph[i].size(); j++) {
            if (graph[i][j].second == 'u') color_u += 1;
            if (graph[i][j].second == 's') color_s += 1;
            if (graph[i][j].second == 't') color_t += 1;
        }
        if (!(color_u == 1 && color_s == 1 && color_t == 1)) {
            cout << "Graph is not 3 colored" << endl;
            return false;
        }
    }
    cout << "Graph is 3 colored" << endl;
    return true;
}

bool is_connected(vector<vector<pair<int, char>>>& graph) {
    // Проверяет граф на связность
    vector<int> dist = bfs(0, graph);
    int max_dist = 0;
    for (int j = 0; j < dist.size(); j++) {
        max_dist = max(max_dist, dist[j]);
    }
    if (max_dist == INF) {
        cout << "Graph is not connected" << endl;
        return false;
    }
    cout << "Graph is connected" << endl;
    return true;
}

vector<int> find_cycle(char color1, char color2, char prev_color, int cur_v, int prev_v, vector<vector<pair<int, char>>>& graph, vector<string>& color, vector<int>& parent) {
    // Стандартный поиск цикла с учётом его двухцветности
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
                    }            ЭТОТ КОД ДОЛЖЕН СОКРАЩАТЬ ДЕРЕВО ПРЕДКОВ ДО ЦИКЛА НО ОН НЕ НУЖЕН В СИЛУ ПОСТРОЕНИЯ ГРАФА
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
    // Ищет двухцветные циклы в графе
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
            print(cycle);
        }
    }
    return cycles;
}

bool is_acceptable(vector<vector<pair<int, char>>>& graph) {
    // Длина любого su-цикла равна 4 и граф связен
    vector<vector<int>> cycles = find_cycles(graph, 's', 'u');
    bool su_cycle_is_4 = 1;
    for (int i = 0; i < cycles.size(); i++) {
        if (cycles[i].size() != 4) {
            su_cycle_is_4 = 0;
        }
    }
    return su_cycle_is_4 && is_connected(graph);
}

int count_euler_number(vector<vector<pair<int, char>>>& graph) {
    // Число Эйлера = tu - su + st
    return find_cycles(graph, 'u', 't').size() - find_cycles(graph, 's', 'u').size() + find_cycles(graph, 's', 't').size();
}

void print_dynamical_system_info(vector<vector<pair<int, char>>>& graph) {
    // Выводит общую информацию о динамической системе по графу
    cout << "Количество источников\t" << find_cycles(graph, 's', 't').size() << "\n";
    cout << "Количество сёдел\t" << find_cycles(graph, 'u', 's').size() << "\n";
    cout << "Количество стоков\t" << find_cycles(graph, 'u', 't').size() << "\n";
    cout << "Число Эйлера\t" << find_cycles(graph, 'u', 't').size() << "\n";
    // TODO: Ориентируема ли поверхность или нет, тип поверхности
    // TODO: Написать проверку на ориентируемость
}