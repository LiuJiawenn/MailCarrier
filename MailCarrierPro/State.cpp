#include "stdafx.h"
#include "State.h"


State::State()
{
}

State::State(CPoint p)
{
	point = p;
	degree = 0;
	visited = 0;
}


State::~State()
{
}

const State & State::operator=(const State & s)
{
	point=s.point;
	degree=s.degree;
	visited=s.visited;
	for (int i = 0; i < degree; i++)
	{
		next[i] = s.next[i];
		related[i] = s.related[i];
	}
	return *this;
}
void State::SetZero()
{
	for (int i = 0; i < degree; i++)
	{
		next[i] = 0;
		related[i] = 0;
	}
	point = 0;
	degree = 0;
	visited = false;
}
