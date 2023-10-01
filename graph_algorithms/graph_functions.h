/*#pragma once*/

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>

using namespace std;

const int INF = 1000000000;

void print(vector<int> mas) {
    for (int i = 0; i < mas.size(); i++) {
        cout << mas[i] << " ";
    }
    cout << endl;
}

vector<int> bfs(int s, vector<vector<pair<int, char>>>& graph) {
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
    for (int i = 0; i < graph.size(); i++) {
        bool color_0 = 0, color_1 = 0, color_2 = 0;
        for (int j = 0; j < graph[i].size(); j++) {
            if (graph[i][j].second == 'u') color_0 = 1; // U = 0
            if (graph[i][j].second == 's') color_1 = 1; // S = 1
            if (graph[i][j].second == 't') color_2 = 1; // T = 2
        }
        if (!(color_0 && color_1 && color_2)) {
            cout << "Graph is not 3 colored" << endl;
            return false;
        }
    }
    cout << "Graph is 3 colored" << endl;
    return true;
}

bool is_connected(vector<vector<pair<int, char>>>& graph) {
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

void /*vector<vector<pair<int, char>>>*/ find_su_cycles(vector<vector<pair<int, char>>>& graph) {
    vector<int> used_v(0);
    /* */

}

vector<int> find_cycle(char color1, char color2, char prev_color, int cur_v, int prev_v, vector<vector<pair<int, char>>>& graph, vector<string>& color, vector<int> parent) {
    color[cur_v] = "grey";
    for (int i = 0; i < graph[cur_v].size(); i++) {
        if (graph[cur_v][i].second != prev_color && (graph[cur_v][i].second == color1 || graph[cur_v][i].second == color2)) {
            if (color[graph[cur_v][i].first] == "white") {
                parent.push_back(cur_v);
                find_cycle(color1, color2, graph[cur_v][i].second, graph[cur_v][i].first, cur_v, graph, color, parent);
            }
            if (color[graph[cur_v][i].first] == "grey" && graph[cur_v][i].first != prev_v) {
                int k = 0;
                for (int j = 0; j < parent.size(); j++) {
                    if (parent[j] == parent[parent.size() - 1]) {
                        k = j + 1;
                    }
                }
                vector<int> cycle(parent.size() - k, 0);
                for (int i = k; i < parent.size(); i++) {
                    cycle[i - k] = parent[k];
                }
                return cycle;
            }
        }
    }
    color[cur_v] = "black";
}