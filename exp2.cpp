#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

char data[5];
int encoded[7] = {0}, edata[7], syndrome[3] = {0};
int hmatrix[3][7] = {
    {1, 1, 1, 0, 1, 0, 0},
    {1, 1, 0, 1, 0, 1, 0},
    {1, 0, 1, 1, 0, 0, 1}
};
char gmatrix[4][8] = {"1000111", "0100110", "0010101", "0001011"};

void main() {
    int i, j;

    clrscr();

    cout << "Hamming Code --- Encoding\n";

    cout << "Enter 4-bit data: ";
    cin >> data;

    cout << "Generator matrix:\n";
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 7; j++) {
            cout << gmatrix[i][j] << " ";
        }
        cout << endl;
    }

    // Encoding the data using the generator matrix
    cout<<"encoded data: \n";
    for (i = 0; i < 7; i++) {
        encoded[i] = 0;  // Initialize to 0 for each iteration
        for (j = 0; j < 4; j++) {
            encoded[i] += ((data[j] - '0') * (gmatrix[j][i] - '0'));
        }
        encoded[i] = encoded[i] % 2;
        cout << encoded[i] << " ";
    }
    cout << endl;

    cout << "\nHamming Code -- Decoding\n";
    cout << "Enter encoding bits as received: ";

    for (i = 0; i < 7; i++) {
        cin >> edata[i];
    }

    // Calculate syndrome
    for (i = 0; i < 3; i++) {
        syndrome[i] = 0;  // Initialize syndrome
        for (j = 0; j < 7; j++) {
            syndrome[i] += (edata[j] * hmatrix[i][j]);
        }
        syndrome[i] = syndrome[i] % 2;
    }

    // Find the position of the error (if any)
    int errorPosition = -1;
    for (j = 0; j < 7; j++) {
        if ((syndrome[0] == hmatrix[0][j]) &&
            (syndrome[1] == hmatrix[1][j]) &&
            (syndrome[2] == hmatrix[2][j])) {
            errorPosition = j;
            break;
        }
    }

    if (errorPosition == -1) {
        cout << "Data is error-free\n";
    } else {
        cout << "Error detected at bit number " << errorPosition + 1 << " of the data\n";
        edata[errorPosition] = !edata[errorPosition];  // Correct the error
        cout << "The correct data should be: ";
        for (i = 0; i < 7; i++) {
            cout << edata[i] << " ";
        }
        cout << endl;
    }

    getch();  // Wait for a key press before exiting
}