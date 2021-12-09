/*
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

void Control::check(UnitsCollection<QueueUnit>& queue, UnitsCollection<StatUnit>& stat, int& n, Kasses& kass)
{
	char C[70];
	UnitsCollection<QueueUnit> queue1;
	QueueUnit queueOne;
	StatUnit statOne;
	int ch, i, j, q, nc, timeoch, w;
	//timeoch - ����� ��������� ������� �������, nc - ���������� ��������� � ������� C, queue1 - ����� ������� �������
	cout << "������� ������� � �������: ABDABC" << endl;
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
		if ((65 <= (int)C[i]) && ((int)C[i] <= (69 - (5 - nType))))  //�������� ��������� �������
		{
			if (queue.size() >= 30) //������� ������������ ������� �� ���������� ������
			{ //������ � ����������
				n++;
				statOne.setNumber(n);
				statOne.setType((int)C[i]);
				statOne.setUnique(0);
				stat << statOne;
			}
			else //������ � �������
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
				if (timeoch > dayTime) //������� ������������ ������� �� ������� ��������� ������
				{
					//������ � ����������
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

	do
	{
		check(queue, stat, nstat, nqueue, n, *timework, *kass, time, *ntype);
	} while (queue.size() == 0); //the case when the user did not enter anything or entered the wrong characters

}
*/