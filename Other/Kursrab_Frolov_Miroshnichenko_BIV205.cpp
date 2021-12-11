#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

#define CLR while (getchar()!='\n')

int read(void); //проверка правильности ввода целого положительного числа

int delch(int* nqueue, int queue[][30]); // nqueue - кол-во заявок в очереди, queue[] - элементы очереди (строка)
									  // задача функции удалить первый элемент в строке и вернуть его

int tet(int* times, int type); // times[] - время обслуживания каждого типа, type - символ для поиска
								// задача функции получить тип заявки и вернуть время, необходимое на обработку этой заявки

int QueueCount(int kass, int* times, int nqueue, int queue[][30]);
// kass - кол-во касс, times[] - время обслуживания каждого типа, nqueue - кол-во заявок в очереди, queue[] - очередь (строка)
// задача функции подсчитать время, необходимое на обслуживание всей очереди, по технологии эл. очереди

void check(int queue[][30], int stat[][70], int* nstat, int* nqueue, int* n, int timework, int kass, int* time, int ntype); //добавление в очередь
void enter(int* kass, int queue[][30], int* nqueue, int* time, int* ntype, int stat[][70], int* nstat, int* timework, int* n); //ввод первоначальных данных
void makeStat(int kasses, int* times, int* nqueue, int queue[][30], int* nstat, int stat[][70], int K[][5], int* count, int* flag, int* d);
void printQueue(int nq, int queue[][30], int K[][5], int time, int kass, int* timers);
void printStat(int stat[][70], int nstat);

int main() {
	setlocale(LC_ALL, "RUS");
	int nqueue = 0, nstat = 0, n = 0, queue[3][30], stat[4][70], ntype, kass, times[5], timework, d = 0;
	int K[4][5], flag = 1, count = 0, min, nowtime = 0, toend = 0, ch, timers[5];
	/* queue - матрица очереди заявок
	nqueue - количество заявок в очереди
	stat - матрица с заявками, полившими статус(обработана или нет)
	nstat - количество заявок, получивших статус(обработана или нет)
	ntype - количество типов заявок
	times - массив со временем обработки каждой заявки
	kass - количество касс
	timework - время рабочего дня
	n - общее число введенных заявок */
	enter(&kass, queue, &nqueue, times, &ntype, stat, &nstat, &timework, &n);
	for (int i = 0; i < nqueue; i++) {
		queue[2][i] = 0;
	}
	for (int i = 0; i < 5; i++) {
		K[0][i] = 0;
		K[1][i] = 0;
		timers[i] = 0;
	}
	for (int i = 0; i < kass; i++) {
		K[3][i] = queue[2][0];
		K[2][i] = queue[1][0];
		K[1][i] = queue[0][0];
		K[0][i] = tet(times, delch(&nqueue, queue));
		timers[i] = K[0][i];
	}
	while (flag) {
		system("cls");
		printQueue(nqueue, queue, K, nowtime, kass, timers);
		min = timers[0];
		for (int i = 1; i < kass; i++) if (timers[i] < min && timers[i] != 0) min = timers[i];
		for (int i = 0; i < min; i++) {
			nowtime++;
			for (int j = 0; j < kass; j++) timers[j]--;
			Sleep(1000);
			system("cls");
			printQueue(nqueue, queue, K, nowtime, kass, timers);
		}
		makeStat(kass, times, &nqueue, queue, &nstat, stat, K, &count, &flag, &d);
		for (int i = 0; i < kass; i++) timers[i] = K[0][i];
		if (!toend && !(d % 5)) {
			system("cls");
			printQueue(nqueue, queue, K, nowtime, kass, timers);
			cout << endl << endl;
			cout << "Что дальше:" << endl;
			min = 1;
			cout << "> Добавить в очередь." << endl << "  Вывести статистику." << endl << "  До конца без остановок.";
			ch = _getch();
			while (ch != 13) {
				system("cls");
				printQueue(nqueue, queue, K, nowtime, kass, timers);
				cout << endl << endl;
				if (ch == 72 && min > 1) min--;
				if (ch == 80 && min < 3) min++;
				cout << "Что дальше:" << endl;
				if (min == 1) cout << "> Добавить в очередь." << endl << "  Вывести статистику." << endl << "  До конца без остановок.";
				if (min == 2) cout << "  Добавить в очередь." << endl << "> Вывести статистику." << endl << "  До конца без остановок.";
				if (min == 3) cout << "  Добавить в очередь." << endl << "  Вывести статистику." << endl << "> До конца без остановок.";
				ch = _getch();
			}
			cout << endl << endl;
			if (min == 1) {
				check(queue, stat, &nstat, &nqueue, &n, timework - nowtime, kass, times, ntype);
			}
			if (min == 2) {
				printStat(stat, nstat);
				cout << "> Continue.";
				ch = _getch();
				while (ch != 13) ch = _getch();
			}
			if (min == 3) {
				toend = 1;
			}
		}
	}
	system("cls");
	cout << "Всего времени прошло: " << count << endl;
	printStat(stat, nstat);
	return 0;
}

int read(void)
{
	char str[80];
	int n, k, f = 0;
	do
	{
		cout << " (введите целое положительное число) " << endl;
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

int delch(int* nqueue, int queue[][30]) {
	int ch;
	if (*nqueue != 0) {
		ch = queue[0][0];
		for (int i = 1; i < *nqueue; i++) {
			queue[0][i - 1] = queue[0][i];
			queue[1][i - 1] = queue[1][i];
		}
		(*nqueue)--;
	}
	else {
		ch = 100;
	}
	return ch;
}

int tet(int* times, int type) {
	if (type == (int)'A') return times[0];
	if (type == (int)'B') return times[1];
	if (type == (int)'C') return times[2];
	if (type == (int)'D') return times[3];
	if (type == (int)'E') return times[4];
	else return 0;
}

int QueueCount(int kass, int* times, int nqueue, int queue[][30]) {
	int K[5], min, count; // K[] - оставшееся время на кажой кассе, min - минимум, count - суммарное время обслуживания
	count = 0;
	for (int i = 0; i < kass; i++) K[i] = tet(times, delch(&nqueue, queue));
	while (nqueue > 0) {
		min = K[0];
		for (int i = 1; i < kass; i++)
			if (K[i] < min) min = K[i];
		for (int i = 0; i < kass; i++) {
			if (K[i] == min)
				K[i] = tet(times, delch(&nqueue, queue));
			else
				K[i] -= min;
		}
		count += min;
	}
	min = 0;
	for (int i = 0; i < kass; i++)
		if (K[i] > min) min = K[i];
	count += min;
	return count;
}

void check(int queue[][30], int stat[][70], int* nstat, int* nqueue, int* n, int timework, int kass, int* time, int ntype) //Дополнение к текущей очереди новых заявок
{
	char C[70];
	int ch, i, j, q, nc, timeoch, queue1[2][30], nqueue1 = 0, w;
	//timeoch - время обработки текущей очереди, nc - количество элементов в массиве C, queue1 - копия матрицы очереди
	cout << "Введите очередь в формате: ABDABC" << endl;
	j = *n;
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
		if ((65 <= (int)C[i]) && ((int)C[i] <= (69 - (5 - ntype))))  //проверка вводимого символа
		{
			if (*nqueue >= 30) //условие переполнения очереди по количеству заявок
			{ //запись в статистику
				(*n)++;
				stat[0][*nstat] = (int)C[i];
				stat[1][*nstat] = *n;
				stat[2][*nstat] = 0;
				(*nstat)++;
			}
			else //запись в очередь
			{
				(*n)++;
				queue[0][*nqueue] = (int)C[i];
				queue[1][*nqueue] = *n;
				for (w = 0; w <= *nqueue; w++)
				{
					queue1[0][w] = queue[0][w];
					queue1[1][w] = queue[1][w];
				}
				(*nqueue)++;
				nqueue1 = *nqueue;
				timeoch = QueueCount(kass, time, nqueue1, queue1);
				//cout << timeoch << endl;
				if (timeoch > timework) //условие переполнения очереди по времени обработки заявок
				{
					//запись в статистику
					(*nqueue)--;
					stat[0][*nstat] = (int)C[i];
					stat[1][*nstat] = *n;
					stat[2][*nstat] = 0;
					(*nstat)++;
				}

			}
		}
	}
}

void enter(int* kass, int queue[][30], int* nqueue, int* time, int* ntype, int stat[][70], int* nstat, int* timework, int* n) //надежный ввод входных данных и оставление очереди
{
	int i;
	do
	{
		cout << "Введите количество типов заявок(максимально 5)";
		*ntype = read();
	} while ((*ntype > 5));

	for (i = 0; i < *ntype; i++)
	{
		do
		{
			cout << "Введите для " << (char)(65 + i) << " типа время обработки заявки (в секундах от 1 до 30)";
			time[i] = read();
		} while ((time[i] > 30));
	}

	do
	{
		cout << "Введите длительность рабочего дня в секундах(в секундах от 30 до 300)";
		*timework = read();
	} while ((*timework < 30) || (*timework > 300));

	do
	{
		cout << "Введите количество касс(максимально 5)";
		*kass = read();
	} while ((*kass > 5));

	do
	{
		check(queue, stat, nstat, nqueue, n, *timework, *kass, time, *ntype);
	} while (*nqueue == 0); //случай, когда пользователь ничего не ввел или ввел не те символы

}

//	// 1ая строка - время до конца обслуживания, 2ая - тип заявки, 3я - номер заявки
//	int K[3][5], flag = 1, count = 0;
//	K[1][0] = 0;
//	K[1][1] = 0;
//	K[1][2] = 0;
//	K[1][3] = 0;
//	K[1][4] = 0;
//	for (int i = 0; i < kasses; i++) {
//		K[2][i] = queue[1][0];
//		K[1][i] = queue[0][0];
//		K[0][i] = tet(times, delch(nqueue, queue));
//	}

void makeStat(int kasses, int* times, int* nqueue, int queue[][30], int* nstat, int stat[][70], int K[][5], int* count, int* flag, int* d) {
	int min, fl = 0;
	if (*nqueue > 0) {
		min = K[0][0];
		for (int i = 1; i < kasses; i++)
			if (K[0][i] < min) min = K[0][i];
		for (int i = 0; i < *nqueue; i++) {
			queue[2][i] += min;
		}
		for (int i = 0; i < kasses; i++) {
			if (K[0][i] == min) {
				if (*nqueue != 0) {
					if (K[1][i] != 0) {
						stat[0][*nstat] = K[1][i];
						stat[1][*nstat] = K[2][i];
						stat[2][*nstat] = 1;
						stat[3][*nstat] = K[3][i] + min;
						(*nstat)++;
						(*d)++;
						K[3][i] = queue[2][0];
						K[2][i] = queue[1][0];
						K[1][i] = queue[0][0];
						K[0][i] = tet(times, delch(nqueue, queue));
					}
				}
				else {
					if (K[1][i] != 0) {
						stat[0][*nstat] = K[1][i];
						stat[1][*nstat] = K[2][i];
						stat[2][*nstat] = 1;
						stat[3][*nstat] = K[3][i] + min;
						(*nstat)++;
						(*d)++;
						K[0][i] = 0;
						K[1][i] = 0;
						K[2][i] = 0;
						K[3][i] = 0;
					}
				}
			}
			else {
				if (K[0][i] != 0) {
					K[0][i] -= min;
					K[3][i] += min;
				}
			}
		}
		*count += min;
	}
	else {
		min = 1000;
		for (int i = 0; i < kasses; i++)
			if (K[0][i] < min && K[1][i] != 0) min = K[0][i];
		for (int i = 0; i < kasses; i++) {
			if (K[0][i] == min && K[1][i] != 0) {
				stat[0][*nstat] = K[1][i];
				stat[1][*nstat] = K[2][i];
				stat[2][*nstat] = 1;
				stat[3][*nstat] = K[3][i] + min;
				(*nstat)++;
				(*d)++;
				K[0][i] = 0;
				K[1][i] = 0;
			}
			else {
				if (K[0][i] != 0) {
					K[0][i] -= min;
					K[3][i] += min;
				}
			}
		}
		*count += min;
		if (K[1][0] <= 0 && K[1][1] <= 0 && K[1][2] <= 0 && K[1][3] <= 0 && K[1][4] <= 0) *flag = 0;
	}
}

void printQueue(int nq, int queue[][30], int K[][5], int time, int kass, int* timers) {
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
	if (time > 99) {
		table[1][2] = (char)((int)(time / 100) + 48);
		table[1][3] = (char)((int)((time % 100) / 10) + 48);
		table[1][4] = (char)(time % 10 + 48);
	}
	else if (time > 9) {
		table[1][2] = '0';
		table[1][3] = (char)((int)(time / 10) + 48);
		table[1][4] = (char)(time % 10 + 48);
	}
	else {
		table[1][2] = '0';
		table[1][3] = '0';
		table[1][4] = (char)(time + 48);
	}
	table[1][5] = ']';
	// [ttt][][][][]
	for (i = 0; i < 45 && i / 10 < kass; i += 10) {
		if (K[1][i / 10] == 0) continue;
		table[2][6 + i] = '[';
		if (timers[i / 10] > 99) {
			table[2][7 + i] = (char)((int)(timers[i / 10] / 100) + 48);
			table[2][8 + i] = (char)((int)((timers[i / 10] % 100) / 10) + 48);
			table[2][9 + i] = (char)(timers[i / 10] % 10 + 48);
		}
		else if (timers[i / 10] > 9) {
			table[2][7 + i] = '0';
			table[2][8 + i] = (char)((int)(timers[i / 10] / 10) + 48);
			table[2][9 + i] = (char)(timers[i / 10] % 10 + 48);
		}
		else {
			table[2][7 + i] = '0';
			table[2][8 + i] = '0';
			table[2][9 + i] = (char)(timers[i / 10] + 48);
		}
		table[2][10 + i] = ']';
	}
	// [ccc]
	for (i = 0; i < 45 && i / 10 < kass; i += 10) {
		if (K[1][i / 10] == 0) continue;
		table[4][6 + i] = '[';
		table[4][7 + i] = (char)K[1][i / 10];
		if (K[2][i / 10] > 9) {
			table[4][8 + i] = (char)((int)(K[2][i / 10] / 10) + 48);
			table[4][9 + i] = (char)(K[2][i / 10] % 10 + 48);
		}
		else {
			table[4][8 + i] = '0';
			table[4][9 + i] = (char)(K[2][i / 10] + 48);
		}
		table[4][10 + i] = ']';
	}
	// [qqq]...
	for (i = 6, n = 0; i < 17 && n < nq; i++, n++) {
		table[i][6] = '[';
		table[i][7] = (char)queue[0][n];
		if (queue[1][n] < 10) {
			table[i][8] = '0';
			table[i][9] = (char)(queue[1][n] + 48);
		}
		else {
			table[i][8] = (char)((int)(queue[1][n] / 10) + 48);
			table[i][9] = (char)(queue[1][n] % 10 + 48);
		}
		table[i][10] = ']';
	}
	if (n < nq) {
		table[16][11] = '[';
		table[16][12] = (char)queue[0][n];
		if (queue[1][n] < 10) {
			table[16][13] = '0';
			table[16][14] = (char)(queue[1][n] + 48);
		}
		else {
			table[16][13] = (char)((int)(queue[1][n] / 10) + 48);
			table[16][14] = (char)(queue[1][n] % 10 + 48);
		}
		table[16][15] = ']';
		n++;
	}
	for (i = 16; i > 8 && n < nq; i--, n++) {
		table[i][16] = '[';
		table[i][17] = (char)queue[0][n];
		if (queue[1][n] < 10) {
			table[i][18] = '0';
			table[i][19] = (char)(queue[1][n] + 48);
		}
		else {
			table[i][18] = (char)((int)(queue[1][n] / 10) + 48);
			table[i][19] = (char)(queue[1][n] % 10 + 48);
		}
		table[i][20] = ']';
	}
	if (n < nq) {
		table[9][21] = '[';
		table[9][22] = (char)queue[0][n];
		if (queue[1][n] < 10) {
			table[9][23] = '0';
			table[9][24] = (char)(queue[1][n] + 48);
		}
		else {
			table[9][23] = (char)((int)(queue[1][n] / 10) + 48);
			table[9][24] = (char)(queue[1][n] % 10 + 48);
		}
		table[9][25] = ']';
		n++;
	}
	for (i = 9; i < 17 && n < nq; i++, n++) {
		table[i][26] = '[';
		table[i][27] = (char)queue[0][n];
		if (queue[1][n] < 10) {
			table[i][28] = '0';
			table[i][29] = (char)(queue[1][n] + 48);
		}
		else {
			table[i][28] = (char)((int)(queue[1][n] / 10) + 48);
			table[i][29] = (char)(queue[1][n] % 10 + 48);
		}
		table[i][30] = ']';
	}
	for (int i = 0; i < 19; i++) cout << table[i] << endl;
}

void printStat(int stat[][70], int nstat) {
	int sred[5], max[5], n[5];
	for (int i = 0; i < nstat; i++) {
		cout << (char)stat[0][i] << "[" << stat[1][i] << "] - ";
		if (stat[2][i]) {
			cout << "одобрено [" << stat[3][i] << "];";
		}
		else {
			cout << "отказано;";
		}
		cout << endl;
	}
	for (int i = 0; i < 5; i++) {
		sred[i] = 0;
		max[i] = 0;
		n[i] = 0;
	}
	for (int i = 0; i < nstat; i++) {
		if (stat[2][i]) {
			if (stat[3][i] > max[stat[0][i] - (int)'A']) max[stat[0][i] - (int)'A'] = stat[3][i];
			sred[stat[0][i] - (int)'A'] += stat[3][i];
			n[stat[0][i] - (int)'A']++;
		}
	}
	cout << endl;
	for (int i = 0; i < 5; i++) {
		if (n[i]) {
			sred[i] = sred[i] / n[i];
			cout << (char)((int)'A' + i) << ": Среднее - " << sred[i] << "  Максимальное - " << max[i] << endl;
		}
	}
}