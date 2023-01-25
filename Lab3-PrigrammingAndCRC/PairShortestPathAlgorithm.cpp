// Write a program to implement all pair shortest path algorithm.
// Path: Lab3-PrigrammingAndCRC\PairShortestPathAlgorithm.cpp

#include <iostream>
#include <climits>

using namespace std;

void floydWarshall(int **edges, int n) {
    // Create a distance matrix and initialize all distances as infinite (INF)
    int **distance = new int *[n];
    for (int i = 0; i < n; i++) {
        distance[i] = new int[n];
        for (int j = 0; j < n; j++) {
            distance[i][j] = INT_MAX;
        }
    }

    // Initialize the distance matrix as same as the input graph matrix. Or we can say the initial values of shortest distances are based on shortest paths considering no intermediate vertex.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            distance[i][j] = edges[i][j];
        }
    }

    // Add all vertices one by one to the set of intermediate vertices.
    // ---> Before start of a iteration, we have shortest distances between all pairs of vertices such that the shortest distances consider only the vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
    // ----> After the end of a iteration, vertex no. k is added to the set of intermediate vertices and the set becomes {0, 1, 2, .. k}
    for (int k = 0; k < n; k++) {
        // Pick all vertices as source one by one
        for (int i = 0; i < n; i++) {
            // Pick all vertices as destination for the above picked source
            for (int j = 0; j < n; j++) {
                // If vertex k is on the shortest path from i to j, then update the value of distance[i][j]
                if (distance[i][k] != INT_MAX && distance[k][j] != INT_MAX && distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    // Print the shortest distance matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (distance[i][j] == INT_MAX) {
                cout << "INF ";
            }
            else {
                cout << distance[i][j] << " ";
            }
        }
        cout << endl;
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
        cout << "Enter first vertex, second vertex and weight: ";
        cin >> f >> s >> weight;
        edges[f][s] = weight;
        edges[s][f] = weight;
    }

    floydWarshall(edges, n);

    for (int i = 0; i < n; i++) {
        delete[] edges[i];
    }
    delete[] edges;

    return 0;
}