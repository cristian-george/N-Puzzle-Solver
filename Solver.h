#pragma once
#include "State.h"
#include "Node.h"
#include <unordered_map>

class Comparator
{
public:
	bool operator()(const Node* node1, const Node* node2) const
	{
		return node1->GetDepth() + node1->GetCost() > node2->GetDepth() + node2->GetCost();
	}
};

class Hash
{
public:
	std::size_t operator()(const State& state) const
	{
		return std::hash<std::string>()(state.HashCode());
	}
};

class Solver
{
public:
	Solver() = default;

	static void Solve(const State& initialState, const State& goalState);

private:
	static void FindSolution(Node* currentNode);
	static void PrintSolution(std::ostream& out);

private:
	static State GetNextState(const State& currentState, int pos0, int neighbour);
	static int InversionsNumber(const State& state);
	static bool IsSolvable(const State& state);

private:
	static int HammingCost(const State& currentState, const State& goalState);
	static int ManhattanCost(const State& currentState, const State& goalState);

private:
	static std::vector<State> solution;
};