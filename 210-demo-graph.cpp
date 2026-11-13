#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
using namespace std;

const int SIZE = 11;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // (neighbor station, travel time in minutes)

// Station names, indexed by vertex number
const string STATIONS[SIZE] = {
    "Central Station",
    "Riverside",
    "Oak Park",
    "Harbor View",
    "University",
    "Market Square",
    "Airport",
    "Hillcrest",
    "Stadium",
    "Lakeside",
    "Industrial Park"
};

class Graph {
public:
    // adjacency list: each station holds its (neighbor, minutes) pairs
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        // add each track segment in both directions (undirected graph)
        for (auto &edge : edges) {
            adjList[edge.src].push_back(make_pair(edge.dest, edge.weight));
            adjList[edge.dest].push_back(make_pair(edge.src, edge.weight));
        }
    }

    // Returns a label like "Station 0 (Central Station)"
    string label(int station) {
        return "Station " + to_string(station) + " (" + STATIONS[station] + ")";
    }

    // Print the transit network
    void printGraph() {
        cout << "City Rail Transit Network:" << endl;
        cout << "==========================" << endl;
        for (int station = 0; station < SIZE; station++) {
            cout << label(station) << " connects to:" << endl;
            for (Pair neighbor : adjList[station]) {
                cout << "  -> " << label(neighbor.first)
                     << " - Travel time: " << neighbor.second << " min" << endl;
            }
        }
        cout << endl;
    }

    // DFS using a stack: traces how a delay could spread down the lines
    void dfs(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> toVisit;
        toVisit.push(start);

        cout << "Delay Propagation Trace (DFS) from " << label(start) << ":" << endl;
        cout << "Purpose: Following how a service delay could ripple down each line" << endl;
        cout << "=================================================================" << endl;

        while (!toVisit.empty()) {
            int current = toVisit.top();
            toVisit.pop();
            if (visited[current]) {
                continue;
            }
            visited[current] = true;
            cout << "Delay reaches " << label(current) << endl;

            for (Pair neighbor : adjList[current]) {
                if (!visited[neighbor.first]) {
                    cout << "  -> Could spread to " << label(neighbor.first)
                         << " - Travel time: " << neighbor.second << " min" << endl;
                    toVisit.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    // BFS using a queue: groups stations by number of stops from the start
    void bfs(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> toVisit;
        visited[start] = true;
        toVisit.push(start);

        cout << "Stops-Away Coverage (BFS) from " << label(start) << ":" << endl;
        cout << "Purpose: Finding which stations are 1, 2, 3... stops away" << endl;
        cout << "==========================================================" << endl;

        while (!toVisit.empty()) {
            int current = toVisit.front();
            toVisit.pop();
            cout << "Checking " << label(current) << endl;

            for (Pair neighbor : adjList[current]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    cout << "  -> Next stop: " << label(neighbor.first)
                         << " - Travel time: " << neighbor.second << " min" << endl;
                    toVisit.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Track segments: {station A, station B, travel time in minutes}
    vector<Edge> edges = {
        {0, 1, 7},  {0, 2, 15}, {0, 3, 10}, {1, 4, 3},  {2, 4, 9},
        {2, 5, 11}, {3, 6, 4},  {4, 7, 13}, {5, 7, 6},  {5, 8, 2},
        {6, 8, 14}, {7, 9, 5},  {8, 10, 8}, {9, 10, 12}, {6, 10, 16}
    };

    Graph graph(edges);

    graph.printGraph();
    graph.dfs(0);
    graph.bfs(0);

    return 0;
}