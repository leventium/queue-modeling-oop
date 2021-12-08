#include "control.h"

int Control::read(void)
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

void Control::check(UnitsCollection<QueueUnit>& queue, UnitsCollection<StatUnit>& stat, int& n, int& kass)
{

}


void Control::enter(int& kass, UnitsCollection<QueueUnit>& queue, UnitsCollection<StatUnit>& stat, int& n)
{
	int i;
	{
		cout << "¬ведите количество типов за€вок(максимально 5)";
		nType = read();
	} while ((nType > 5));

	for (i = 0; i < nType; i++)
	{
		do
		{
			cout << "¬ведите дл€ " << (char)(65 + i) << " типа врем€ обработки за€вки (в секундах от 1 до 30)";
			times[i] = read();
		} while ((times[i] > 30));
	}

	do
	{
		cout << "¬ведите длительность рабочего дн€ в секундах(в секундах от 30 до 300)";
		dayTime = read();
	} while ((dayTime < 30) || (dayTime > 300));

	do
	{
		cout << "¬ведите количество касс(максимально 5)";
		kass = read();
	} while ((kass > 5));

	do
	{
		check(queue, stat, nstat, nqueue, n, *timework, *kass, time, *ntype);
	} while (queue.size == 0); //случай, когда пользователь ничего не ввел или ввел не те символы

}
