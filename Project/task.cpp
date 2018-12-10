#include "task.h"


int maxIdTask;//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void task::add(int x, int y)
{
	pointTask np;
	np._weight = 0;
	np._x = x;
	np._y = y;
	stackNEXT.push(np);
}

void task::addWW(int x, int y, float weight)
{
	pointTask np;
	np._weight = weight;
	np._x = x;
	np._y = y;
	stackNEXT.push(np);
}

pointTask task::top()
{
	if (!stackNEXT.empty()) { return stackNEXT.top(); }
}

void task::addTask(int idTask, int xTask, int yTask, int xNode, int yNode)
{
	taskStack t;
	t.idTask = idTask;
	t.Xnode = xNode;
	t.Ynode = yNode;
	t.xTask = xTask;
	t.yTask = yTask;
	taskSTACK.push(t);
}
taskStack task::takeTopTask()
{
	return taskSTACK.top();
}

void task::addTaskR(int idTaskR, int xTaskR, int yTaskR, int xNodeR, int yNodeR)
{
	historyOfRobTask t;
	t.idTaskofRob = idTaskR;
	t.XnodeR = xNodeR;
	t.YnodeR = yNodeR;
	t.xTaskR = xTaskR;
	t.yTaskR = yTaskR;
	TasksOfRobot.push(t);
}

task::task()
{
}


task::~task()
{
}
