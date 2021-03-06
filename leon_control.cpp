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

void Control::printQueue(Kasses &kassa, const UnitsCollection<QueueUnit> &queue) const
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