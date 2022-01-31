//merge sorting
#include <stdio.h> // for C
#include<windows.h> // for Russian language
#include <bits/stdc++.h> // C++ all libraries

void input_array(int *mas, int size){
    for(int i = 0; i < size; i++)
        std::cin >> mas[i];
}

void sort_array(int *mas, int size){
    if (size <= 1) return;
    else{
        int middle = size / 2;
        int left_point = middle;
        int right_point = size - middle;
        int *left = mas;
        int *right = mas + middle;

        sort_array(left,left_point);
        sort_array(right,right_point);

        int *buffer = new int[size];
        int left_i = 0;
        int right_i = 0;
        int buffer_i = 0;

        while(left_i < left_point && right_i < right_point){
            if (left[left_i] <= right[right_i]){
                buffer[buffer_i++] = left[left_i++];
            }else{
                buffer[buffer_i++] = right[right_i++];
            }
        }

        while(left_i < left_point){
            buffer[buffer_i++] = left[left_i++];
        }
        while(right_i < right_point){
            buffer[buffer_i++] = right[right_i++];
        }

        for (int i = 0; i < size; i++)
            mas[i] = buffer[i];

        delete[] buffer;
    }
}

void output_array(int *mas, int size){
    for(int i = 0; i < size; i++)
        std::cout << mas[i] << ' ';
}

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
    int n;
    std::cout << "Enter mas size: ";
    std::cin >> n;
    int *mas = new int[n];
    input_array(mas,n);
    sort_array(mas,n);
    output_array(mas,n);
    delete[] mas;
}