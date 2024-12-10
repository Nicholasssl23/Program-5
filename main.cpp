#include <iostream>
#include "WeightedGraph.h"

using namespace std;

int main() {
    using namespace std;
        // Create the graph
        WeightedGraph graph(5);

        // Add vertices
        Vertex* vA = new Vertex("A"); // Use string literals "A" instead of 'A'
        Vertex* vB = new Vertex("B");
        Vertex* vC = new Vertex("C");
        Vertex* vD = new Vertex("D");
        Vertex* vE = new Vertex("E");

    graph.addVertex(vA);
    graph.addVertex(vB);
    graph.addVertex(vC);
    graph.addVertex(vD);
    graph.addVertex(vE);

    // Add edges
    graph.addEdge(0, 1, 10); // A to B, weight 10
    graph.addEdge(0, 2, 12); // A to C, weight 12
    graph.addEdge(0, 3, 60); // A to D, weight 60
    graph.addEdge(1, 2, 20); // B to C, weight 20
    graph.addEdge(2, 3, 32); // C to D, weight 32
    graph.addEdge(4, 0, 7);  // E to A, weight 7

    // Perform DFS and BFS from node E
    cout << "DFS Traversal from E: ";
    graph.DFS(vE);
    cout << endl;

    cout << "BFS Traversal from E: ";
    graph.BFS(vE);
    cout << endl;

    // Test the pathExists function
    cout << "Path from A to D: ";
    graph.pathExists(vA, vD);
    cout << endl;

    cout << "Path from E to B: ";
    graph.pathExists(vE, vB);
    cout << endl;

    return 0;
}