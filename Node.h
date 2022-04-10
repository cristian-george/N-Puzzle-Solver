#pragma once
#include "State.h"

class Node
{
public:
	Node(const State& state, Node* parent = nullptr, int depth = 0, int cost = 0);

	const State& GetState() const;
	Node* GetParent() const;
	int GetDepth() const;
	int GetCost() const;

private:
	State m_state;
	Node* m_parent;
	int m_depth;
	int m_cost;
};