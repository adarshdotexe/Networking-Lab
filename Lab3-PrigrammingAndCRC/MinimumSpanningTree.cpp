// Write a program to find minimum spanning tree of a graph.
// Path: Lab3-PrigrammingAndCRC\MinimumSpanningTree.cpp

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int source;
    int destination;
    int weight;
};

bool compare(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

int findParent(int v, int *parent) {
    if (parent[v] == v) {
        return v;
    }
    return findParent(parent[v], parent);
}

void kruskal(Edge *input, int n, int E) {
    // Sort the input array in ascending order based on weights
    sort(input, input + E, compare);

    // Create an output array
    Edge *output = new Edge[n - 1];

    // Create a parent array
    int *parent = new int[n];
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    // Iterate over the input array and take the current edge in consideration only if it does not form a cycle with the spanning tree formed so far
    int count = 0;
    int i = 0;
    while (count != n - 1) {
        Edge currentEdge = input[i];

        // Check if we can add the current edge in the MST or not
        int sourceParent = findParent(currentEdge.source, parent);
        int destinationParent = findParent(currentEdge.destination, parent);
        if (sourceParent != destinationParent) {
            output[count] = currentEdge;
            count++;
            parent[sourceParent] = destinationParent;
        }
        i++;
    }

    // Print MST
    for (int i = 0; i < n - 1; i++) {
        if (output[i].source < output[i].destination) {
            cout << output[i].source << " " << output[i].destination << " " << output[i].weight << endl;
        } else {
            cout << output[i].destination << " " << output[i].source << " " << output[i].weight << endl;
        }
    }
}

int main() {
    int n, E;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> E;

    Edge *input = new Edge[E];
    for (int i = 0; i < E; i++) {
        int s, d, w;
        cout << "Enter source, destination and weight of edge " << i << ": ";
        cin >> s >> d >> w;
        input[i].source = s;
        input[i].destination = d;
        input[i].weight = w;
    }

    kruskal(input, n, E);

    return 0;
}