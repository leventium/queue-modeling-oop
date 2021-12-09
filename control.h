#ifndef CONTROL
#define CONTROL

#include <iostream>
#include <stdio.h>
//#include <conio.h>
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
    int workTime, nowTime, nType, times[5];
	// workTime - время рабочего дня (вводится один раз)
	// nowTime - текущее время (меняется каждую секунду)
    // nType - заданное количество типов
    // times[] - заданное время обработки каждого типа
public:
    void printQueue(Kasses &kassa, const UnitsCollection<QueueUnit> &queue) const;
    void printStat();
    int queueCount(Kasses &kass, UnitsCollection<QueueUnit> &queue);
    void makeStat();

    int read(void);
    void check(UnitsCollection<QueueUnit> &queue, UnitsCollection<StatUnit> &stat, int &n, Kasses &kass);
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
	cout << "Enter the queue in the format: ABDABC" << endl;
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
				queueOne.setUnique(times[(int)C[i]-65]);
				queue << queueOne;
				queue1.delAll();
				for (w = 0; w < queue.size(); w++)
				{
					queue1 << queue[w];
				}
				//timeoch = QueueCount(kass, time, nqueue1, queue1);
				//cout << timeoch << endl;
				timeoch = 1;
				if (timeoch > nowTime) //условие переполнения очереди по времени обработки заявок
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
		nowTime = read();
	} while ((nowTime < 30) || (nowTime > 300));

	do
	{
		cout << "Enter the number of cash registers (maximum 5)";
		a = read();
	} while ((a > 5));
	kass.setAmount(a);

	int c;
	do
	{
		check(queue, stat, n, kass);
	    c = queue.size();
	} while (c == 0); //the case when the user did not enter anything or entered the wrong characters
	
}

/*int Control::queueCount(Kasses& kass, UnitsCollection<QueueUnit>& queue)
{

}*/

void Control::printQueue(Kasses& kassa, const UnitsCollection<QueueUnit>& queue) const
{
	int i, n;
	char table[20][80];
	strcpy_s(table[0], "#########################################################");
	strcpy_s(table[1], "#.......................................................#");
	strcpy_s(table[2], "#.......................................................#");
	strcpy_s(table[3], "#.....KASSA.....KASSA.....KASSA.....KASSA.....KASSA.....#");
	strcpy_s(table[4], "#.....CLOSE.....CLOSE.....CLOSE.....CLOSE.....CLOSE.....#");
	strcpy_s(table[5], "#.......................................................#");
	strcpy_s(table[6], "#.......................................................#");
	strcpy_s(table[7], "#.......................................................#");
	strcpy_s(table[8], "#.......................................................#");
	strcpy_s(table[9], "#.......................................................#");
	strcpy_s(table[10], "#.......................................................#");
	strcpy_s(table[11], "#.......................................................#");
	strcpy_s(table[12], "#.......................................................#");
	strcpy_s(table[13], "#.......................................................#");
	strcpy_s(table[14], "#.......................................................#");
	strcpy_s(table[15], "#.......................................................#");
	strcpy_s(table[16], "#.......................................................#");
	strcpy_s(table[17], "#.......................................................#");
	strcpy_s(table[18], "#########################################################");
	// [ttt]
	table[1][1] = '[';
	if (nowTime > 99) {
		table[1][2] = (char)((int)(nowTime / 100) + 48);
		table[1][3] = (char)((int)((nowTime % 100) / 10) + 48);
		table[1][4] = (char)(nowTime % 10 + 48);
	}
	else if (nowTime > 9) {
		table[1][2] = '0';
		table[1][3] = (char)((int)(nowTime / 10) + 48);
		table[1][4] = (char)(nowTime % 10 + 48);
	}
	else {
		table[1][2] = '0';
		table[1][3] = '0';
		table[1][4] = (char)(nowTime + 48);
	}
	table[1][5] = ']';
	// [ttt][][][][]
	for (i = 0; i < 45 && i / 10 < kassa.getAmount(); i += 10) {
		if (kassa[i / 10].getType() == 0) continue;
		table[2][6 + i] = '[';
		if (kassa[i / 10].getUnique() > 99) {
			table[2][7 + i] = (char)((int)(kassa[i / 10].getUnique() / 100) + 48);
			table[2][8 + i] = (char)((int)((kassa[i / 10].getUnique() % 100) / 10) + 48);
			table[2][9 + i] = (char)(kassa[i / 10].getUnique() % 10 + 48);
		}
		else if (kassa[i / 10].getUnique() > 9) {
			table[2][7 + i] = '0';
			table[2][8 + i] = (char)((int)(kassa[i / 10].getUnique() / 10) + 48);
			table[2][9 + i] = (char)(kassa[i / 10].getUnique() % 10 + 48);
		}
		else {
			table[2][7 + i] = '0';
			table[2][8 + i] = '0';
			table[2][9 + i] = (char)(kassa[i / 10].getUnique() + 48);
		}
		table[2][10 + i] = ']';
	}
	// [ccc]
	for (i = 0; i < 45 && i / 10 < kassa.getAmount(); i += 10) {
		if (kassa[i / 10].getType() == 0) continue;
		table[4][6 + i] = '[';
		table[4][7 + i] = (char)kassa[i / 10].getType();
		if (kassa[i / 10].getNumber() > 9) {
			table[4][8 + i] = (char)((int)(kassa[i / 10].getNumber() / 10) + 48);
			table[4][9 + i] = (char)(kassa[i / 10].getNumber() % 10 + 48);
		}
		else {
			table[4][8 + i] = '0';
			table[4][9 + i] = (char)(kassa[i / 10].getNumber() + 48);
		}
		table[4][10 + i] = ']';
	}
	// [qqq]...
	for (i = 6, n = 0; i < 17 && n < queue.size(); i++, n++) {
		table[i][6] = '[';
		table[i][7] = (char)queue[n].getType();
		if (queue[n].getNumber() < 10) {
			table[i][8] = '0';
			table[i][9] = (char)(queue[n].getNumber() + 48);
		}
		else {
			table[i][8] = (char)((int)(queue[n].getNumber() / 10) + 48);
			table[i][9] = (char)(queue[n].getNumber() % 10 + 48);
		}
		table[i][10] = ']';
	}
	if (n < queue.size()) {
		table[16][11] = '[';
		table[16][12] = (char)queue[n].getType();
		if (queue[n].getNumber() < 10) {
			table[16][13] = '0';
			table[16][14] = (char)(queue[n].getNumber() + 48);
		}
		else {
			table[16][13] = (char)((int)(queue[n].getNumber() / 10) + 48);
			table[16][14] = (char)(queue[n].getNumber() % 10 + 48);
		}
		table[16][15] = ']';
		n++;
	}
	for (i = 16; i > 8 && n < queue.size(); i--, n++) {
		table[i][16] = '[';
		table[i][17] = (char)queue[n].getType();
		if (queue[n].getNumber() < 10) {
			table[i][18] = '0';
			table[i][19] = (char)(queue[n].getNumber() + 48);
		}
		else {
			table[i][18] = (char)((int)(queue[n].getNumber() / 10) + 48);
			table[i][19] = (char)(queue[n].getNumber() % 10 + 48);
		}
		table[i][20] = ']';
	}
	if (n < queue.size()) {
		table[9][21] = '[';
		table[9][22] = (char)queue[n].getType();
		if (queue[n].getNumber() < 10) {
			table[9][23] = '0';
			table[9][24] = (char)(queue[n].getNumber() + 48);
		}
		else {
			table[9][23] = (char)((int)(queue[n].getNumber() / 10) + 48);
			table[9][24] = (char)(queue[n].getNumber() % 10 + 48);
		}
		table[9][25] = ']';
		n++;
	}
	for (i = 9; i < 17 && n < queue.size(); i++, n++) {
		table[i][26] = '[';
		table[i][27] = (char)queue[n].getType();
		if (queue[n].getNumber() < 10) {
			table[i][28] = '0';
			table[i][29] = (char)(queue[n].getNumber() + 48);
		}
		else {
			table[i][28] = (char)((int)(queue[n].getNumber() / 10) + 48);
			table[i][29] = (char)(queue[n].getNumber() % 10 + 48);
		}
		table[i][30] = ']';
	}
	for (int i = 0; i < 19; i++) cout << table[i] << endl;
}