#pragma once
#include <iostream>
#include <stack>


using namespace std;


struct pointTask
{
	int _x, _y;
	float _weight;
	
};
struct taskStack
{
	int xTask, yTask;//Координата клетки,продя на которую ,начнется выполнение задачи Z
	int Xnode,Ynode;//Узел или клетка,встав на которую открылась задача Z
	int idTask;// номер задачи Z
};
struct historyOfRobTask
{
	int xTaskR, yTaskR;//Координата клетки,продя на которую ,начнется выполнение задачи Z
	int XnodeR, YnodeR;//Узел или клетка,встав на которую открылась задача Z
	int idTaskofRob;// номер задачи Z
};


class task
{
private:
	pointTask last;
	pointTask prevx, prevy;
//	int prevx, prevy;///////////////////////////////////////////////////////////

public:
	stack<pointTask> stackNEXT;//hranilishe pridenih kletok
	void add(int x, int y);
	void addWW(int x, int y, float weight);//adding with weight
	pointTask top();

	stack<taskStack> taskSTACK;
	void addTask(int idTask,int xTask,int yTask,int xNode,int yNode);
	taskStack takeTopTask();
	void popTask();

	stack<historyOfRobTask> TasksOfRobot;
	void addTaskR(int idTaskR, int xTaskR, int yTaskR, int xNodeR, int yNodeR);
	taskStack takeTopRoboTask();


	task();
	~task();
};

