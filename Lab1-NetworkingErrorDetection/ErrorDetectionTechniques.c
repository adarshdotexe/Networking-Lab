#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int checkParity(unsigned char data) {
    unsigned char parity = 0;
    while (data) {
        parity ^= (data & 1);
        data >>= 1;
    }
    return parity;
}

void check2DParity(unsigned char data[][4],int row,int column) {
    int i,j;
    unsigned char row_parity = 0,col_parity = 0;

    // calculate parity of rows
    for (i = 0; i < row; i++) {
        row_parity = 0;
        for (j = 0; j < column; j++) {
            row_parity ^= data[i][j];
        }
        printf("Parity of row %d is %d\n", i+1, row_parity);
    }

    // calculate parity of columns
    for (i = 0; i < column; i++) {
        col_parity = 0;
        for (j = 0; j < row; j++) {
            col_parity ^= data[j][i];
        }
        printf("Parity of column %d is %d\n", i+1, col_parity);
    }
}

char* add(char* a, char* b, int n) {
    char* sum = (char *) malloc(sizeof(char) * n);
    int carry = 0;
    for (int i = n-1; i >= 0; i--) {
        sum[i] = (a[i] ^ b[i]) ^ carry;
        carry = (a[i] & b[i]) | (b[i] & carry) | (a[i] & carry);
    }
    return sum;
}


void checksum(unsigned char data[][4],int row,int column) {
    char* sum = (char *) malloc(sizeof(char) * column);
    for (int i = 0; i < column; i++) {
        sum[i] = data[0][i];
    }
    int i,j;
    for (i = 1; i < row; i++) {
        char* s = (char *) malloc(sizeof(char) * column);
        for (j = 0; j < column; j++) {
            if (data[i][j] == 0) {
                s[j] = 1;
            } else {
                s[j] = 0;
            }
        }
        sum = add(sum, s, column);
    }
    printf("Checksum is: ");
    // Take 1's Compliment after addition.
    for (i = 0; i < column; i++) {
        if (sum[i] == 0) {
            sum[i] = 1;
        } else {
            sum[i] = 0;
        }
        printf("%d", sum[i]);
    }
    printf("\n");
    int checksum = 0;
    for (i = 0; i < column; i++) {
        checksum += sum[i] * (1 << (column - i - 1));
    }
    printf("Checksum in decimal is: %d", checksum);

}


int main() {
    unsigned int data = 0b010110100101; // Example data
    printf("Data is: %d\n", data);
    printf("Data in binary is: ");
    for (int i = 0; i < 12; i++) {
        printf("%d", (data >> (11-i)) & 1);
    }
    printf("\n");

    printf("Parity of data is: %d\n", checkParity(data));

    unsigned char data2D[3][4] = {
        {0,1,0,1},
        {1,0,1,0},
        {0,1,0,1}
    };

    check2DParity(data2D, 3, 4);

    checksum(data2D, 3, 4);

    return 0;
}