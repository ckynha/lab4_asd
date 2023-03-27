#include "Graph.h"

Graph::Graph(int n)
{
	for (size_t i = 0; i < n; i++)
	{
		nodes.push_back(Vertex(i)); // ������� n �����
	}
	esFrom.resize(n);
	prev.resize(n); // ��� �������� ���������� � ���, �� ����� ������� ���� �������� ������� �������.
	k = 0; // ���������� ��� ��������� ������
	start = 0; // ������ ��������� ������� ��� ������ ������
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
	WriteEdge(cycle_end, start); f << ",color=green\n"; // ���������� ����� ����� ������ � ������� �����

	vector<int> temp; // ������ ��� ���������� ������, ���������� ����

	temp.push_back(cycle_st);

	// ������� ������� � ������ temp
	for (int v = cycle_end; v != cycle_st; v = prev[v]) 
	{
		temp.push_back(v);
	}

	temp.push_back(cycle_st);

	if (temp.size() > 3) // �������� �� ���������� ����
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


void Graph::RunAlgorithm() // ��������� ����� ����� � �������
{
	auto visited = vector<bool>(nodes.size(), false); // �������� ���������� � ���, ���� �� �������� �������
	for (int i = 0; i < nodes.size(); ++i) // ����������� �� ���� �������� �����
	{
		visited[i] = true; // �������� ������� ������� ��� ����������
		start = i;
		k = 1;
		RunRecursive(i, visited);
		visited[i] = true; // ���������� ������� � �������� ��������� ��� ��������� �������� �����
	}

	// ������� ��������� �����
	for (int i = 0; i < cycle.size(); ++i) // ���������� ��������� �����
	{
		for (int j = 0; j < cycle[i].size(); ++j) // ���������� ������� ������� �����
		{
			cout << cycle[i][j] << " ";
		}
		cout << "\n";
	}
	WriteEnd();
}


void Graph::RunRecursive(int v, vector<bool>& visited) 
{
	visited[v] = true; // �������� ������� ��� ����������

	f << v << ",color=green,label=" << v << "\n"; // ���������� visited[v] 
	f << "w,500\n";

	for (Edge* e : esFrom[v]) 
	{
		// 2-5 �� 2 => sosed=5
		// 2-5 �� 5 => sosed=2
		const Vertex& sosed = (e->from.id == v) ? e->to : e->from;

		int eid = sosed.id;
		if (!visited[eid]) // ���������, �������� �� ������� �� ������ ����� ����� sosed ��� ����������
		{

			prev[eid] = v; // �������� ������� sosed ��� ���������� � ������������� � ��� ���������� ������� (prev) ��� ������� ������� v

			k++;

			WriteEdge(v, eid); f << ",color=green\n"; // ���������� ����� ����� v � sosed �� ������

			RunRecursive(eid, visited); // �������� ���������� ��� ���� �������

			k--;

			f << eid << ",color=blue,label=" << eid << "\n";
			WriteEdge(v, eid); f << ",color=blue\n";
			f << "w,500\n";

		}
		else if (eid == start) // ��������� ��������� �� ����� �����
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