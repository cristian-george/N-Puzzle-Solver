#pragma once
#include <unordered_map>

class Graph
{
public:
	Graph(int dim = 0);

	const std::vector<int>& operator[](int node) const;

private:
	void InitializeGraph(int dim);

private:
	std::unordered_map<int, std::vector<int>> m_neighbours;
};