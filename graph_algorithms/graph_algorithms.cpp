#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

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