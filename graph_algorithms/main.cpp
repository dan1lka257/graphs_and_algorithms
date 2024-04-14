#include "graph_functions.h"

int main()
{
    vector<vector<pair<int, char>>> graph;
    graph = { { {7, 't'}, { 7, 's'}, { 5, 'u'} },
            { {2, 't'}, {2, 's'}, {4, 'u'} },
            { {1, 't'}, {1, 's'}, {3, 'u'} },
            { {6, 't'}, {4, 's'}, {2, 'u'} },
            { {5, 't'}, {3, 's'}, {1, 'u'} },
            { {4, 't'}, {6, 's'}, {0, 'u'} },
            { {3, 't'}, {5, 's'}, {7, 'u'} },
            { {0, 't'}, {0, 's'}, {6, 'u'} } };
    print_dynamical_system_info(graph);
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
    vector<vector<vector<pair<int, char>>>> graphs = graph_generator(-2, 8);
    for (int i = 0; i < graphs.size(); i++) {
        cout << "----------------------\n";
        for (int j = 0; j < graphs[i].size(); j++) {
            cout << j << "\t";
            for (int k = 0; k < graphs[i][j].size(); k++) {
                cout << graphs[i][j][k].first << " " << graphs[i][j][k].second << "\t";
            }
            cout << "\n";
        }
        print_dynamical_system_info(graphs[i]);
    }
    system("pause");
}
