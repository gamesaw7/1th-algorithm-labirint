#include "robot.h"
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include "Source/Drawler.h"
#include "Source/TwodObj.h"
#include "keyboard.h"
#include "mouse.h"
#include "world.h"
#include "robot.h"
#include "RRT.h"
#include <Box2D.h>
#include "task.h"

//sf::RenderWindow window(sf::VideoMode(1900, 1000), "Window");
//Drawler dr(window);

//sf::RenderWindow window(sf::VideoMode(1900, 1000), "Window");
int MAXIDTASK=1;//////////////////////////////////////////////////////////////////////////////////////////
robot::robot()
{
}

robot::~robot()
{

}

void robot::setSpeed(float sp)
{
	_speed = sp;
}

//отсчет от нуля wx wy
void robot::init(int worldX, int worldY, world &w, sf::RenderWindow &window, Drawler &dr)
{
	_world.initMap(w.getX(), w.getY(), window);
	_world.setValue(worldX, worldY, 2);
	curXWorld = worldX;
	curYWorld = worldY;
	curXWorldOld = worldX;
	curYWorldOld = worldY;
	curX = w.whereAmIinPixels(curXWorld, curYWorld).x;
	curY = w.whereAmIinPixels(curXWorld, curYWorld).y;
	_avatar.setPic("robot_3", dr);
	_avatar.setCoord(curX, curY);
	_avatar.initWH(100, 100);

}

void robot::addPoint(int worldX, int worldY, int status)
{
	_world.setValue(worldX, worldY, status);
}

void robot::askWorld(world &w)
{
	curXWorld = w.whereAmI(curX, curY).x;// tekushie coordinati 
	curYWorld = w.whereAmI(curX, curY).y;// robota
	if (curXWorld != curXWorldOld || curYWorld != curYWorldOld)// если текущие координаты не равны еоординатам предыдущего шага
	{
		last._x = curXWorldOld;// last-временная переменная для сохранения старого значения положения (предыдущего положения)
		last._y = curYWorldOld;
		curXWorldOld = curXWorld;// При перемещении на сл. клетку координаты тогда нынешней клетки стали теперь координатами предыдущей клетки
		curYWorldOld = curYWorld;
	}
	if (w.isLeft(curXWorld, curYWorld))
	{
		if (_world.whatAmI(curXWorld - 1, curYWorld) == 0)_world.setValue(curX - 1, curY, 3);// если следующая клетка для посещения пуста,то  ставим ей значение 3
		if (tarX < 0 && tarY < 0)// когда достигли нынешней целевой клетки (тогда tarX=tarY= -1)
		{
			tarX = (int)_world.whereAmIinPixels(curXWorld - 1, curYWorld).x;// цель по х равна кординатам клетки слева ( в пикселях)
			tarY = (int)_world.whereAmIinPixels(curXWorld - 1, curYWorld).y;
		}
	}
	if (w.isRight(curXWorld, curYWorld))
	{
		if (_world.whatAmI(curXWorld+1, curYWorld) == 0)_world.setValue(curX+1, curY, 3);
		if (tarX < 0 && tarY < 0)
		{
			tarX = (int)_world.whereAmIinPixels(curXWorld + 1, curYWorld).x;
			tarY = (int)_world.whereAmIinPixels(curXWorld + 1, curYWorld).y;
		}
	}
	if (w.isDown(curXWorld, curYWorld))
	{
		if (_world.whatAmI(curXWorld, curYWorld-1) == 0)_world.setValue(curX, curY-1, 3);
		if (tarX < 0 && tarY < 0)
		{
			tarX = (int)_world.whereAmIinPixels(curXWorld, curYWorld - 1).x;
			tarY = (int)_world.whereAmIinPixels(curXWorld, curYWorld - 1).y;
		}
	}
	if (w.isUp(curXWorld, curYWorld))
	{
		if (_world.whatAmI(curXWorld, curYWorld+1) == 0)_world.setValue(curX, curY+1, 3);
		if (tarX < 0 && tarY < 0)
		{
			tarX = (int)_world.whereAmIinPixels(curXWorld, curYWorld + 1).x;
			tarY = (int)_world.whereAmIinPixels(curXWorld, curYWorld + 1).y;
		}
	}

	




}

void robot::goToTarget()
{
	if (tarX >= 0 && tarY >= 0)
	{
		float dx = tarX - curX;
		float dy = tarY - curY;
		float len = sqrtf(dx*dx + dy*dy);
		if (len > _speed*1.2)
		{
			float k = _speed / len;
			dx *= k;
			dy *= k;
			curX += dx;
			curY += dy;
			float angle = 57.29*atan2f(dy, dx) + 90;
			_avatar.setRotation(angle);
		}
		else
		{
			tar.x = -1;
			tar.y = -1;
			//change target of robot to next point in task.h
		}
	}
}

void robot::setTarget(int worldX, int worldY)
{
	tarX = _world.whereAmIinPixels(worldX, worldY).x;
	tarY = _world.whereAmIinPixels(worldX, worldY).y;
}

void robot::update(world & w)
{
	askWorld(w);
	goToTarget();
}

void robot::draw(Drawler & dr, sf::RenderWindow &window)
{
	_avatar.setCoord(curX, curY);
	_avatar.draw(dr);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void robot::Going(world &w,task &t)
{
	curXWorld = w.whereAmI(curX, curY).x;// tekushie coordinati 
	curYWorld = w.whereAmI(curX, curY).y;// robota

	if (!t.stackNEXT.empty()) { // Если стек пустой (при первом вызове функции Going) -то выдаст ошибку,если просто написать :  prevPoint = t.top();
		prevPoint = t.top();
	}

	if (curXWorld != curXWorldOld || curYWorld != curYWorldOld)// если текущие координаты не равны еоординатам предыдущего шага
	{
		last._x = curXWorldOld;// last-временная переменная для сохранения старого значения положения (предыдущего положения)
		last._y = curYWorldOld;
		curXWorldOld = curXWorld;// При перемещении на сл. клетку координаты тогда нынешней клетки стали теперь координатами предыдущей клетки
		curYWorldOld = curYWorld;
	}
	if (curXWorld == 9 && curYWorld == 8)//////////////////////////
	{
		int a = 10;///////////////// Можно удалять Можно удалять Можно удалять Можно удалять Можно удалять Можно удалять Можно удалять Можно удалять Можно удалять Можно удалять 
	}////////////////////////////////////////////////////
	if (bool Vyrazheninie = ((CheckPrev(t)) ? (w.isLeft(curXWorld, curYWorld) && (prevPoint._x != curXWorld - 1)) :( w.isLeft(curXWorld, curYWorld))))
	{
		//if (_world.whatAmI(curXWorld, curYWorld) == 0)_world.setValue(curXWorld, curYWorld, 3);// если следующая клетка для посещения пуста,то  ставим ей значение 3
		//if (_world.whatAmI(curXWorld, curYWorld) == 0)_world.setValue(curXWorld, curYWorld, 3);
		if (w.whatAmI(curXWorld, curYWorld) == 0)w.setValue(curXWorld, curYWorld, 3);
		setTarget(curXWorld - 1, curYWorld);
		setSpeed(15);
		t.add(curXWorld, curYWorld);
		for (int i = 0; i < 15; i++) { goToTarget(); }  return;
}
	if (bool Vyrazheninie = ((CheckPrev(t)) ? (w.isRight(curXWorld, curYWorld) && (prevPoint._x != curXWorld + 1)): (w.isRight(curXWorld, curYWorld))))
	{
		//if (_world.whatAmI(curXWorld, curYWorld) == 0)_world.setValue(curXWorld, curYWorld, 3);
		if (w.whatAmI(curXWorld, curYWorld) == 0)w.setValue(curXWorld, curYWorld, 3);


		setTarget(curXWorld + 1, curYWorld);
		setSpeed(15);
		t.add(curXWorld, curYWorld);
		for (int i = 0; i < 10; i++) { goToTarget(); }  return;

	}
	if (bool Vyrazheninie = ((CheckPrev(t)) ? (w.isDown(curXWorld, curYWorld) && (prevPoint._y != curYWorld+1)): (w.isDown(curXWorld, curYWorld))))
	{
		//if (_world.whatAmI(curXWorld, curYWorld) == 0)_world.setValue(curXWorld, curYWorld, 3);
		if (w.whatAmI(curXWorld, curYWorld) == 0)w.setValue(curXWorld, curYWorld, 3);
		setTarget(curXWorld, curYWorld + 1);
		setSpeed(15);
		t.add(curXWorld, curYWorld);
		for (int i = 0; i < 10; i++) { goToTarget(); }   return;
	}
	if (bool Vyrazheninie = ((CheckPrev(t)) ? (w.isUp(curXWorld, curYWorld) && (prevPoint._y != curYWorld-1)): (w.isUp(curXWorld, curYWorld))))
	{
		//if (_world.whatAmI(curXWorld, curYWorld) == 0)_world.setValue(curX, curY, 3);
		//if (_world.whatAmI(curXWorld, curYWorld) == 0)_world.setValue(curXWorld, curYWorld, 3);
		if (w.whatAmI(curXWorld, curYWorld) == 0)w.setValue(curXWorld, curYWorld, 3);

		setTarget(curXWorld, curYWorld - 1);
		setSpeed(15);
		t.add(curXWorld, curYWorld);
		for (int i = 0; i < 10; i++) { goToTarget(); }  return;
	}
}

bool robot::CheckPrev(task &t)// Проверка на налчие предыдущей посещенной клетки в стеке (т.е. проверка на наличие самого стека)
{
	if (t.stackNEXT.size() !=0)//  razmer steka ne 0?
	{ 
		return true; // da,stek ne pustoy
	}
	else
	{
		return false;//stek pust
	}
}
void robot::FindTask(world &w, task &t,Drawler &d, sf::RenderWindow &window)
{
	int xnoder=t.TasksOfRobot.top().XnodeR, ynoder=t.TasksOfRobot.top().YnodeR;
	//////////////////////////////////
	curXWorld = w.whereAmI(curX, curY).x;// tekushie coordinati 
	curYWorld = w.whereAmI(curX, curY).y;// robota
	if (curXWorld == 9 && curYWorld == 8)
	{
		int a = 10;
	}
	if (!t.stackNEXT.empty()) { // Если стек пустой (при первом вызове функции Going) -то выдаст ошибку,если просто написать :  prevPoint = t.top();
		prevPoint = t.top();
	}
	int sch = 0;// Счетчик количества задач
	int i = 0;// Счетчик массива строк
	//string freeDirection;
	string freeDirection[4];
	if (bool Vyrazheninie = ((CheckPrev(t)) ? (w.isDown(curXWorld, curYWorld) && (prevPoint._y != curYWorld + 1)) : (w.isDown(curXWorld, curYWorld)))) { sch++; freeDirection[i] = "Down"; i++; }
	if (bool Vyrazheninie = ((CheckPrev(t)) ? (w.isUp(curXWorld, curYWorld) && (prevPoint._y != curYWorld - 1)) : (w.isUp(curXWorld, curYWorld)))) { sch++; freeDirection[i] = "Up"; i++; }
	if (bool Vyrazheninie = ((CheckPrev(t)) ? (w.isLeft(curXWorld, curYWorld) && (prevPoint._x != curXWorld - 1)) : (w.isLeft(curXWorld, curYWorld)))) { sch++; freeDirection[i] = "Left"; i++; }
	if (bool Vyrazheninie = ((CheckPrev(t)) ? (w.isRight(curXWorld, curYWorld) && (prevPoint._x != curXWorld + 1)) : (w.isRight(curXWorld, curYWorld)))) { sch++; freeDirection[i] = "Rigt";i++; }
	switch (sch)
	{
	case 1: Going(w, t); return;// Есть только одна свободная клетка и эта не та,из которой мы пришли => продолжаем простое движение по кишке =)
	case 2: for (int i = 0; i < 4; i++) { addTaskToStack(w, t, freeDirection, i); }; setTarget(t.taskSTACK.top().xTask, t.taskSTACK.top().yTask); t.add(curXWorld, curYWorld);  for (int i = 0; i < 10; i++) { goToTarget(); } return;// (sizeof(freeDirection)/sizeof(char*) -просто выпендрежное
	case 3: for (int i = 0; i < 4; i++) { addTaskToStack(w, t, freeDirection, i); }; setTarget(t.taskSTACK.top().xTask, t.taskSTACK.top().yTask); t.add(curXWorld, curYWorld); for (int i = 0; i < 10; i++) { goToTarget(); }return;// определение размера массива строк,которое итак равно константе 4 =)

	//case 2: for (int i = 0; i < 4; i++) { addTaskToStack(w, t, freeDirection, i); }; setTarget(t.taskSTACK.top().xTask, t.taskSTACK.top().yTask); t.add(curXWorld, curYWorld); for (int i = 0; i < 10; i++) { goToTarget(); } return;// (sizeof(freeDirection)/sizeof(char*) -просто выпендрежное
	//case 3: for (int i = 0; i < 4; i++) { addTaskToStack(w, t, freeDirection, i); }; setTarget(t.taskSTACK.top().xTask, t.taskSTACK.top().yTask); t.add(curXWorld, curYWorld); for (int i = 0; i < 10; i++) { goToTarget(); }return;// определение размера массива строк,которое итак равно константе 4 =)

	case 0: 
		//if ((xnoder != curXWorld) && (ynoder != curYWorld))//if ((t.TasksOfRobot.top().XnodeR != curXWorld) && (t.TasksOfRobot.top().YnodeR != curYWorld))
		if (w.whatAmI(curXWorld, curYWorld) == 0)w.setValue(curXWorld, curYWorld, 3);
		//////////////////////////

		do
			{
				curXWorld = w.whereAmI(curX, curY).x;// tekushie coordinati 
				curYWorld = w.whereAmI(curX, curY).y;// robota
				window.clear(sf::Color::White);
				w.draw(window);
				draw(d, window);////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////11111111111111111
				window.display();
				sf::sleep(sf::milliseconds(33));
				//if (t.taskSTACK.size() == 2) 
			//	{ return; }
				if (curXWorld == 9 && curYWorld == 8)
				{
					int a = 10;
				}
				if (t.stackNEXT.size() != 0 && (!(t.taskSTACK.top().Xnode == curXWorld && t.taskSTACK.top().Ynode == curYWorld))) //if (t.stackNEXT.size() != 0 && (!(t.TaskOfRobot.top().Xnode == curXWorld && t.TaskOfRobot.top().Ynode == curYWorld)))
				{
					setTarget(t.stackNEXT.top()._x, t.stackNEXT.top()._y); t.stackNEXT.pop();
					for (int i = 0; i < 10; i++) { goToTarget(); }
				}
				else if(t.stackNEXT.size() == 0) { return; }
				if (t.taskSTACK.top().Xnode == curXWorld && t.taskSTACK.top().Ynode == curYWorld)//if (t.TasksOfRobot.top().XnodeR == curXWorld && t.TasksOfRobot.top().YnodeR == curYWorld)
				{
					t.TasksOfRobot.pop(); t.taskSTACK.pop(); t.add(curXWorld, curYWorld);//t.TasksOfRobot.pop(); t.taskSTACK.pop();
					if (w.whatAmI(curXWorld, curYWorld) == 0)w.setValue(curXWorld, curYWorld, 3);// раньше не красили узлы.... тестовая штука
					if (t.taskSTACK.top().Xnode == curXWorld && t.taskSTACK.top().Ynode == curYWorld)
					{
						setTarget(t.taskSTACK.top().xTask,t.taskSTACK.top().yTask);
						for (int i = 0; i < 10; i++) { goToTarget(); }
					}
				
					return;
				}  // Что происходит?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????? t.TasksOfRobot.pop(); t.taskSTACK.pop();t.TasksOfRobot.pop(); t.taskSTACK.pop();






			} while (!((xnoder == curXWorld) && (ynoder == curYWorld)));//while (t.TasksOfRobot.top().XnodeR != curXWorld && t.TasksOfRobot.top().YnodeR != curYWorld);
		
			////////////////////////////////
		if (t.TasksOfRobot.top().XnodeR == curXWorld && t.TasksOfRobot.top().YnodeR == curYWorld)//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
		//w.setValue(t.TasksOfRobot.top().xTaskR, t.TasksOfRobot.top().yTaskR, 2);// выполнили задачу,вернулись к порождающему (задачу) узлу => ставим заглушку ,т.е. вместо пустой клетки,с которой начинали задачу- ставим препятствие,чтобы не добавить задачу снова при сканировании роботом окружающих клеток
		//	t.TasksOfRobot.pop(); t.taskSTACK.pop();// выполнили задачу,вернулись к порождающему (задачу) узлу => вынимаем задачу из общего стека и стека робота
		}
		return; // case 0 => Мы достигли тупика => возврат к предыдущему узлу
// И пока координаты узла (развилки ,где появилась задача Z) задачи Z не равны текущим координатам робота - устанавливаем цель:предыдущая клетка,которую берем из стека посещенных клеток,а потом выход из функции (findTask)


	default: return;




	}
}
void robot::addTaskToStack(world &w, task &t,string *s,int i)// Добавление задачи в стэк задач
{
	curXWorld = w.whereAmI(curX, curY).x;// tekushie coordinati 
	curYWorld = w.whereAmI(curX, curY).y;// robota

	if (s[i] == "Down") { t.addTask(MAXIDTASK, curXWorld, curYWorld + 1, curXWorld, curYWorld); t.addTaskR(MAXIDTASK, curXWorld, curYWorld + 1, curXWorld, curYWorld); MAXIDTASK++; }// клетка снизу свободна и мы не от нее пришли- добавим ее в общий стэк задач и стэк задач робота
		if (s[i] == "Up"){ t.addTask(MAXIDTASK, curXWorld, curYWorld - 1, curXWorld, curYWorld); t.addTaskR(MAXIDTASK, curXWorld, curYWorld + 1, curXWorld, curYWorld); MAXIDTASK++; }
			if (s[i] == "Rigt"){ t.addTask(MAXIDTASK, curXWorld+1, curYWorld, curXWorld, curYWorld); t.addTaskR(MAXIDTASK, curXWorld, curYWorld + 1, curXWorld, curYWorld); MAXIDTASK++; }
				if (s[i] == "Left"){ t.addTask(MAXIDTASK, curXWorld-1, curYWorld, curXWorld, curYWorld); t.addTaskR(MAXIDTASK, curXWorld, curYWorld + 1, curXWorld, curYWorld); MAXIDTASK++; }

}
//void task::addTask(int idTask, int xTask, int yTask, int xNode, int yNode)

void robot::chooseTaskAndGovoid(world &w, task &t, taskStack task)
{
	if (curXWorld == t.takeTopTask().Xnode && curYWorld == t.takeTopTask().Ynode)
	{
		setTarget(t.takeTopTask().xTask, t.takeTopTask().yTask);
	}
}
///////////////////////////////////////////////
void robot::initTaskRobot(world &w, task &t)// инициализация нулевой задачи, от которой будет ветвиться граф задач и ,к клетке которой,в конце своего долгого пути врнется робот
{
	t.addTaskR(0, curXWorld, curYWorld, curXWorld, curYWorld);
	t.addTask(0, curXWorld, curYWorld, curXWorld, curYWorld);
}


//do
//{
//	curXWorld = w.whereAmI(curX, curY).x;// tekushie coordinati 
//	curYWorld = w.whereAmI(curX, curY).y;// robota
//	if (curXWorld == 9 && curYWorld == 8)
//	{
//		int a = 10;
//	}
//	if (t.stackNEXT.size() != 0)
//	{
//		setTarget(t.stackNEXT.top()._x, t.stackNEXT.top()._y); t.stackNEXT.pop();
//		for (int i = 0; i < 10; i++) { goToTarget(); }
//	}
//	else { return; }
//} while (!((xnoder == curXWorld) && (ynoder == curYWorld)));//while (t.TasksOfRobot.top().XnodeR != curXWorld && t.TasksOfRobot.top().YnodeR != curYWorld);