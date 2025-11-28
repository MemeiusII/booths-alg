#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define SHFT_AMT 1

const uint16_t PRODUCT_MASK = 0b1111111100000000;
const uint16_t FLAG_MASK    = 0b0000000000000001;

void
print_bits (size_t size, uint16_t byte) 
{
    for (int i = size - 1; i >= 0; i--)
    {
        printf ("%d", (byte >> i) & 1);
        if (i % 8 == 0)
            printf(" ");
    }
}

void
next_iter(uint16_t *product, 
          uint8_t  multiplicand,
          bool     *flag)
{
    bool product_bit = (*product & FLAG_MASK);

    if (!product_bit && *flag) {
        printf ("Add\n");
        uint8_t top = *product >> 8;
        uint8_t res = top + multiplicand;
        *product = (*product & ~PRODUCT_MASK) | ((uint16_t) res) << 8;
    }
    else if (product_bit && !*flag) {
        printf ("Sub\n");
        uint8_t top = *product >> 8;
        uint8_t res = top - multiplicand;
        *product = (*product & ~PRODUCT_MASK) | ((uint16_t) res) << 8;
    }
    else
        printf ("Nop\n");

    *flag = product_bit;
    // Arithmetic right shift
    printf ("Shift Right\n");
    *product = (uint16_t)( (int16_t)(*product) >> 1 );
}

int8_t
booths_alg (int8_t x, int8_t y)
{
    print_bits (8, x);
    printf ("\n%d\n", x);
    print_bits (8, y);
    printf ("\n%d\n", y);

    uint16_t product      = (uint16_t) x & ~PRODUCT_MASK; // Set leading zeros
    int8_t   multiplicand = y;
    bool     flag         = 0;

    printf ("Initialize\n");
    printf ("Product: ");
    print_bits (16, product);
    printf ("|%d\n", flag);

    printf ("Multiplicand: ");
    print_bits (8, multiplicand);
    printf ("\n");

    printf("===================== \n");

    for (size_t i = 0; i < 8; i++)
    {
        printf ("Iteration: %ld\n", i);
        printf ("Product: ");
        print_bits (16, product);
        printf ("|%d\n", flag);

        printf ("Multiplicand: ");
        print_bits (8, multiplicand);
        printf ("\n");

        next_iter (&product, multiplicand, &flag);
        printf ("===================== \n");

    }

    return (int8_t) (product);
}

int
main ()
{
    int x, y;

    printf ("Enter an integer: ");
    scanf ("%d", &x);

    printf ("Enter another integer: ");
    scanf ("%d", &y);

    int8_t result = booths_alg ((uint8_t) y, (uint8_t) x);
    printf ("Result: %d\n", (int)result);
    print_bits (8, result);

    return 0;
}
