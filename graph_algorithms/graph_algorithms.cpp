#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

class Node {
    friend Graph;
    Node(); // TODO node constructor
    void push(int id, int color) {
        neighbours.push_back(make_pair(id, color));
    }
    int marked = 0;
    int id; // TODO correct id maker 
    // TODO copying operator
    vector<pair<int, int>> neighbours;
};

class Graph {
    vector<Node> nodes;
    int verticles_number = 0;
    Graph() {
        int nodes_number;
        cin >> nodes_number;
        vector<vector<int>> temp_nodes(nodes_number, vector<int>());
        for (int i = 0; i < nodes_number; i++) {
            int node_number;
            Node versus(); // TODO clearify this moment
            while (cin >> node_number) {
                temp_nodes[i].push_back(node_number);
                versus.push(node_number);
            }
        }
    }
};

// TODO write basic BFS algorithm

// TODO write funcs for graph

int main()
{
    std::cout << "Hello World!\n";
}