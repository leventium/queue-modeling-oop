#ifndef CONTROLL
#define CONTROLL

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

    int read();
    void check();
    void enter();
};

#endif CONTROLL