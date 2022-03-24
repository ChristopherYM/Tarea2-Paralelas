#include <iostream>
#include <chrono>
#include <time.h>
#include <stdlib.h>

using namespace std;

void classic(int** A, int** B, int** C, int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            C[i][j] = 0;
            for (k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}


void blocked(int** A, int** B, int** C, int n, int bsize) {
    int i, j, k, kk, jj;
    int sum;
    int en = bsize * (n / bsize);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            C[i][j] = 0.0;

    for (kk = 0; kk < en; kk += bsize) {
        for (jj = 0; jj < en; jj += bsize) {
            for (i = 0; i < n; i++) {
                for (j = jj; j < jj + bsize; j++) {
                    sum = C[i][j];
                    for (k = kk; k < kk + bsize; k++) {
                        sum += A[i][k] * B[k][j];
                    }
                    C[i][j] = sum;
                }
            }
        }
    }
}


void Ini(int**& A, int**& B, int**& C, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            int va = (int)rand() / (int)RAND_MAX;
            int vb = (int)rand() / (int)RAND_MAX;
            A[row][col] = va;
            B[row][col] = vb;
        }
    }
}


int main()
{
    int size = 5000;
    int** A = new int* [size];
    int** B = new int* [size];
    int** C = new int* [size];
    for (int i = 0; i < size; ++i) {
        A[i] = new int[size];
        B[i] = new int[size];
        C[i] = new int[size];
    }

    Ini(A, B, C, size);

    //Prueba con implementacion clasica
    auto started = chrono::high_resolution_clock::now();
    classic(A, B, C, size);
    auto done = chrono::high_resolution_clock::now();
    cout << "Implementacion clasica (ms): " << chrono::duration_cast<chrono::milliseconds>(done - started).count() << endl;

    //Pueba con implementacion por bloques
    started = chrono::high_resolution_clock::now();
    blocked(A, B, C, size, 50);
    done = chrono::high_resolution_clock::now();
    cout << "Implementacion bloques (ms): " << chrono::duration_cast<chrono::milliseconds>(done - started).count() << endl;

    for (int i = 0; i < size; ++i) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }

    delete[] A;
    delete[] B;
    delete[] C;
}