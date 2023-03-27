#include "Graph.h"

int main() 
{
	Graph g(4);
	g.AddEdge(0, 1);
	g.AddEdge(0, 2);
	g.AddEdge(1, 2);
	g.AddEdge(1, 3);
	g.AddEdge(2, 3);

	g.WriteGraph("../../../vis/commands.js");
	g.RunAlgorithm();

	return 0;
}