#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

using std::cin;
using std::cout;
using std::endl;

void init_array(int** a, int* size);

void output_array(const int a[], int size);

void sumneg(const int a[], int size);

void countingzeros(int zerocnt);

int main() {
    int* a;
    int size;
    init_array(&a, &size);
        output_array(a, size);

    sumneg(a, size);

    int zerocnt{};
    for (int i = 0; i < size; i++)
        if (a[i] == 0) zerocnt++;
    countingzeros(zerocnt);

    delete[] a;

    return 0;
}

void init_array(int** a, int* size) {
    std::mt19937 rnd;
    rnd.seed(std::time(nullptr));
    *size = abs(static_cast<int>(rnd())) % 21 + 10;
    *a = new int[*size];
    cout << "Array size: " << *size << endl;
    for (int i = 0; i < *size; i++) {
        (*a)[i] = abs(static_cast<int>(rnd())) % (*size / 2 * 2) - (*size / 2) + 1;
    }
}

void output_array(const int a[], int size) {
    cout << "Array: ";
    for (int i = 0; i < size; i++) (i == size - 1) ? cout << a[i] << endl : cout << a[i] << ' ';
}

void sumneg(const int a[], int size) {
    int smn = 0;
    for (int i = 0; i < size; i++)
        if (a[i] < 0) smn += a[i];
    cout << "Sum of negative elements: " << smn << endl;
}

void countingzeros(int zerocnt) { cout << "Amount of zeros: " << zerocnt << endl; }
