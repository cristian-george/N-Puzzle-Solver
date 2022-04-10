#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

class State
{
public:
	State(int dim = 0);
	State(const State& other);

	const std::string& HashCode() const;
	int Size() const;
	int PositionOf(int value) const;

	bool operator == (const State& other) const;
	bool operator != (const State& other) const;

	int& operator[](int index);
	const int& operator[](int index) const;

	State& operator=(const State& other);

	friend std::istream& operator>>(std::istream& in, State& state);
	friend std::ostream& operator<<(std::ostream& out, const State& state);

private:
	std::vector<int> m_config;
	int	m_dim;
};