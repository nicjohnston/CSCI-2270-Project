#include "Graph.h"
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <climits>
#include <limits.h>
#include <algorithm>


#define	LOAD_DATA_OVERWRITE		1
#define LOAD_DATA_APPEND		0

#define LENGTH_RATIO			1
#define LEFT_TURN_RATIO			1
#define RIGHT_TURN_RATIO		1

using namespace std;

Graph::Graph(const char fileName[]) { loadDataFromFile(fileName, 1); }

Graph::Graph() {}

Graph::~Graph() {}

int Graph::calculatePathWeight(int length, int rightTurns, int leftTurns) { return length*LENGTH_RATIO + rightTurns*RIGHT_TURN_RATIO + leftTurns*LEFT_TURN_RATIO; }


/*
Function prototype:
void Graph::addEdge(string v1, string v2, int length, int rightTurns, int leftTurns)

Function description:
This method adds an edge into the graph by creating an adjacent vertex between


Precondition: The rightTurns, leftTurns, and length variables muse be integers greater than or equal to 0. The variables v1 and v2 are the names of the two delivery locations that the link connects.
Post condition: An adjVertex is created with the specified length and turn count. One version of this adjVertex is created from the vertex whose name is v1, to the vertex whose name is v2.  Another link is created in the other direction as well.
*/
void Graph::addEdge(string v1, string v2, int length, int rightTurns, int leftTurns) {
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
					av.length = length;
					av.rightTurns = rightTurns;
					av.leftTurns = leftTurns;
					av.weight = calculatePathWeight(length, rightTurns, leftTurns);
                    vertices[i].adj.push_back(av);


					//another vertex for edge in other direction
					adjVertex av2;
					av2.v = &vertices[i];

					av2.length = length;
					av2.rightTurns = leftTurns;
					av2.leftTurns = rightTurns;
					av2.weight = calculatePathWeight(length, leftTurns, rightTurns);

					vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}

/*
Function prototype:
void Graph::addVertex(string n)

Function description:
This method adds a vertex to the vertices array that represents a delivery location.


Precondition: The string n is the name of the delivery location to be added.
Post condition: A new vertex is in the vertices vector the represents the delivery location that was added.
*/
void Graph::addVertex(string n) {
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        v.district = -1;
        v.visited = false;
        vertices.push_back(v);

    }
}

/*
Function prototype:
void Graph::printVertices()

Function description:
This method displays the connections between all the delivery locations.


Precondition: None.
Post condition: The connections between the delivery locations have been written to the command line.
*/
void Graph::printVertices(){
	//loop through all vertices and adjacent vertices
	for(int i = 0; i < vertices.size(); i++) {
		cout << vertices[i].district << ":" << vertices[i].name << "-->";
		for(int j = 0; j < vertices[i].adj.size(); j++) {
				cout<<vertices[i].adj[j].v->name;
				if (j != vertices[i].adj.size()-1)
					cout << "***";
		}
		cout<<endl;
	}
}

/*
Function prototype:
void Graph::findDistricts()

Function description:
This method assigns district id's to each delivery location.

Precondition: None.
Post condition: The district id's in the vertices vector have been updated to reflect the number of discrete graphs in the vector.
*/
void Graph::findDistricts() {
	int num_district = 1;

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].visited = false;
	}

	int i = 0;
	queue<vertex *> Q;

	for (int i = 0; i < vertices.size(); i++) {
		//num_district++;
		bool new_district = false;

		Q.push(&vertices[i]);

		while (!Q.empty()) {
			vertex * u = Q.front();
			Q.pop();
			for (int k = 0; k < u->adj.size(); k++) {
				if (u->adj[k].v->visited == false) {
					u->adj[k].v->visited = true;
					u->adj[k].v->district = num_district;
					Q.push(u->adj[k].v);
					new_district = true;
				}
			}
		}

		if (new_district) {
			num_district++;
			new_district = false;
		}

	}
}

/*
Function prototype:
vertex* Graph::BF_Search(string city, string startingCity)

Function description:
This method searches the graph for a delivery location with a specified name starting a a specified node.


Precondition: The city variable must be a string with the name of the delivery location to search for. The startingSicy variable must be a string with the name of the delivery location to start the breadth-first traversal from.
Post condition: A pointer to the vertex that was found is returned. If a delivery location with the specified name is not found, a null pointer is returned.
*/
vertex* Graph::BF_Search(string city, string startingCity) {

	vertex *searchResult = nullptr;
	bool foundCity = false;

	int i = 0;
	queue<vertex *> Q;
	for(i = 0; i < vertices.size(); i++){
		vertices[i].visited = false;
		if (vertices[i].name == startingCity) {
			vertices[i].visited = true;
			Q.push(&vertices[i]);
			//cout << vertices[i].name << endl;
			//break;
		}
		if (vertices[i].name == city) {
			searchResult = &vertices[i];
			foundCity = true;
		}
	}

	while (!Q.empty() && foundCity == false) {
		vertex * u = Q.front();
		Q.pop();

		for (int k = 0; k < u->adj.size(); k++) {
			if (u->adj[k].v->visited == false) {
				u->adj[k].v->visited = true;
				//cout << u->adj[k].v->name << endl;
				if (u->adj[k].v->name == city) {
					searchResult = u->adj[k].v;
					foundCity = true;
					cout << u->adj[k].v->name << endl;
				}
				Q.push(u->adj[k].v);
			}
		}
	}
	cout << "foundCity: " << foundCity << endl;
	return searchResult;
}

/*
Function prototype:
vertex* Graph::BF_Search(string city)

Function description:
This method is an overload of the BF_Search function that allows the user to call it without specifying a starting location.


Precondition: The city variable must be a string with the name of the delivery location to search for.
Post condition: A pointer to the vertex that was found is returned. If a delivery location with the specified name is not found, a null pointer is returned.
*/
vertex* Graph::BF_Search(string city) {
	string start = vertices[0].name;
	return this->BF_Search(city, start);
}

/*
Function prototype:
void Graph::BF_Traversal(string startingCity)

Function description:
This method traverses the delivery location graph from a starting location.  This method uses the breadth-first traversal algorithm.


Precondition: The startingCity variable must be a string with the name of the delivery location to start from.
Post condition: None
*/
void Graph::BF_Traversal(string startingCity) {
	int i = 0;
	queue<vertex *> Q;
	for(i = 0; i < vertices.size(); i++){
		vertices[i].visited = false;
		if (vertices[i].name == startingCity) {
			vertices[i].visited = true;
			Q.push(&vertices[i]);
			cout << "1st Loop: " << vertices[i].name << endl;
			break;
		}
	}
	while (!Q.empty()) {
		vertex * u = Q.front();
		Q.pop();
		for (int k = 0; k < u->adj.size(); k++) {
			if (u->adj[k].v->visited == false) {
				u->adj[k].v->visited = true;
				cout << "2nd Loop: " << u->adj[k].v->name << endl;
				Q.push(u->adj[k].v);
			}
		}
	}
}

vertex * Graph::findVertex(string name)
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == name)
            return &vertices[i];
    }
    return NULL;
}

/*
Function prototype:
void Graph::loadDataFromFile(const char fileName[], int mode)

Function description:
This method loads a set of deliveries from a file into the delivery locations graph.


Precondition: The fileName variable must contain the name of the file from which to read the data. The mode variable is an integer whose values must be either 0 or 1.  mode = 0 appends the new data into the graph, mode = 1 overwrites the existing data with new data.
Post condition: The vertices graph contains new delivery locations and connections between those locations.
*/
void Graph::loadDataFromFile(const char fileName[], int mode) {

	if (mode == 1) {
        clearGraph();
	}

	fileData.open(fileName);
	string line;
	getline(fileData, line);
	vector <string> Cities;
	parseLine(line, Cities);
	for (int i = 1; i < Cities.size(); i++) {
		//cout << Cities[i] << ",";
		addVertex(Cities[i]);
	}

	int startingColumn = 0;
	vector <string> data;

	while (getline(fileData, line)) {
		parseLine(line, data);
		//cout << endl << data[0] << ":	";
		for (int i = startingColumn+1; i < Cities.size(); i++) {

			vector <string> data2;

			parseLine(data[i], data2, ',');

			int length = atoi(data2[0].c_str());
			int rightTurns = atoi(data2[1].c_str());
			int leftTurns = atoi(data2[2].c_str());

			if (length > 0) addEdge(data[0], Cities[i], length, rightTurns, leftTurns);
			//cout << edgeVal << "	  ";
		}
		data.clear();
		startingColumn++;
	}
}

// The clearGraph function is supposed to completly clear the graph.
// It is currently not functioning properly.  It clears the graph, however inserting new data fails after clearing the graph.
void Graph::clearGraph() {
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].adj.clear();
	}
	vertices.clear();
}

/*
Function prototype:
void Graph::shortestDeliveryRoute(string startingCity)

Function description:
This method determines the shortest delivery route and writes it to a vertex of strings.


Precondition: The startingCity variable must be a string specifying where to start the deliveries from. It defaults to the node called STARTING
Post condition: The currentRoute vertex contains the most efficient route to deliver the packages.
*/
// This is addapted from the assignment 8 solution.
void Graph::shortestDeliveryRoute(string startingCity)
{
    vertex * start = findVertex(startingCity);

    if (start == NULL)
    {
        cout << "City doesn't exist." << endl;
        return;
    }
    if (start->district == -1)
    {
        cout << "Identifying the districts." << endl;
        findDistricts();
        //return;
    }

    // Initialization
    queueVertex qv;
    qv.distance = 0;
    qv.path.push_back(start);
    queue<queueVertex> q;
    q.push(qv);

    // Contains all of the possible path solutions we run into.
    std::priority_queue<queueVertex> possibleSolutions;

    while (q.empty() != true)
    {
        qv = q.front();
        q.pop();

        // If we have covered all nodes, we need to add the connection back to the first node if it exists.
        if (qv.path.size() == vertices.size())
        {
            for(int i = 0; i < qv.path.back()->adj.size(); i++)
            {
                // If we find a link to the first node.
                if (qv.path.back()->adj[i].v == start)
                {
                    // Add it to path
                    qv.distance += qv.path.back()->adj[i].weight;
                    qv.path.push_back(qv.path.back()->adj[i].v);
                    // Add this as a possible solution.
                    possibleSolutions.push(qv);
                }
            }
        }

        else
        {
            // For each adjacent city
            for(int i = 0; i < qv.path.back()->adj.size(); i++)
            {

                // Create a new path that contains this node, if node doesn't already exist in path.
                if (find(qv.path.begin(), qv.path.end(),qv.path.back()->adj[i].v) == qv.path.end())
                {
                    vector<vertex *> path = qv.path;
                    int distance = qv.distance + qv.path.back()->adj[i].weight;
                    path.push_back(qv.path.back()->adj[i].v);
                    queueVertex temp;
                    temp.path = path;
                    temp.distance = distance;
                    for (int i = 0; i < temp.path.size(); i++)
						cout << temp.path[i]->name << "<-->";
					cout << endl;
                    q.push(temp);
                }

            }


        }
    }

    cout << endl << endl;
    if (!possibleSolutions.empty())
    {
        queueVertex solution = possibleSolutions.top();
        cout << solution.distance << endl;
        cout << solution.distance;
        for (int j = 0; j < solution.path.size(); j++) {
            cout << "," << solution.path[j]->name;
            // The following code was an attempt at using a vector of the routePath struct to store the length and number of turns for each delivery.
//            routePath temp;
//            temp.starting = solution.path[j]->name;
//            temp.ending = solution.path[j+1]->name;
//            pathLength(temp.starting, temp.ending, temp.length, temp.rightTurns, temp.leftTurns);
//            cout << temp.starting << ":" << temp.ending << ":" << temp.length << ":" << temp.rightTurns << ":" << temp.leftTurns << endl;
//            currentRoute.push(temp);
            currentRoute.push_back(solution.path[j]->name);
		}
        cout << endl;
		numDeliveries = currentRoute.size()-2;
    }
    else
        cout << "No possible path." << endl;
    return;
}

// This function is adapted from my solution to recitation 11 part 5.
// Although it is presently unused, it was originally intended to provide extra information about the path between each delivery.
void Graph::pathLength(string vertex1, string vertex2, int &length, int &leftTurns, int &rightTurns) {

    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].visited = false;
    }


    queue<vertex*> bfq;
    vertex v;
    int i = 0;
    for(i=0; i<vertices.size();i++) {
        if (vertex1 == vertices[i].name) {
            v = vertices[i];
            break;
        }
    }
    //cout<<v.name<<endl;
    vertices[i].visited = true;
    bfq.push(&vertices[i]);


    while (!bfq.empty()) {
        v = *bfq.front();
        bfq.pop();
        for(i=0;i<v.adj.size();i++) {
            if (v.adj[i].v->visited==false) {
                v.adj[i].v->visited = true;
                bfq.push(v.adj[i].v);
                //cout<<v.adj[i].v->name<<endl;
                if (vertex2 == v.adj[i].v->name) {
                    //cout << vertex2 << ":" << v.adj[i].v->name << endl;
                    length = v.adj[i].length;
                    rightTurns = v.adj[i].rightTurns;
                    leftTurns = v.adj[i].leftTurns;
                }
            }
        }
    }
}

void Graph::printCurrentRoute() {
	if (numDeliveries != 0) {
		for (int i = 0; i < currentRoute.size()-1; i++) {
			if (i != 0) cout << "-->";
			cout << currentRoute[i];
		}
		cout << endl;
	} else {
		cout << "There are no deliveries." << endl;
	}
}

void Graph::deliverPackage() {
	if (numCompleteDeliveries < numDeliveries && numDeliveries != 0) {
		cout << "Delivered a package to " << currentRoute[numCompleteDeliveries+1] << endl;
		numCompleteDeliveries++;
		cout << numCompleteDeliveries << ":" << numDeliveries << endl;
	} else {
		cout << "All packages have been delivered." << endl;
		currentRoute.clear();
		numCompleteDeliveries = 0;
		numDeliveries = 0;
	}
}

void Graph::printCurrentProgress() {
	if (numDeliveries != 0) {
		float percent = ((float)numCompleteDeliveries/(float)numDeliveries)*100.0;
		cout << numCompleteDeliveries << " out of " << numDeliveries << " delivered. ";
		cout << percent;
		cout << "% complete." << endl;
	} else {
		cout << "There are no deliveries." << endl;
	}
}

void Graph::parseLine(string line, vector <string> &words, char delimiter) {
	stringstream buffer(line);
	string word;
	while (getline(buffer, word, delimiter)) {
		//cout << "====" << word << "====" << endl;
		words.push_back(word);
	}
}
