#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

const int SIZE = 11;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i]) {
                cout << "(" << v.first << ", " << v.second << ") ";
            }
            cout << endl;
        }
    }

    // DFS using a stack
    void dfs(int s) {
        vector<bool> vis(SIZE, false);
        stack<int> st;
        st.push(s);
        cout << "DFS starting from vertex " << s << ":" << endl;
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            if (vis[u]) {
                continue;
            }
            vis[u] = true;
            cout << u << " ";
            for (Pair v : adjList[u]) {
                if (!vis[v.first]) {
                    st.push(v.first);
                }
            }
        }
        cout << endl;
    }

    // BFS using a queue
    void bfs(int s) {
        vector<bool> vis(SIZE, false);
        queue<int> q;
        vis[s] = true;
        q.push(s);
        cout << "BFS starting from vertex " << s << ":" << endl;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";
            for (Pair v : adjList[u]) {
                if (!vis[v.first]) {
                    vis[v.first] = true;
                    q.push(v.first);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,7},{0,2,15},{0,3,10},{1,4,3},{2,4,9},{2,5,11},{3,6,4},{4,7,13},
        {5,7,6},{5,8,2},{6,8,14},{7,9,5},{8,10,8},{9,10,12},{6,10,16}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    // Runs DFS and BFS from vertex 0
    graph.dfs(0);
    graph.bfs(0);

    return 0;
}