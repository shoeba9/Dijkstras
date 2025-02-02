#include <iostream>
#include <vector>
#include <limits.h>  

using namespace std;

#define INF INT_MAX     // Represents no direct connection

// Function to find the nearest unvisited node
int getNearestNode(vector<int>& minDistance, vector<bool>& visitedNodes, int totalNodes) {
    int nearestNode = -1, smallestDist = INF;

    for (int i = 0; i < totalNodes; i++) 
{
        if (!visitedNodes[i] && minDistance[i] < smallestDist) 
{
            smallestDist = minDistance[i];
            nearestNode = i;
        }
    }
    return nearestNode;
}

// Function to find the shortest path using Dijkstra's Algorithm
void findShortestRoute(vector<vector<int>>& graph, int startNode, int endNode, int totalNodes) 
{
    vector<int> minDistance(totalNodes, INF);  // Stores shortest distance from startNode
    vector<int> previousNode(totalNodes, -1);  // Stores previous node for path tracking
    vector<bool> visitedNodes(totalNodes, false); // Tracks visited nodes

    minDistance[startNode] = 0;  // Start node has distance 0

    for (int i = 0; i < totalNodes - 1; i++) 
{
        int currentNode = getNearestNode(minDistance, visitedNodes, totalNodes);
        if (currentNode == -1) break;  // Stop if no reachable node is found

        visitedNodes[currentNode] = true;  // Mark as visited

        // Update distances for neighbors
        for (int neighbor = 0; neighbor < totalNodes; neighbor++) 
{
            if (!visitedNodes[neighbor] && graph[currentNode][neighbor] > 0)
 { 
                int newDist = minDistance[currentNode] + graph[currentNode][neighbor];

                if (newDist < minDistance[neighbor])
 { 
                    minDistance[neighbor] = newDist;
                    previousNode[neighbor] = currentNode;
                }
            }
        }
    }
    // Output the shortest path and cost
    if (minDistance[endNode] == INF) 
{
        cout << "No path exists between node " << startNode << " and node " << endNode << "." << endl;
    } else 
{
        cout << "Shortest route cost: " << minDistance[endNode] << endl;
        cout << "Route: ";

        vector<int> path;
        for (int node = endNode; node != -1; node = previousNode[node]) 
{
            path.insert(path.begin(), node);
        }

        for (size_t i = 0; i < path.size(); i++) 
{
            cout << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
}

int main() 
{
    int totalNodes;
    cout << "Enter total number of nodes: ";
    cin >> totalNodes;

    vector<vector<int>> graph(totalNodes, vector<int>(totalNodes, 0));

    cout << "Enter the adjacency matrix (0 for no connection):\n";
    for (int i = 0; i < totalNodes; i++) {
        for (int j = 0; j < totalNodes; j++) {
            cin >> graph[i][j];
        }
    }

    int startNode, endNode;
    cout << "Enter starting node (0 to " << totalNodes - 1 << "): ";
    cin >> startNode;
    cout << "Enter ending node (0 to " << totalNodes - 1 << "): ";
    cin >> endNode;

    findShortestRoute(graph, startNode, endNode, totalNodes);

    return 0;
}
