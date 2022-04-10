#include "Solver.h"
#include "Graph.h"
#include "Node.h"
#include <fstream>
#include <queue>
#include <unordered_set>

std::vector<State> Solver::solution;

void Solver::Solve(const State& initialState, const State& goalState)
{
	std::ofstream fout("puzzle.out");

	if (!IsSolvable(initialState))
	{
		fout << "The puzzle cannot be solved !";
		return;
	}

	Graph graph(sqrt(initialState.Size()));
	std::unordered_set<std::string> visitedNodes;

	std::priority_queue<Node*, std::vector<Node*>, Comparator> openQueue;
	openQueue.push(new Node(initialState));

	while (!openQueue.empty())
	{
		Node* currentNode = openQueue.top();
		openQueue.pop();

		State currentState = currentNode->GetState();
		if (currentState == goalState)
		{
			FindSolution(currentNode);
			PrintSolution(fout);
			break;
		}

		if (visitedNodes.find(currentState.HashCode()) != visitedNodes.end())
			continue;

		int pos0 = currentState.PositionOf(0);
		for (const auto& neighbour : graph[pos0])
		{
			State nextState = GetNextState(currentState, pos0, neighbour);

			int cost = HammingCost(nextState, goalState) + ManhattanCost(nextState, goalState);
			int depth = currentNode->GetDepth() + 1;

			openQueue.push(new Node(nextState, currentNode, depth, cost + depth));
		}

		visitedNodes.insert(currentState.HashCode());
	}
}

void Solver::FindSolution(Node* currentNode)
{
	while (currentNode != nullptr)
	{
		solution.push_back(currentNode->GetState());
		currentNode = currentNode->GetParent();
	}

	reverse(solution.begin(), solution.end());
}

void Solver::PrintSolution(std::ostream& out)
{
	out << "The puzzle has been solved in " << solution.size() - 1 << " steps: \n";
	for (const auto& state : solution)
		out << state << std::endl;
}

State Solver::GetNextState(const State& currentState, int pos0, int neighbour)
{
	State nextState = currentState;
	std::swap(nextState[pos0], nextState[neighbour]);
	return nextState;
}

int Solver::InversionsNumber(const State& state)
{
	int inversions = 0;

	for (int i = 0; i < state.Size() - 1; ++i)
		for (int j = i + 1; j < state.Size(); ++j)
			if (state[i] && state[j] && state[i] > state[j])
				++inversions;

	return inversions;
}

bool Solver::IsSolvable(const State& state)
{
	int inversions = InversionsNumber(state);
	int dim = state.Size();
	if (dim % 2 == 1)
		return inversions % 2 == 0;

	int line0 = state.PositionOf(0) / dim;
	return (line0 % 2 == 0 && inversions % 2 == 1) or (line0 % 2 == 1 && inversions % 2 == 0);
}

int Solver::HammingCost(const State& currentState, const State& goalState)
{
	int cost = 0;

	for (int i = 0; i < currentState.Size(); ++i)
		if (currentState[i] && currentState[i] != goalState[i])
			++cost;

	return cost;
}

int Solver::ManhattanCost(const State& currentState, const State& goalState)
{
	int cost = 0;
	int size = sqrt(currentState.Size());

	for (int i = 0; i < currentState.Size(); ++i)
		if (currentState[i] && currentState[i] != goalState[i])
		{
			int valDest = goalState.PositionOf(currentState[i]);

			int x = i % size;
			int y = i / size;

			int xDest = valDest % size;
			int yDest = valDest / size;

			cost += abs(x - xDest) + abs(y - yDest);
		}

	return cost;
}
