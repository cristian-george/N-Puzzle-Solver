#include "Graph.h"

Graph::Graph(int dim)
{
	InitializeGraph(dim);
}

const std::vector<int>& Graph::operator[](int node) const
{
	return m_neighbours.at(node);
}

void Graph::InitializeGraph(int dim)
{
	const int dx[] = { -1, 0, 1, 0 };
	const int dy[] = { 0, 1, 0, -1 };

	for (int i = 0; i < dim; ++i)
		for (int j = 0; j < dim; ++j)
			for (int k = 0; k < 4; ++k)
			{
				int x = i + dx[k];
				int y = j + dy[k];

				if (x >= 0 && x < dim && y >= 0 && y < dim)
					m_neighbours[i * dim + j].push_back(x * dim + y);
			}
}
