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
    }
}

void
next_iter(uint16_t *product, 
          int8_t   multiplicand,
          bool     *flag)
{
    bool product_bit = (*product & FLAG_MASK);

    if (!product_bit && *flag) {
        int8_t top = (int8_t)(*product >> 8);
        int8_t res = top + multiplicand;
        *product = (*product & 0x00FF) | (((uint16_t)(uint8_t)res) << 8);
    }
    else if (product_bit && !*flag) {
        int8_t top = (int8_t)(*product >> 8);
        int8_t res = top - multiplicand;
        *product = (*product & 0x00FF) | (((uint16_t)(uint8_t)res) << 8);
    }

    *flag = product_bit;

    // Arithmetic right shift
    *product = (uint16_t)( (int16_t)(*product) >> 1 );
}

int8_t
booths_alg (uint16_t x, int8_t y)
{
    print_bits (16, x);
    printf ("\n%d\n", x);
    print_bits (8, y);
    printf ("\n%d\n", y);

    uint16_t product    = x;
    int8_t multiplicand = y;
    bool   flag         = 0;

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

    /* Return 8 least significant bits */
    return (int8_t) (product >> 8);
}

int
main ()
{
    int x, y;

    printf ("Enter an integer: ");
    scanf ("%d", &x);

    printf ("Enter another integer: ");
    scanf ("%d", &y);

    int8_t result = booths_alg ((uint16_t) y, (int8_t) x);
    printf ("Result: %d", result);

    return 0;
}
