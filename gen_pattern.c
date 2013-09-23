/* 
 * Created on September 4, 2013, 9:53 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "math.h"

 //======Declarations
long int dectobin(long int decimalNumber);
long int bintodec(long int binaryNumber);
int mutation(int prev, int now, int next, int rule[8]);

int main(int argc, char** argv) {
    int max_nodes  = atoi(argv[1]);
    int box[max_nodes][max_nodes * 2]; // capacity matrix
    int col, row, a;
    int i = 0, j = 1;
    int rulenumber;
    int rule[8];
    long int binaryRule;
    
    // init Box
    for (row = 0; row < max_nodes; row++) {    
        for (col = 0; col < max_nodes * 2; col++) {  
            box[row][col] = 0;
        }
    }
    
    box[0][(max_nodes * 2 - 1) / 2] = 1;

    // init filter
    for (a = 0; a < 8; a++) {
        rule[a] = 0;
    }

    rulenumber = atoi(argv[2]);
    binaryRule = dectobin(rulenumber);

    //generate array of ruler from binaryrule
    while (binaryRule != 0) {
        j = j * 10;
        rule[i] = binaryRule % j;
        binaryRule = binaryRule - rule[i];
        rule[i] = rule[i] * 10 /j;
        i = i + 1;
    }

    //select new cell based on the rule with 3 arguments, right neighbor box, left neighbor box and the box it self
    for (row = 1; row < max_nodes; row++) {    
        for (col = 1; col < max_nodes * 2 - 1; col++) {
            box[row][col]  = mutation(box[row -  1][col -  1], box[row -  1][col], box[row -  1][col +  1], rule);
        }
    }

    // print the result
    // if box.value = 1 print o, otherwise print " "
    for (row = 0; row < max_nodes; row++) {    
        for (col = 0; col < max_nodes * 2; col++) {  
            if (box[row][col] == 1) printf("%s", "o");
            else printf(" ");
        }
        printf("\n");
    }
    return (EXIT_SUCCESS);
}


long int dectobin(long int decimalNumber) {
    long int binaryNumber =0 , quotient, j = 1;

    quotient = decimalNumber;

    while (quotient != 0){
        binaryNumber += (quotient % 2) * j;
        j = j * 10;
        quotient = quotient / 2;
    }

    return binaryNumber;
}

// unused function :p
long int bintodec(long int binaryNumber) {
    long int decimalNumber=0, j=1, remainder;

    while (binaryNumber != 0) {
        remainder = binaryNumber % 10;
        decimalNumber = decimalNumber + remainder * j;
        j = j * 2;
        binaryNumber=binaryNumber / 10;
    }

    return decimalNumber;
}

// mapping rule
int mutation(int prev, int now, int next, int rule[8]) {
    int binaryNumber;
    binaryNumber = 4 * prev + 2 * now + 1 * next;
    //printf("%d\n", binaryNumber);
    return rule[binaryNumber];
}
