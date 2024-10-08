#include <stdio.h>
#define DEGREE 16

int mod2add(int, int);
int getnext(int array[], int pos);
int result[30];

void calc_crc(int length) {
    int ccit[] = {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    int i = 0, pos = 0, newpos;

    while (pos < length - DEGREE) {
        for (i = pos; i < pos + DEGREE + 1; ++i)
            result[i] = mod2add(result[i], ccit[i - pos]);
        newpos = getnext(result, pos);

        if (newpos > pos + 1)
            pos = newpos - 1;

        ++pos;
    }
}

int getnext(int array[], int pos) {
    int i = pos;
    while (array[i] == 0 && i < 30)
        ++i;
    return i;
}

int mod2add(int x, int y) {
    return (x == y ? 0 : 1);
}

int main() {
    int array[30], ch;
    int length, i = 0;

    printf("Enter the data stream: ");

    // Read input from the user until newline ('\n') is pressed
    while ((ch = getchar()) != '\n' && i < 30) {
        if (ch == '0' || ch == '1') {
            array[i++] = ch - '0';
        }
    }

    length = i;

    // Append DEGREE zeros to the array
    for (i = 0; i < DEGREE; ++i)
        array[i + length] = 0;
    length += DEGREE;

    for (i = 0; i < length; i++)
        result[i] = array[i];

    calc_crc(length);

    printf("\nThe transmitted frame is: ");
    for (i = 0; i < length - DEGREE; ++i)
        printf("%d", array[i]);
    for (i = length - DEGREE; i < length; ++i)
        printf("%d", result[i]);

    printf("\nEnter the stream for which CRC is to be checked: ");
    i = 0;

    // Read another stream for CRC checking
    while ((ch = getchar()) != '\n' && i < 30) {
        if (ch == '0' || ch == '1') {
            array[i++] = ch - '0';
        }
    }

    length = i;

    for (i = 0; i < length; i++)
        result[i] = array[i];

    calc_crc(length);

    printf("\nChecksum: ");
    for (i = length - DEGREE; i < length; ++i)
        printf("%d", result[i]);

    return 0;
}
