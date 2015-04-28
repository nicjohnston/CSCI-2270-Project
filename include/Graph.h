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
	bool visited = false;
	int distance;
	//vertex *previous;
	//int ID;
	int district;

	vector <adjVertex> adj;
};

// This is not used
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

		void pathLength(string, string, int&, int&, int&);

		void printCurrentRoute();
		void printCurrentProgress();
		void deliverPackage();

	protected:
	private:

		int calculatePathWeight(int, int, int);

		//vector<edge> edges;
		vector <vertex> vertices;
		ifstream fileData;

		//queue <routePath> currentRoute;
		vector <string> currentRoute;

		int numDeliveries = 0;
		int numCompleteDeliveries = 0;

};

#endif // GRAPH_H
