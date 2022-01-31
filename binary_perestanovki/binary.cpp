#include <stdio.h>
#include<windows.h>
#include <bits/stdc++.h>

using namespace std;

const int MAX_BINARY_DIGITS_TO_GENERATE = 100;

void generate_binary_numbers(int digits_left_to_generate)
{
    static int digits_combination[MAX_BINARY_DIGITS_TO_GENERATE];
    static int top = 0;

    if (digits_left_to_generate == 0) {  // base case
        for(int i = 0; i < top; i++)
            cout << digits_combination[i];
        cout << '\n';
    } else {  // recursive case
        digits_combination[top++] = 1;
        generate_binary_numbers(digits_left_to_generate - 1);
        top--;

        digits_combination[top++] = 0;
        generate_binary_numbers(digits_left_to_generate - 1);
        top--;
    }

}

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
    int n;
    cin >> n;
    generate_binary_numbers(n);
}

/*
 * n = 4
 *                       start
                  1                  0
              1        0         1       0
           1    0    1   0     1   0   1   0
          1 0  1 0  1 0 1 0   1 0 1 0 1 0 1 0
 */