#include "control.h"

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

void Control::check(UnitsCollection<QueueUnit>& queue, UnitsCollection<StatUnit>& stat, int& n, int& kass)
{

}


void Control::enter(int& kass, UnitsCollection<QueueUnit>& queue, UnitsCollection<StatUnit>& stat, int& n)
{
	int i;
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
		kass = read();
	} while ((kass > 5));

	do
	{
		check(queue, stat, nstat, nqueue, n, *timework, *kass, time, *ntype);
	} while (queue.size == 0); //the case when the user did not enter anything or entered the wrong characters

}
