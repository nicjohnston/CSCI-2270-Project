#ifndef GRAPH_H
#define GRAPH_H


#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <climits>
#include <limits.h>
#include <algorithm>

#define DEFAULT_PARSE_LINE_DELIMITER	';'

using namespace std;

struct vertex;

struct adjVertex{
	vertex *v;
	int weight;

	int length;
	int rightTurns;
	int leftTurns;
};

// The vertex struct holds the information about every delivery location.
struct vertex {
	string name;
	bool visited;
	int distance;
	vertex *previous;

	int district = -1; // This variable will most likely be unused because all the deliveries are connected to the starting node.

	vector <adjVertex> adj;
};

struct routePath {
	string starting;
	string ending;
	int length;
	int leftTurns;
	int rightTurns;
};

struct queueVertex{
    int distance;
    std::vector <vertex *> path;
    // Must override the less operatator so that we get a min value from priority queue.
    bool operator<(const queueVertex& a) const
    {
        return distance > a.distance;
    }
};

// Must override operator so we get a min value from priority queue.
struct Comparator {
public:
    bool operator()(const vertex* a, const vertex* b)
    {
        return (a->distance > b->distance);
    }
};

class Graph {
	public:
		Graph(const char []);
		Graph();
		~Graph();
		void addEdge(string v1, string v2, int length, int rightTurns, int leftTurns);
		void addVertex(string name);
		void displayEdges();

		void printVertices();
		void findDistricts();
		void find_Shortest_Distance(string, string);
		void find_Shortest_Path(string, string);

		vertex* BF_Search(string, string);
		vertex* BF_Search(string);
		vertex* findVertex(string name);
		void BF_Traversal(string);
		void parseLine(string, vector <string> &, char delimiter = DEFAULT_PARSE_LINE_DELIMITER);

		void loadDataFromFile(const char [], int);

		void clearGraph();

		void shortestDeliveryRoute(string startingCity);

	protected:
	private:

		int calculatePathWeight(int, int, int);

		//vector<edge> edges;
		vector <vertex> vertices;
		ifstream fileData;

		queue <routePath> currentRoute;
};

#endif // GRAPH_H
