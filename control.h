#ifndef CONTROLL
#define CONTROLL

#include <iostream>
#include <stdio.h>
//#include <conio.h>
//#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include "collection.h"
#include "units.h"
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
    void check(UnitsCollection<QueueUnit>& queue, UnitsCollection<StatUnit>& stat, int &n, int &kass);
    void enter(int &kass, UnitsCollection<QueueUnit> &queue, UnitsCollection<StatUnit> &stat, int &n);
};

#endif CONTROLL