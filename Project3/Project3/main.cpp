#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "collection.cpp"
#include "control.h"
#include "kasses.h"
#include "units.h"

int main()
{
    setlocale(LC_ALL, "RUS");
    UnitsCollection<QueueUnit> queue;
    UnitsCollection<StatUnit> stat;
    Kasses kassa;
    Control screen;
    int n = 0, count = 0, flag = 1, repeats = 0, toEnd = 1, min, ch;

    screen.enter(kassa, queue, stat, n);
    for (int i = 0; i < kassa.getAmount(); ++i)
    {
        kassa[i] = queue[0];
        queue.del(0);
    }
    while (flag)
    {
        system("cls");
        screen.printQueue(kassa, queue);
        min = kassa[0].getUnique();
        for (int i = 1; i < kassa.getAmount(); ++i)
            if (kassa[i].getUnique() < min && kassa[i].getUnique() != 0)
                min = kassa[i].getUnique();
        for (int i = 0; i < min; ++i)
        {
            screen.setNowTime(screen.getNowTime() + 1);
            for (int j = 0; j < kassa.getAmount(); ++j)
                kassa[j].setUnique(kassa[j].getUnique() - 1);
            Sleep(1000);
            system("cls");
            screen.printQueue(kassa, queue);
        }
        screen.makeStat(queue, stat, kassa, count, flag, repeats);
        if (!toEnd && !(repeats % 5))
        {
            system("cls");
            screen.printQueue(kassa, queue);
            std::cout << "\n\n" << "What's next?" << "\n";
            min = 1;
            std::cout << "> Add to queue." << "\n" << "  Print the stats."
                << "\n" << "  To end without stops.";
            ch = _getch();
            while (ch != 13)
            {
                system("cls");
                screen.printQueue(kassa, queue);
                std::cout << "\n\n";
                if (ch == 72 && min > 1) min--;
                if (ch == 80 && min < 3) min++;
                std::cout << "What's next?" << "\n";
                switch (min)
                {
                    case 1:
                        cout << "> Add to queue." << "\n" << "  Print the stats."
                            << "\n" << "  To end without stops.";
                        break;
                    case 2:
                        cout << "  Add to queue." << "\n" << "> Print the stats."
                            << "\n" << "  To end without stops.";
                        break;
                    case 3:
                        cout << "  Add to queue." << "\n" << "  Print the stats."
                            << "\n" << "> To end without stops.";
                        break;
                }
                ch = _getch();
            }
            std::cout << "\n\n";
            switch (min)
            {
                case 1:
                    screen.check(queue, stat, n, kassa);
                    break;
                case 2:
                    screen.printStat(stat);
                    std::cout << "> Continue.";
                    ch = _getch();
                    while (ch != 13)
                        ch = _getch();
                    break;
                case 3:
                    toEnd = 1;
                    break;
            }
        }
    }
    system("cls");
    std::cout << "Spended time: " << count << "\n";
    screen.printStat(stat);
    std::cout << "> Continue.";
    ch = _getch();
    while (ch != 13)
        ch = _getch();
    return 0;
}