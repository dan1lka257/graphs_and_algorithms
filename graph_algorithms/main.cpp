#include "graph_functions.h"
#include <fstream>

int main() {
    ifstream fin;
    ofstream fout;
    fin.open("../tocpp.txt");

    // ENTERED GRAPH MUST BE INVOLVED IS SCTRICT REQUIREMENTS
    // DYNAMICAL SYSTEM INFO TESTING
    vector<vector<pair<int, char>>> graph;
    graph = { { {1, 't'}, { 5, 's'}, { 15, 'u'} },
            { {0, 't'}, {2, 's'}, {14, 'u'} },
            { {3, 't'}, {1, 's'}, {13, 'u'} },
            { {2, 't'}, {4, 's'}, {10, 'u'} },
            { {5, 't'}, {3, 's'}, {9, 'u'} },
            { {4, 't'}, {0, 's'}, {6, 'u'} },
            { {7, 't'}, {15, 's'}, {5, 'u'} },
            { {6, 't'}, {12, 's'}, {8, 'u'} },
            { {9, 't'}, {11, 's'}, {7, 'u'} },
            { {8, 't'}, {10, 's'}, {4, 'u'} },
            { {11, 't'}, {9, 's'}, {3, 'u'} },
            { {10, 't'}, {8, 's'}, {12, 'u'} },
            { {13, 't'}, {7, 's'}, {11, 'u'} },
            { {12, 't'}, {14, 's'}, {2, 'u'} },
            { {15, 't'}, {13, 's'}, {1, 'u'} },
            { {14, 't'}, {6, 's'}, {0, 'u'} } };
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

    // GRAPH GENERATOR TESTING
    /*
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
    }*/

    // FIND NEIGHBORS TESTING
    /*vector<vector<vector<pair<int, char>>>> graphs = graph_generator(2, 8);
    print_dynamical_system_info(graphs[1]);
    vector<pair<char, vector<int>>> neighbors = find_neighbors(graphs[1]);
    for (int i = 0; i < neighbors.size(); i++) {
        cout << i << " " << neighbors[i].first << " ";
        for (int j = 0; j < neighbors[i].second.size(); j++) {
            cout << neighbors[i].second[j] << " ";
        }
        cout << "\n";
    }*/
    vector<vector<vector<pair<int, char>>>> graphs = graph_generator(2, 8);
    vector<pair<char, vector<float>>> separatres_coords = find_separatres_coords(graphs[6]);
    /*for (int i = 0; i < separatres_coords.size(); i++) {
        cout << separatres_coords[i].first << " ";
        for (int j = 0; j < separatres_coords[i].second.size(); j++) {
            cout << separatres_coords[i].second[j] << " ";
        }
        cout << "\n";
    }*/

    fout.open("../separatres.txt", ios::trunc);
    for (int i = 0; i < separatres_coords.size(); i++) {
        fout << separatres_coords[i].first << " ";
        for (int j = 0; j < separatres_coords[i].second.size(); j++) {
            fout << separatres_coords[i].second[j] << " ";
        }
        fout << "\n";
    }
    fout.close();

    vector<pair<int, pair<float, float>>> dots_coords = find_dots_coords(graphs[6]);
    fout.open("../dots.txt", ios::trunc);
    for (int i = 0; i < dots_coords.size(); i++) {
        fout << dots_coords[i].first << " " << dots_coords[i].second.first << " " << dots_coords[i].second.second << "\n";
    }
    fout.close();
    fin.close();
    return 0;
}
