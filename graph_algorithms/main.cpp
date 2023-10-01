#include "graph_functions.h"

/*
Задание с дедлайном до 1.10
1) Реализовать ДФС с поиском цикла, используя массив предков
2) Все найденные циклы измерить и посчитать
3) По числу эйлера найти тип поверхности (Теор 1, Теор 2)
5) Придумать графы для тестов
6) Обвесить все функции тестами (google test, habr)
7) Оформить всё в латехе
*/

int main()
{
    vector<vector<pair<int, char>>> enter1;
    enter1 = { { {2, 'u'}, { 3, 'u' } }, {}, { {0, 'u'}, {3, 'u'} }, { {0, 'u'}, {2, 'u'} } };
    print(bfs(0, enter1));
    /*std::cout << "graph\n";
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, char>>> graph(n, vector<pair<int, char>>());
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back(make_pair(b, c));
        graph[b].push_back(make_pair(a, c));
    }*/

    /* DEBUG GRAPH COUT
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < graph[i].size(); j++) {
            cout << "in" << graph[i][j].first << "for" << graph[i][j].second << " ";
        }
        cout << endl;
    }
    */

    system("pause");
}