#include "Node.h"

Node::Node(const State& state, Node* parent, int depth, int cost) :
	m_state(state), m_parent(parent), m_depth(depth), m_cost(cost) {}

const State& Node::GetState() const
{
	return m_state;
}

Node* Node::GetParent() const
{
	return m_parent;
}

int Node::GetDepth() const
{
	return m_depth;
}

int Node::GetCost() const
{
	return m_cost;
}