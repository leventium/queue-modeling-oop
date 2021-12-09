#include "control.h"
#include "kasses.h"
#include "units.h"
#include "collection.h"
#include <string.h>

/*
K[0] - время до конца обслуживания
K[1] - тип заявки
K[2] - номер заявки
K[3] - время в очереди

queue[0] - тип заявки
queue[1] - номер заявки
queue[2] - время в очереди
*/

void Control::printQueue(const Kasses &kassa, const UnitsCollection<QueueUnit> &queue) const
{
	int i, n;
	char table[20][80];
	strcpy(table[0], "#########################################################");
	strcpy(table[1], "#.......................................................#");
	strcpy(table[2], "#.......................................................#");
	strcpy(table[3], "#.....KASSA.....KASSA.....KASSA.....KASSA.....KASSA.....#");
	strcpy(table[4], "#.....CLOSE.....CLOSE.....CLOSE.....CLOSE.....CLOSE.....#");
	strcpy(table[5], "#.......................................................#");
	strcpy(table[6], "#.......................................................#");
	strcpy(table[7], "#.......................................................#");
	strcpy(table[8], "#.......................................................#");
	strcpy(table[9], "#.......................................................#");
	strcpy(table[10], "#.......................................................#");
	strcpy(table[11], "#.......................................................#");
	strcpy(table[12], "#.......................................................#");
	strcpy(table[13], "#.......................................................#");
	strcpy(table[14], "#.......................................................#");
	strcpy(table[15], "#.......................................................#");
	strcpy(table[16], "#.......................................................#");
	strcpy(table[17], "#.......................................................#");
	strcpy(table[18], "#########################################################");
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