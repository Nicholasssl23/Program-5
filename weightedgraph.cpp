// WeightedGraph.cpp
#include "WeightedGraph.h"
#include <iostream>
#include <queue>
#include <stack>
#include <functional> // Add this line to include the <functional> header

WeightedGraph::WeightedGraph(int size) {
    m_numVertices = 0;
    m_maxVertices = size;
    m_vertices.resize(size);
    for (int i = 0; i < size; i++) {
        m_vertices[i] = NULL;
    }

    m_marks.resize(size);
    int rows = size;
    int columns = size;
    m_edges.resize(rows, std::vector<int>(columns, 0));
}

void WeightedGraph::addVertex(Vertex* aVertex) {
    m_vertices[m_numVertices] = aVertex;
    for (int i = 0; i < m_maxVertices; i++) {
        m_edges[m_numVertices][i] = NULL_EDGE;
        m_edges[i][m_numVertices] = NULL_EDGE;
    }
    m_numVertices++;
}

void WeightedGraph::addEdge(int fromVertex, int toVertex, int weight) {
    int row;
    int column;
    row = indexIs(m_vertices[fromVertex]);
    column = indexIs(m_vertices[toVertex]);
    m_edges[row][column] = weight;
}

int WeightedGraph::indexIs(Vertex* aVertex) {
    int i = 0;
    while (i < m_numVertices) {
        if (m_vertices[i] == aVertex) {
            return i;
        }
        i++;
    }
    return -1;
}

void WeightedGraph::clearMarks() {
    for (int i = 0; i < m_numVertices; i++) {
        m_marks[i] = false;
    }
}

void WeightedGraph::doDFS(Vertex* aVertex) {
    int ix, ix2;
    if (aVertex == NULL) return;
    std::cout << aVertex->getTitle() << " ";
    ix = indexIs(aVertex);
    m_marks[ix] = true;
    for (int i = 0; i < m_numVertices; i++) {
        ix2 = indexIs(m_vertices[i]);
        if (m_edges[ix][ix2] != NULL_EDGE) {
            if (m_marks[i] == false)
                doDFS(m_vertices[i]);
        }
    }
}

void WeightedGraph::DFS(Vertex* aVertex) {
    clearMarks();
    doDFS(aVertex);
}

void WeightedGraph::doBFS(Vertex* aVertex) {
    int ix, ix2;
    std::queue<Vertex*> que;
    ix = indexIs(aVertex);
    m_marks[ix] = true;
    que.push(aVertex);
    while (!que.empty()) {
        Vertex* node = que.front();
        que.pop();
        ix = indexIs(node);
        std::cout << node->getTitle() << " ";
        for (int i = 0; i < m_numVertices; i++) {
            ix2 = indexIs(m_vertices[i]);
            if (m_edges[ix][ix2] != NULL_EDGE) {
                if (m_marks[ix2] == false) {
                    m_marks[i] = true;
                    que.push(m_vertices[i]);
                }
            }
        }
    }
}

void WeightedGraph::BFS(Vertex* aVertex) {
    clearMarks();
    doBFS(aVertex);
}

// Function to check if a path exists between two nodes
void WeightedGraph::pathExists(Vertex* source, Vertex* destination) {
    if (source == NULL || destination == NULL) {
        std::cout << "Invalid source or destination vertex." << std::endl;
        return;
    }

    clearMarks();
    std::stack<Vertex*> pathStack; // Use a stack to store the path
    int totalCost = 0;

    // Recursive helper function to find the path
    std::function<bool(Vertex*)> findPath = [&](Vertex* current) {
        pathStack.push(current);
        int currentIndex = indexIs(current);
        m_marks[currentIndex] = true;

        if (current == destination) {
            return true; // Path found
        }

        for (int i = 0; i < m_numVertices; i++) {
            if (m_edges[currentIndex][i] != NULL_EDGE && !m_marks[i]) {
                if (findPath(m_vertices[i])) {
                    return true; // Path found through recursion
                }
            }
        }

        pathStack.pop(); // Pop the vertex if it doesn't lead to the destination
        return false; // No path found from this vertex
    };

    if (findPath(source)) {
        // Path found, print the path and calculate the total cost
        std::stack<Vertex*> outputStack; // Use another stack to reverse the order
        while (!pathStack.empty()) {
            outputStack.push(pathStack.top());
            pathStack.pop();
        }

        Vertex* prevVertex = nullptr;
        while (!outputStack.empty()) {
            Vertex* currentVertex = outputStack.top();
            outputStack.pop();
            std::cout << currentVertex->getTitle() << " ";

            if (prevVertex != nullptr) {
                int prevIndex = indexIs(prevVertex);
                int currentIndex = indexIs(currentVertex);
                totalCost += m_edges[prevIndex][currentIndex];
            }

            prevVertex = currentVertex;
        }

        std::cout << " (Cost: " << totalCost << ")" << std::endl;
    }
    else {
        std::cout << "No path found from " << source->getTitle() << " to " << destination->getTitle() << std::endl;
    }
}