/*
    Name: Kareem Youssry
    ID: 1900382
*/

#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void poly_div(float *x, float *y, float *z, int num_deg, int denom_deg);
void print_poly(float *x, int degree, float *denominator, int denom_deg);

char rem_flag = 0; // flag that is set when print_poly is used to print the remainder

int main(void)
{
    // Variables to hold the numerator and denominator degrees
    int num_deg, denom_deg;
    char retry, first_time_flag = 0; // flags used in the program

    // Do while loop if the user wants to try different polynomial divisions
    do
    {
        // Prompts for the user to enter the numerator and denominator degrees
        printf("Enter the degree of the numerator polynomial: ");
        scanf("%d", &num_deg);

        printf("Enter the degree of the denominator polynomial: ");
        scanf("%d", &denom_deg);
        printf("\n");

        // Adds 1 to each degree to allocate enough memory for each polynomial
        num_deg++; denom_deg++;

        // result_deg is the degree of the polynomial resulting from the division
        int result_deg = num_deg - denom_deg;

        // Allocates memory for each polynomial according to the inputed degrees
        float *numerator = (float*) malloc(sizeof(float) * num_deg);
        float *denominator = (float*) malloc(sizeof(float) * denom_deg);

        // result_poly holds both the polynomial and the remainder of the division
        float *result_poly = (float*) malloc(sizeof(float) * num_deg);

        if (numerator == NULL || denominator == NULL || result_poly == NULL)
        {
            free(numerator);
            free(denominator);
            free(result_poly);
            printf("There is not enough memory to store the specified degrees of polynomials\n");
            printf("Please enter smaller degrees\n\n");
            continue;
        }

        // A message shown to user one time at the beginning of the program
        if (first_time_flag == 0)
        {
            printf("Each coefficient (a_n) corresponds to x^n,\n");
            printf("ex: x^2 + 3x + 9, a0 = 9, a1 = 3, a2 = 1\n\n");
            first_time_flag = 1;
        }

        // Prompt for the user to enter the polynomial coefficients in order from numerator[0] -> numerator[num_deg - 1]
        for (int i = 0; i < num_deg; i++)
        {
            printf("Enter the coefficient a%d: ", i);
            scanf("%f", &numerator[i]);
            fflush(stdin); fflush(stdout);
        }
        printf("\n");

        // Prompt for the user to enter the polynomial coefficients in order from denominator[0] -> denominator[num_deg - 1]
        for (int i = 0; i < denom_deg; i++)
        {
            printf("Enter the coefficient b%d: ", i);
            scanf("%f", &denominator[i]);
            fflush(stdin); fflush(stdout);
        }

        // Decreases one from the degrees to enter the function properly
        num_deg--; denom_deg--;

        // poly_div takes the first and second arguments as pointers to float(array of floats), and puts the result
        // in the third argument, the fourth and fifth arguments are the degrees of the first and second arguments, respectively
        poly_div(numerator, denominator, result_poly, num_deg, denom_deg);

        // print_poly prints the first argument as a polynomial with the third and fourth arguments needed in case of a remainder
        print_poly(result_poly, result_deg, denominator, denom_deg);
        printf("\n\n");

        // Frees the allocated memory in each of the pointers
        free(numerator);
        free(denominator);
        free(result_poly);

        // A prompt that asks the user if he wants to do another division with different polynomials
        printf("Would you like to try another polynomial division\n");
        printf("Enter y to retry, or any other key to exit\n");
        scanf("%c", &retry);
        printf("\n");
        rem_flag = 0;

    } while (retry == 'y' || retry == 'Y');

    return 0;
}


// poly_div uses the fact that a polynomial division always produces the same number of terms
// distributed between the polynomial and the remainder
void poly_div(float *x, float *y, float *z, int num_deg, int denom_deg)
{
    // A temporary array used to hold the terms that will subtract from the numerator in the division process
    float *temp = (float*) malloc(sizeof(float) * num_deg + 1);

    // This loops over the entire numerator polynomial and resulting polynomial, with i as the index
    for (int i = num_deg; i >= 0; i--)
    {
        // A condition to see if the resulting polynomial is in
        // the polynomial part or the remainder part
        if (i >= (denom_deg))
            z[i] = x[i] / y[denom_deg];
        else
            z[i] = x[i];

        // This loops over the temp array and evaluates each of its terms by multiplying
        // the newly divided term with the denominator and makes the rest of the array 0
        for (int j = denom_deg, k = num_deg; k >= 0; k--)
        {
            if (k <= i && j >= 0)
            {
                temp[k] = z[i] * y[j];
                j--;
            }
            else
                temp[k] = 0;
        }

        // Subtracts the temp array from the numerator and makes that the new numerator
        // and repeats the above steps on the new numerator
        if (i >= denom_deg)
        {
            for (int k = 0; k < num_deg + 1; k++)
                x[k] = x[k] - temp[k];
        }
    }
    // frees the memory allocated to the temporary array
    free(temp);
}

// print_poly prints the array in the first argument and its remainder (if present)
void print_poly(float *x, int degree, float *denominator, int denom_deg)
{
    // A remainder
    float *remainder = (float*) malloc(sizeof(float) * (denom_deg - 1));

    // Loops over the resulting polynomial without the remainder part, where i is the index
    for (int i = degree + denom_deg; i >= denom_deg - 1; i--)
    {
        // This if checks whether the term is the first or not
        if (i == degree + denom_deg)
        {
            // Checks when it is the coefficient of x^0
            if (i == denom_deg)
            {
                if (x[i] > 0)
                    printf("%.2f", x[i]);
                else if (x[i] < 0)
                    printf("- %.2f", -x[i]);
            }
            // Checks when it is the coefficient of x^1
            else if (i == denom_deg + 1)
            {
                if (x[i] > 0)
                    printf("%.2fx", x[i]);
                else if (x[i] < 0)
                    printf("- %.2fx", -x[i]);
            }
            // Checks when it is the coefficient of x^i
            else if (i > denom_deg + 1)
            {
                if (x[i] > 0)
                    printf("%.2fx^%d", x[i], i - denom_deg);
                else if (x[i] < 0)
                    printf("- %.2fx^%d", -x[i], i - denom_deg);
            }
        }
        // Checks when it is not the first term and a coefficient of x^n
        else if (i > denom_deg + 1)
        {
            if (x[i] > 0)
                printf(" + %.2fx^%d", x[i], i - denom_deg);
            else if (x[i] < 0)
                printf(" - %.2fx^%d", -x[i], i - denom_deg);
        }
        // Checks when it is not the first term and a coefficient of x^1
        else if (i == denom_deg + 1)
        {
            if (x[i] > 0)
                printf(" + %.2fx", x[i]);
            else if (x[i] < 0)
                printf(" - %.2fx", -x[i]);
        }
        // Checks when it is not the first term and a coefficient of x^0
        else if (i == denom_deg)
        {
            if (x[i] > 0)
                printf(" + %.2f", x[i]);
            else if (x[i] < 0)
                printf(" - %.2f", -x[i]);
        }
    }

    // A variable that is added when a remainder is found
    int is_remainder = 0;

    // Loops over the remainder and stores each value in the array remainder
    for (int i = denom_deg - 1; i >= 0; i--)
    {
        if (x[i] != 0)
            is_remainder++;
        remainder[i] = x[i];
    }

    // When a remainder is found and the rem_flag is not set, the condition is satisfied
    // and the function prints the remainder part of the polynomial
    if (is_remainder > 0 && rem_flag == 0)
    {
        // Raises rem_flag in order not to re-enter the function again
        rem_flag = 1;

        printf(" + (");
        print_poly(remainder, denom_deg - 1, 0, 0);
        printf(")/(");
        print_poly(denominator, denom_deg, 0, 0);
        printf(")\n");
    }

    // Frees the allocated memory in remainder
    free(remainder);
}
