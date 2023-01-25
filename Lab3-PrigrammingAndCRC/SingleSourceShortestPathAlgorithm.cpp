// Write a program to implement single source shortest path algorithm.

// Path: Lab3-PrigrammingAndCRC\SingleSourceShortestPathAlgorithm.cpp

#include <iostream>
#include <climits>

using namespace std;

void dijkstra(int **edges, int n) {
    // Create a distance array and initialize all distances as infinite (INF)
    int *distance = new int[n];
    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
    }

    // Mark all the vertices as not visited
    bool *visited = new bool[n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    // Distance of source vertex from itself is always 0
    distance[0] = 0;

    // Find shortest path for all vertices
    for (int i = 0; i < n - 1; i++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in first iteration.
        int minVertex = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (minVertex == -1 || distance[j] < distance[minVertex])) {
                minVertex = j;
            }
        }

        // Mark the picked vertex as processed
        visited[minVertex] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int j = 0; j < n; j++) {
            if (edges[minVertex][j] != 0 && !visited[j]) {
                int dist = distance[minVertex] + edges[minVertex][j];
                if (dist < distance[j]) {
                    distance[j] = dist;
                }
            }
        }
    }

    // Print the constructed distance array
    for (int i = 0; i < n; i++) {
        cout << i << " " << distance[i] << endl;
    }
}

int main() {
    int n, e;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;

    int **edges = new int *[n];
    for (int i = 0; i < n; i++) {
        edges[i] = new int[n];
        for (int j = 0; j < n; j++) {
            edges[i][j] = 0;
        }
    }

    for (int i = 0; i < e; i++) {
        int f, s, weight;
        cout << "Enter first vertex, second vertex and weight of edge " << i << ": ";
        cin >> f >> s >> weight;
        edges[f][s] = weight;
        edges[s][f] = weight;
    }

    dijkstra(edges, n);

    for (int i = 0; i < n; i++) {
        delete[] edges[i];
    }
    delete[] edges;
}