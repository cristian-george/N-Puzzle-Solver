#include "State.h"

State::State(int dim) : m_dim(dim)
{
	m_config.resize(m_dim * m_dim);
	for (int i = 0; i < Size(); ++i)
		m_config[i] = i;
}

State::State(const State& other)
{
	m_dim = other.m_dim;
	m_config = other.m_config;
}

const std::string& State::HashCode() const
{
	static std::string key;
	key.clear();

	for (int i = 0; i < Size(); ++i)
		key += std::to_string(m_config[i]) + " ";

	key.pop_back();
	return key;
}

int State::Size() const
{
	return m_config.size();
}

int State::PositionOf(int value) const
{
	for (int i = 0; i < Size(); ++i)
		if (m_config[i] == value)
			return i;

	return -1;
}

bool State::operator==(const State& other) const
{
	return m_dim == other.m_dim && m_config == other.m_config;
}

bool State::operator!=(const State& other) const
{
	return !(*this == other);
}

int& State::operator[](int index)
{
	return m_config[index];
}

const int& State::operator[](int index) const
{
	return m_config[index];
}

State& State::operator=(const State& other)
{
	if (this != &other)
	{
		this->~State();
		m_dim = other.m_dim;
		m_config = other.m_config;
	}

	return *this;
}

std::istream& operator>>(std::istream& in, State& state)
{
	in >> state.m_dim;
	state.m_config.resize(state.m_dim * state.m_dim);
	for (int i = 0; i < state.Size(); ++i)
		in >> state[i];
	return in;
}

std::ostream& operator<<(std::ostream& out, const State& state)
{
	for (int i = 0; i < state.m_dim; ++i, out << "\n")
		for (int j = 0; j < state.m_dim; ++j)
			out << std::setw(2) << state[i * state.m_dim + j] << " ";

	out << "\n";

	return out;
}
