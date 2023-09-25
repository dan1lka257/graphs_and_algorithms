#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string>

using namespace std;

const int INF = 1e9;

/*
Задание с дедлайном до 1.10
1) Реализовать ДФС с поиском цикла, используя массив предков
2) Все найденные циклы измерить и посчитать
3) По числу эйлера найти тип поверхности (Теор 1, Теор 2)
4) Организовать ввод и вывод из файла
5) Придумать графы для тестов
6) Обвесить все функции тестами (google test, habr)
7) Оформить всё в латехе
*/

vector<int> bfs(int s, vector<vector<pair<int, int>>>& graph) {
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

void print(vector<int> mas) {
    for (int i = 0; i < mas.size(); i++) {
        cout << mas[i] << " ";
    }
    cout << endl;
}

bool is_3_colored(vector<vector<pair<int, int>>>& graph) {
    for (int i = 0; i < graph.size(); i++) {
        bool color_0 = 0, color_1 = 0, color_2 = 0;
        for (int j = 0; j < graph[i].size(); j++) {
            if (graph[i][j].second == 0) color_0 = 1; // U = 0
            if (graph[i][j].second == 1) color_1 = 1; // S = 1
            if (graph[i][j].second == 2) color_2 = 1; // T = 2
        }
        if (!(color_0 && color_1 && color_2)) {
            cout << "Graph is not 3 colored" << endl;
            return false;
        }
    }
    cout << "Graph is 3 colored" << endl;
    return true;
}

bool is_connected(vector<vector<pair<int, int>>>& graph) {
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

vector<vector<pair<int, int>>> find_su_cycles(vector<vector<pair<int, int>>>& graph) {
    vector<int> used_v(/*n, 0*/);
    /* */

}

queue<int> find_cycle(int s, int p, vector<vector<pair<int, int>>>& graph, vector<string>& color, queue<int> parent) {
    color[s] = "grey";
    for(int i = 0; i < graph[s].size(); i++) {
        if (color[i] == "white") {
            parent.push(s);
            find_cycle(i, s, graph, color, parent);
        }
        if (color[i] == "grey" && i != p) {
            return parent;
        }
    color[s] == "black";
    }
}



int main()
{
    std::cout << "Hello World!\n";
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>> ());
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back(make_pair(b, c));
        graph[b].push_back(make_pair(a, c));
    }




    /* DEBUG GRAPH COUT
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < graph[i].size(); j++) {
            cout << "in" << graph[i][j].first << "for" << graph[i][j].second << " ";
        }
        cout << endl;
    }
    */
}
