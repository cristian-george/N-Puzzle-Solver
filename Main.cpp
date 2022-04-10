#include <fstream>
#include "State.h"
#include "Solver.h"

int main()
{
	std::ifstream fin("puzzle.in");

	State initial, goal;
	fin >> initial >> goal;

	Solver::Solve(initial, goal);
	return 0;
}