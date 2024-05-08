#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Class to represent an edge in the graph
class Edge {
public:
    int from, to, weight;

    Edge(int from, int to, int weight) {
        this->from = from;
        this->to = to;
        this->weight = weight;
    }

    // Overloading < operator for sorting edges based on weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Class to implement Union-Find data structure
class UnionFind {
public:
    vector<int> parent;
    vector<int> rank;

    // Constructor to initialize parent and rank arrays
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i; // Initially, each vertex is its own parent
            rank[i] = 0;   // Initially, each vertex has rank 0
        }
    }

    // Find operation with path compression
    int find(int v) {
        if (parent[v] != v) {
            parent[v] = find(parent[v]);
        }
        return parent[v];
    }

    // Union operation with union by rank
    void unionSet(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

// Function to find Minimum Spanning Tree using Kruskal's Algorithm
vector<Edge> kruskal(vector<Edge>& edges, int n) {
    sort(edges.begin(), edges.end()); // Sort edges based on weight
    UnionFind uf(n); // Create UnionFind instance
    vector<Edge> minSpanningTree; // Vector to store edges of MST

    // Traverse sorted edges and add to MST if not forming cycle
    for (const Edge& edge : edges) {
        if (uf.find(edge.from) != uf.find(edge.to)) {
            minSpanningTree.push_back(edge);
            uf.unionSet(edge.from, edge.to);
        }
    }

    return minSpanningTree;
}

int main() {
    // Sample graph edges
    vector<Edge> edges;
    edges.push_back(Edge(0, 1, 2));
    edges.push_back(Edge(0, 2, 3));
    edges.push_back(Edge(1, 2, 4));
    edges.push_back(Edge(1, 3, 5));
    edges.push_back(Edge(2, 3, 1));

    int n = 4; // Number of vertices

    // Find Minimum Spanning Tree
    vector<Edge> minSpanningTree = kruskal(edges, n);

    // Print Minimum Spanning Tree
    cout << "Minimum Spanning Tree (Kruskal's Algorithm):" << endl;
    for (const Edge& edge : minSpanningTree) {
        cout << edge.from << " - " << edge.to << ": " << edge.weight << endl;
    }

    return 0;
}
