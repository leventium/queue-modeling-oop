#ifndef CONTROL
#define CONTROL

#include <iostream>
#include <stdio.h>
#include <conio.h>
//#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include "collection.h"
#include "units.h"
#include "kasses.h"
using namespace std;

#define CLR while (getchar()!='\n')

class Control
{
private:
    int dayTime, nType, times[5];
    // dayTime - заданное время дня
    // nType - заданное количество типов
    // times[] - заданное время обработки каждого типа
public:
    void printQueue();
    void printStat();
    int queueCount();
    void makeStat();

    int read(void);
    void check(UnitsCollection<QueueUnit>& queue, UnitsCollection<StatUnit>& stat, int &n, Kasses &kass);
    void enter(Kasses &kass, UnitsCollection<QueueUnit> &queue, UnitsCollection<StatUnit> &stat, int &n);
};

#endif CONTROL


int Control::read(void)
{
	char str[80];
	int n, k, f = 0;
	do
	{
		cout << " (enter a positive integer) " << endl;
		cin >> str;
		k = cin.fail();
		if (!k)
		{
			if (strcmp(str, "0") == 0) n = 0, f = 0;
			else
				if (strcmp(str, "") != 0 && !strchr(str, ','))
				{
					char* s = str;
					while (isdigit(*s))
						s++;

					if (!*s)
					{
						n = atoi(str);
						if (n) f = 1;
					}
				}
		}
	} while (!f);
	CLR;
	return n;
}

void Control::check(UnitsCollection<QueueUnit>& queue, UnitsCollection<StatUnit>& stat, int& n, Kasses& kass)
{
	char C[70];
	UnitsCollection<QueueUnit> queue1;
	QueueUnit queueOne;
	StatUnit statOne;
	int ch, i, j, q, nc, timeoch, w;
	//timeoch - время обработки текущей очереди, nc - количество элементов в массиве C, queue1 - копия матрицы очереди
	cout << "Введите очередь в формате: ABDABC" << endl;
	j = n;
	i = 0;
	ch = _getche();
	while ((j < 70) && (ch != 13))
	{
		C[i] = (char)ch;
		ch = _getche();
		i++;
		j++;
	}
	nc = i - 1;
	cout << endl;

	for (i = 0; i <= nc; i++)
	{
		if ((65 <= (int)C[i]) && ((int)C[i] <= (69 - (5 - nType))))  //проверка вводимого символа
		{
			if (queue.size() >= 30) //условие переполнения очереди по количеству заявок
			{ //запись в статистику
				n++;
				statOne.setNumber(n);
				statOne.setType((int)C[i]);
				statOne.setUnique(0);
				stat << statOne;
			}
			else //запись в очередь
			{
				n++;
				queueOne.setNumber(n);
				queueOne.setType((int)C[i]);
				queueOne.setUnique(times[(int)C[i]]);
				queue1.delAll();
				for (w = 0; w <= queue.size(); w++)
				{
					queue1 << queue[w];
				}
				//timeoch = QueueCount(kass, time, nqueue1, queue1);
				//cout << timeoch << endl;
				timeoch = 1;
				if (timeoch > dayTime) //условие переполнения очереди по времени обработки заявок
				{
					//запись в статистику
					queue.del(queue.size());
					statOne.setNumber(n);
					statOne.setType((int)C[i]);
					statOne.setUnique(0);
					stat << statOne;
				}

			}
		}
	}
}


void Control::enter(Kasses& kass, UnitsCollection<QueueUnit>& queue, UnitsCollection<StatUnit>& stat, int& n)
{
	int i, a;
	{
		cout << "Enter the number of application types (maximum 5)";
		nType = read();
	} while ((nType > 5));

	for (i = 0; i < nType; i++)
	{
		do
		{
			cout << "Enter for " << (char)(65 + i) << " type application processing time (in seconds from 1 to 30)";
			times[i] = read();
		} while ((times[i] > 30));
	}

	do
	{
		cout << "Enter the length of the working day in seconds (in seconds from 30 to 300)";
		dayTime = read();
	} while ((dayTime < 30) || (dayTime > 300));

	do
	{
		cout << "Enter the number of cash registers (maximum 5)";
		a = read();
	} while ((a > 5));
	kass.setAmount(a);

	/*do
	{
		check(queue, stat, n, kass);
	} while (queue.size() == 0); //the case when the user did not enter anything or entered the wrong characters*/
	
}