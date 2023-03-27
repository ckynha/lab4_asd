#include <iostream>
#include<fstream>
#include<vector>

using namespace std;

class Vertex 
{
public:
	const int id;
	Vertex(int id) : id(id)
	{

	}
};

class Edge
{
public:
	const Vertex& from, & to;
	int w;
	Edge(Vertex& v1, Vertex& v2, int w) :
		from(v1), to(v2), w(w)
	{

	}
	Edge(Vertex& v1, Vertex& v2) :
		from(v1), to(v2), w(1)
	{

	}
};


class Graph
{
private:
	void WriteEnd();
	void AddCycle(int cycle_end, int cycle_st);
	void WriteEdge(int i, int j);
	void RunRecursive(int v, vector<bool>& visited);

	vector<Vertex> nodes;
	vector<vector<Edge*>> esFrom;
	vector<Edge*> edges;
	vector<int> prev;
	vector<vector<int>> cycle;

	int k;
	int start;

	wofstream f;

public:
	Graph(int n);

	void AddEdge(int from, int to);
	void WriteGraph(std::string fileName);
	void RunAlgorithm();

	~Graph();
};