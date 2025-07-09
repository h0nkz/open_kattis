/*
	solution for https://open.kattis.com/problems/bigtruck
*/

#include <vector>
#include <iostream>
#include <queue>
#include <limits>

class Edge
{
private:
	int _to;
	int _from;
	int _weight;

public:
	Edge(int from, int to, int weight) : _from(from), _to(to), _weight(weight) {}
	int weight()
	{
		return _weight;
	}
	int from()
	{
		return _from;
	}
	int to()
	{
		return _to;
	}

	bool operator==(Edge& rhs)
	{
		return _weight == rhs._weight;
	}

	bool operator<(Edge& rhs)
	{
		return _weight < rhs._weight;
	}

	bool operator>(Edge& rhs)
	{
		return _weight > rhs._weight;
	}
};

class Graph
{
private:
	const int _vertices;
	int _edges;
	std::vector<std::vector<Edge>> _adjacencyList;

public:
	Graph(int vertices) : _vertices(vertices), _edges(0)
	{
		for (int i = 0; i < _vertices; i++)
		{
			_adjacencyList.push_back(std::vector<Edge>());
		}
	}

	int vertices()
	{
		return _vertices;
	}

	int edges()
	{
		return _edges;
	}

	void addEdge(int from, int to, int weight)
	{
		Edge e(from, to, weight);
		_adjacencyList[from].push_back(e);
		_edges++;
	}

	std::vector<Edge> adjacent(int vertice)
	{
		return _adjacencyList[vertice];
	}

};

typedef std::pair<int, int> iPair;

class ShortestPath
{
private:
	std::vector<int> distanceTo;
	std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> pq;
	std::vector<int> itemsTo;

public:
	ShortestPath(Graph& graph, int source, std::vector<int>& items)
	{
		const int int_max = std::numeric_limits<int>::max();
		const int int_min = std::numeric_limits<int>::min();
		for (int i = 0; i < graph.vertices(); i++)
		{
			distanceTo.push_back(int_max);
			itemsTo.push_back(int_min);

		}
		distanceTo[source] = 0;
		itemsTo[source] = items[source];

		pq.push(std::make_pair(0, source));

		while (!pq.empty())
		{
			int vertice = pq.top().second;
			relax(graph, vertice, items);
		}
	}

	void relax(Graph& graph, int vertice, std::vector<int>& items) 
	{
        int currentDistance = distanceTo[vertice];
        int currentItems = itemsTo[vertice];
    
        pq.pop();
    
        for (Edge& edge : graph.adjacent(vertice)) {
            int w = edge.to();
            int newDistance = currentDistance + edge.weight();
            int newItems = currentItems + items[w];
    
            if (newDistance < distanceTo[w] || (newDistance == distanceTo[w] && newItems > itemsTo[w])) {
                distanceTo[w] = newDistance;
                itemsTo[w] = newItems;
                pq.push(std::make_pair(newDistance, w));
            }
        }
    }

	int getDistanceTo(int vertice)
	{
		return distanceTo[vertice];
	}

	int getItemsTo(int vertice)
	{
		return itemsTo[vertice];
	}
};

int main()
{
	int locations, roads;
	std::vector<int> items;

	std::cin >> locations;
	Graph graph(locations);

	int item;
	for (int i = 0; i < locations; i++)
	{
		std::cin >> item;
		items.push_back(item);
	}

	std::cin >> roads;

	int from, to, length;
	for (int i = 0; i < roads; i++)
	{
		std::cin >> from;
		std::cin >> to;
		std::cin >> length;

		graph.addEdge(from - 1, to - 1, length);
		graph.addEdge(to - 1, from - 1, length);
	}

	ShortestPath sp(graph, 0, items);

	int distance = sp.getDistanceTo(locations - 1);
	int numItems = sp.getItemsTo(locations - 1);
	if (distance == std::numeric_limits<int>::max())
	{
		std::cout << "impossible";
	}
	else
	{
		std::cout << distance << " " << numItems;
	}
}