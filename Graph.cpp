#include "Graph.h"

Graph::Graph(int n)
{
	for (size_t i = 0; i < n; i++)
	{
		nodes.push_back(Vertex(i)); // создаем n узлов
	}
	esFrom.resize(n);
	prev.resize(n); // для хранения информации о том, из какой вершины была посещена текущая вершина.
	k = 0; // используем для нумерации вершин
	start = 0; // храним начальную вершину для поиска циклов
}

void Graph::AddEdge(int from, int to) 
{
	if (from == to) return;
	Edge* e = new Edge(nodes[from], nodes[to]);
	edges.push_back(e);
	esFrom[from].push_back(e);
	esFrom[to].push_back(e);
}


void Graph::WriteGraph(string fileName) 
{
	f = wofstream(fileName);
	f << "window.prog=`\n";
	for (auto& n : nodes) 
	{
		f << n.id << endl;
	}
	for (auto e : edges)
	{
		WriteEdge(e->from.id, e->to.id); f << endl;
	}

	f << "draw\n";
}

void Graph::WriteEnd()
{
	f << "`\n";
	f.close();
}

void Graph::WriteEdge(int i, int j)
{
	if (i <= j) f << i << "-" << j;
	else f << j << "-" << i;
}

void Graph::AddCycle(int cycle_end, int cycle_st)
{
	WriteEdge(cycle_end, start); f << ",color=green\n"; // записываем ребро между концом и началом цикла

	vector<int> temp; // вектор для добавления вершин, образующих цикл

	temp.push_back(cycle_st);

	// заносим вершины в вектор temp
	for (int v = cycle_end; v != cycle_st; v = prev[v]) 
	{
		temp.push_back(v);
	}

	temp.push_back(cycle_st);

	if (temp.size() > 3) // проверка на нормальный цикл
	{
		reverse(temp.begin(), temp.end()); 
		cycle.push_back(temp);

		for (int i = 0; i < temp.size() - 1; ++i) 
		{
			f << temp[i] << ",color=red,label=" << temp[i] << "\n";
		}
		f << "pause" << "\n";

		for (int i = 0; i < temp.size() - 1; ++i) 
		{
			f << temp[i] << ",color=green,label=" << temp[i] << "\n";
		}
		WriteEdge(cycle_end, start); f << ",color=blue\n";

	}
}


void Graph::RunAlgorithm() // запускаем обход графа в глубину
{
	auto visited = vector<bool>(nodes.size(), false); // содержит информацию о том, была ли посещена вершина
	for (int i = 0; i < nodes.size(); ++i) // итерируемся по всем вершинам графа
	{
		visited[i] = true; // помечаем текущую вершину как посещенную
		start = i;
		k = 1;
		RunRecursive(i, visited);
		visited[i] = true; // возвращаем вершину в исходное состояние для следующей итерации цикла
	}

	// выводим найденные циклы
	for (int i = 0; i < cycle.size(); ++i) // перебираем найденные циклы
	{
		for (int j = 0; j < cycle[i].size(); ++j) // перебираем вершины каждого цикла
		{
			cout << cycle[i][j] << " ";
		}
		cout << "\n";
	}
	WriteEnd();
}


void Graph::RunRecursive(int v, vector<bool>& visited) 
{
	visited[v] = true; // помечаем веришну как посещенную

	f << v << ",color=green,label=" << v << "\n"; // отображаем visited[v] 
	f << "w,500\n";

	for (Edge* e : esFrom[v]) 
	{
		// 2-5 из 2 => sosed=5
		// 2-5 из 5 => sosed=2
		const Vertex& sosed = (e->from.id == v) ? e->to : e->from;

		int eid = sosed.id;
		if (!visited[eid]) // проверяем, является ли вершина на другом конце ребра sosed уже посещённой
		{

			prev[eid] = v; // Помечаем вершину sosed как посещённую и устанавливаем её как предыдущую вершину (prev) для текущей вершины v

			k++;

			WriteEdge(v, eid); f << ",color=green\n"; // отображаем ребро между v и sosed на экране

			RunRecursive(eid, visited); // вызываем рекурсивно для этой вершины

			k--;

			f << eid << ",color=blue,label=" << eid << "\n";
			WriteEdge(v, eid); f << ",color=blue\n";
			f << "w,500\n";

		}
		else if (eid == start) // проверяем закончили ли обход цикла
		{
			AddCycle(v, eid);
		}
	}
	visited[v] = false;
}

Graph::~Graph() 
{
	for (size_t i = 0; i < edges.size(); i++)
	{
		delete edges[i];
	}
}