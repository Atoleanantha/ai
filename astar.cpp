#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Node {
    Node* parent;
    pair<int, int> position;

    int g; // Cost from start to node
    int h; // Heuristic cost from node to end
    int f; // Total cost

    Node(Node* p, pair<int, int> pos) : parent(p), position(pos), g(0), h(0), f(0) {}

    bool operator == (const Node& other) const {
        return position == other.position;
    }
};

class AStar {
public:
    // Function to perform A* search
    static vector<pair<int, int>> search(vector<vector<int>>& maze, pair<int, int> start, pair<int, int> end) {
        Node* startNode = new Node(nullptr, start);
        Node* endNode = new Node(nullptr, end);

        vector<Node*> openList;
        vector<Node*> closedList;

        openList.push_back(startNode);

        while (!openList.empty()) {
            Node* currentNode = openList.front();
            int currentIndex = 0;

            // Find the node with the lowest f score
            for (int i = 0; i < openList.size(); i++) {
                if (openList[i]->f < currentNode->f) {
                    currentNode = openList[i];
                    currentIndex = i;
                }
            }

            // Remove the current node from the open list and add to closed list
            openList.erase(openList.begin() + currentIndex);
            closedList.push_back(currentNode);

            // If the goal is reached, reconstruct the path
            if (*currentNode == *endNode) {
                vector<pair<int, int>> path;
                while (currentNode != nullptr) {
                    path.push_back(currentNode->position);
                    currentNode = currentNode->parent;
                }
                reverse(path.begin(), path.end());
                cleanUp(openList);
                cleanUp(closedList);
                return path;
            }

            // Generate children nodes in all eight possible directions
            for (const pair<int, int>& move : vector<pair<int, int>>{{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}}) {
                pair<int, int> nodePos = {currentNode->position.first + move.first, currentNode->position.second + move.second};

                // Check boundaries
                if (nodePos.first >= maze.size() || nodePos.first < 0 || nodePos.second >= maze[0].size() || nodePos.second < 0)
                    continue;

                // Check if the node is walkable
                if (maze[nodePos.first][nodePos.second] != 0)
                    continue;

                Node* newNode = new Node(currentNode, nodePos);

                // Check if new node is in the closed list
                if (find_if(closedList.begin(), closedList.end(), [&newNode](const Node* other) {
                    return *newNode == *other;
                }) != closedList.end()) {
                    continue;
                }

                // Calculate g, h, and f
                newNode->g = currentNode->g + 1;
                newNode->h = (abs(newNode->position.first - endNode->position.first) + abs(newNode->position.second - endNode->position.second)) * 2;
                newNode->f = newNode->g + newNode->h;

                // Check if new node is in the open list with a lower g value
                if (find_if(openList.begin(), openList.end(), [&newNode](const Node* other) {
                    return *newNode == *other && newNode->g > other->g;
                }) != openList.end()) {
                    continue;
                }

                openList.push_back(newNode);
            }
        }

        // Clean up memory if no path is found
        cleanUp(openList);
        cleanUp(closedList);
        return vector<pair<int, int>>(); // return empty path if no path is found
    }

private:
    // Helper function to clean up memory
    static void cleanUp(vector<Node*>& list) {
        for (Node* node : list) {
            delete node;
        }
        list.clear();
    }
};

int main() {
    vector<vector<int>> maze {
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    pair<int, int> start = {9, 0};
    pair<int, int> end = {0,5};

    vector<pair<int, int>> path = AStar::search(maze, start, end);

    for (auto& p : path) {
        cout << "(" << p.first << ", " << p.second << ") ";
    }

    return 0;
}

