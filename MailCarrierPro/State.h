#pragma once
#define M 100
class State
{
public:
	CPoint point;
	int degree;
	bool visited;
	CPoint* next=new CPoint[M]();
	int related[M] = {0};//����Ӧ���Ƿ�Ϊ��
public:

	State();
	State(CPoint p);
	~State();
	const State& operator = (const State& s);
	void SetZero();
};

