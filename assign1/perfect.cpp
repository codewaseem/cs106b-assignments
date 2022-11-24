/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <iostream>
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
using namespace std;

/* The divisorSum function takes one argument `n` and calculates the
 * sum of proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division using the modulus operator %
 *
 * Note: the C++ long type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n)
{
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++)
    {
        if (n % divisor == 0)
        {
            total += divisor;
        }
    }
    return total;
}

/* The isPerfect function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n)
{
    return (n != 0) && (n == divisorSum(n));
}

/* The findPerfects function takes one argument `stop` and performs
 * an exhaustive search for perfect numbers over the range 1 to `stop`.
 * Each perfect number found is printed to the console.
 */
void findPerfects(long stop)
{
    for (long num = 1; num < stop; num++)
    {
        if (isPerfect(num))
        {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0)
            cout << "." << flush; // progress bar
    }
    cout << endl
         << "Done searching up to " << stop << endl;
}

long smarterSum(long n)
{
    long total = 1;

    for (long divisor = 2; divisor * divisor <= n; divisor++)
    {
        if (n % divisor == 0)
        {
            if (divisor * divisor != n)
            {
                total += divisor + n / divisor;
            }
            else
            {
                total += divisor;
            }
        }
    }

    return total;
}

bool isPerfectSmarter(long n)
{
    return (n != 0) && (n == smarterSum(n));
}

void findPerfectsSmarter(long stop)
{
    for (long num = 1; num < stop; num++)
    {
        if (isPerfectSmarter(num))
        {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0)
            cout << "." << flush; // progress bar
    }
    cout << endl
         << "Done searching up to " << stop << endl;
}

long findNthPerfectEuclid(long n)
{

    auto nthPos = 0;
    long long perfectNum = 0;
    for (long k = 2; nthPos < n; k++)
    {
        auto m = pow(2, k) - 1;
        if (smarterSum(m) == 1)
        {
            perfectNum = (pow(2, k - 1) * m);
            nthPos++;
        }
    }

    return perfectNum;
}

/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs")
{
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect")
{
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect")
{
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect")
{
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect")
{
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trial of findPerfects on input size 1000")
{
    TIME_OPERATION(1000, findPerfects(1000));
}

STUDENT_TEST("Multiple time trials of findPerfects on increasing input sizes")
{

    int smallest = 10'000, largest = 40'000;

    for (size_t size = smallest; size <= largest; size *= 2)
    {
        TIME_OPERATION(size, findPerfects(size));
    }
}

STUDENT_TEST("isPerfect returns false for negative input")
{
    EXPECT_EQUAL(isPerfect(-1), false);
    EXPECT_EQUAL(isPerfect(-1000), false);
}

STUDENT_TEST("smarterSum(n) returns same output as divisorSum(n)")
{
    EXPECT_EQUAL(smarterSum(6), divisorSum((6)));
    EXPECT_EQUAL(smarterSum(25), divisorSum((25)));
    EXPECT_EQUAL(smarterSum(28), divisorSum((28)));
    EXPECT_EQUAL(smarterSum(496), divisorSum((496)));
}

STUDENT_TEST("Multiple time trials of findPerfectsSmarter on increasing input sizes")
{

    int smallest = 10'000, largest = 100'000 * 8;

    for (size_t size = smallest; size <= largest; size *= 2)
    {
        TIME_OPERATION(size, findPerfectsSmarter(size));
    }
}

STUDENT_TEST("fintNthPerfectNumber with euclid algorithm")
{
    EXPECT_EQUAL(findNthPerfectEuclid(1), 6);
    EXPECT_EQUAL(findNthPerfectEuclid(4), 8128);
    EXPECT_EQUAL(findNthPerfectEuclid(5), 33550336);
    EXPECT_EQUAL(findNthPerfectEuclid(6), 8589869056);
    EXPECT_EQUAL(findNthPerfectEuclid(7), 137438691328);
    EXPECT_EQUAL(findNthPerfectEuclid(8), 2305843008139952128);
}
