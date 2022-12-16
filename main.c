#include <stdio.h>
#include <math.h>

/*
 * Ths program will calculate the n-th root of a number. The number and the root to be computed is entered by the user.
 * The program will utilize the sliding-digit algorithm to compute the root.
 *
 */

int main() {

//Declaring variables
    int A = 0;                                  //number to take root of
    int n = 0;                                  //which root to calculate
    int k = 0;                                  //number of decimal places (precision)
    int y;                                      //x times 10^k
    int alpha = 0;
    int beta = 0;
    int num = 0;
    int digits = 0;                             //number of digits in A
    int groups = 0;                             //how many n-digit groups in A
    int iterations = 0;                         //number of digits in solution/number of iterations for algorithm
    int exponent = 0;                           //exponent for determining what power of 10 to use to find alpha
    int div = 0;                                //used to find alpha
    int originalA;                              //used to save for the value of A for future use

    double x;                                   //estimated n-th root, with k decimal places
    double r = 0;
    double u = 0;
    double comparisonRoot = 0;                  //shows how closely the estimated root matches the actual root

//Prompting user for number A, root n, and number of decimal digits (precision) k
    printf("Number: ");

    scanf("%d", &A);

    originalA = A;                                  //save A (used again for comparing estimated root to actual root)

    printf("Root: ");

    scanf("%d", &n);

    printf("Digits: ");

    scanf("%d", &k);

//Printing restatement of the problem, then an empty line
    printf("Compute root %d of %d to %d digits.\n", n, A, k);

    printf("\n");

//Compute number of n-digit groups, then print the number of n-digit groups that are in the integer
    num = A;

    while (num > 0) {                           //computing number of digits in the number

        digits++;                               //increment digits counter

        num /= 10;                              //"chopping off" last digit of number
    }


    if (digits == 1) {                          //computing number of groups
        groups = 1;
    }
    else if (digits % n) {
        groups = (digits / n) + 1;
    }
    else {
        groups = digits / n;
    }

    printf("Number has %d groups of %d digits.\n", groups, n);

    printf("\n");

//Algorithm
   y = 0;                                       //initialize y and r to 0

   r = 0;

    for (iterations = groups + k; iterations > 0; iterations--) {
    //number of iterations is equal to number of groups + decimal places

//Calculating Alpha, then print alpha
        exponent = (groups * n) - n;

        if (exponent <= 0) {                     //10^0 = 1
            num = 1;
        }
        else {
            num = 1;
            while (exponent > 0) {               //loop for calculating power of ten for use with / and %
                num *= 10;
                --exponent;
            }
        }

        div = A / num;                            //first use division to get upper digits

        alpha = div;                              //alpha = upper digits

        groups--;                                 /* subtract 1 from total groups, as upper digit(s) are first group;
                                                  groups has changed, so power of ten will change in next iteration */
        A = A % num;                              /* use modulo to get lower digits, which is our new number to divide
                                                  from */
        printf("alpha = %d, ", alpha);

//Calculating u ("Upper Limit")

    u = (pow(10,n) * r) + alpha;

//Calculating beta, then print beta
        beta = 0;
         while ((beta >= 0) && (beta <= 9) && (((pow((10 * y + beta), n)) - (pow(10 * y, n))) <= u)) {
                 beta++;
             }
         beta -= 1;

    printf("beta = %d", beta);
    printf("\n");

//Calculating r

    r = u - ((pow(((10 * y) + beta),n)) - (pow((10 * y), n)));


//Calculating y

    y = (10 * y) + beta;

//Print values of y and r

    printf("y = %d, ", y);
    printf("r = %.0f", r);
    printf("\n");
    }

//Print empty line
    printf("\n");

//Calculate estimated root and print
    x = y / (pow(10, k));                         //x (estimated root) = y / 10^k

    printf("Estimated root = %f\n", x);

//Calculate how closely the estimated root matches the actual root and print
    comparisonRoot = pow(x,n);                    //x^n will show how close we are to the original number (A)

    printf("Check: %f to the %d = %f (orig = %d)\n", x, n, comparisonRoot, originalA);

    return 0;
}
