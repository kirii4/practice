#include <stdio.h> // for C
#include<windows.h> // for Russian language
#include <bits/stdc++.h> // C++ all libraries

using namespace std;

void hanoi(int f, int s, int num) {
    if (num == 1) {
        cout << endl << "Перемещаем 1 диск с " << f << " столба на " << s;
        printf(". (%d,%d,%d)\n", f, s, num);
    } else {
        hanoi(f, 6 - f - s, num - 1);
        cout << "Перемещаем " << num << " диск с " << f << " столба на " << s;
        printf(". (%d,%d,%d)\n", f, s, num);
        hanoi(6 - f - s, s, num - 1);
    }
}

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
    hanoi(1,2,3);
}

//f s n
//1 2 3
//
//1 3 2
//1 2 1 -- 1: '1'->'2'
//1 3 2 -- 2: '1'->'3'
//
//1 2 3 -- 3: '1'->'2'
//
//обратно
//
//3 2 2
//3 1 1 -- 1: '3'->'1'
//3 2 2 -- 2: '3'->'2'
//
//1 2 1 -- 1: '1'->'2'