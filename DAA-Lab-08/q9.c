#include <stdio.h>
#include <limits.h>

/* Return the next value in the Collatz sequence */
unsigned long long collatzNext(unsigned long long n) {

    if (n % 2 == 0)
        return n / 2;

    /* Check overflow before calculating 3*n + 1 */
    if (n > (ULLONG_MAX - 1) / 3) {
        printf("Overflow would occur for n = %llu\n", n);
        return 0;
    }

    return 3 * n + 1;
}


/* Print the complete trajectory */
void printTrajectory(unsigned long long n) {

    printf("%llu", n);

    while (n != 1) {
        n = collatzNext(n);

        if (n == 0) {
            printf(" -> OVERFLOW");
            break;
        }

        printf(" -> %llu", n);
    }

    printf("\n");
}


/* Count number of steps needed to reach 1 */
unsigned long long collatzSteps(unsigned long long n) {

    unsigned long long steps = 0;

    while (n != 1) {

        n = collatzNext(n);

        if (n == 0)
            return ULLONG_MAX;

        steps++;
    }

    return steps;
}


/* Find maximum value reached in the trajectory */
unsigned long long collatzMaximum(unsigned long long n) {

    unsigned long long maximum = n;

    while (n != 1) {

        n = collatzNext(n);

        if (n == 0)
            return ULLONG_MAX;

        if (n > maximum)
            maximum = n;
    }

    return maximum;
}


/* Analyze all starting values in [a,b] */
void analyzeInterval(unsigned long long a,
                     unsigned long long b) {

    unsigned long long maxSteps = 0;
    unsigned long long maxStepsN = a;

    unsigned long long maxValue = 0;
    unsigned long long maxValueN = a;

    for (unsigned long long n = a; n <= b; n++) {

        unsigned long long steps = collatzSteps(n);
        unsigned long long maximum = collatzMaximum(n);

        if (steps == ULLONG_MAX ||
            maximum == ULLONG_MAX) {

            printf("Overflow encountered for starting value %llu\n", n);
            continue;
        }

        printf("n = %llu, steps = %llu, maximum = %llu\n",
               n, steps, maximum);

        if (steps > maxSteps) {
            maxSteps = steps;
            maxStepsN = n;
        }

        if (maximum > maxValue) {
            maxValue = maximum;
            maxValueN = n;
        }

        /*
           Avoid unsigned integer wraparound when
           incrementing n.
        */
        if (n == ULLONG_MAX)
            break;
    }

    printf("\nSummary for [%llu, %llu]\n", a, b);

    printf("Starting value with maximum stopping time: %llu\n",
           maxStepsN);

    printf("Maximum number of steps: %llu\n",
           maxSteps);

    printf("Starting value reaching the largest value: %llu\n",
           maxValueN);

    printf("Largest value reached: %llu\n",
           maxValue);
}


int main() {

    unsigned long long n;
    unsigned long long a, b;

    printf("Enter starting value n: ");
    scanf("%llu", &n);

    if (n < 1) {
        printf("n must be >= 1.\n");
        return 1;
    }

    printf("\nCollatz trajectory:\n");
    printTrajectory(n);

    printf("\nNumber of steps to reach 1: %llu\n",
           collatzSteps(n));

    printf("\nMaximum value reached: %llu\n",
           collatzMaximum(n));

    printf("\nEnter interval [a,b]: ");
    scanf("%llu %llu", &a, &b);

    if (a < 1 || a > b) {
        printf("Invalid interval.\n");
        return 1;
    }

    printf("\nInterval analysis:\n");
    analyzeInterval(a, b);

    return 0;
}
// Collatz trajectory:

// 60 -> 80 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
// 17275526695616512 -> 8637763347808256 -> 4318881673904128 -> 2159440836952064 -> 1079720418476032 ->
//  539860209238016 -> 269930104619008 -> 134965052309504 -> 67482526154752 -> 33741263077376 -> 16870631538688
//   -> 8435315769344 -> 4217657884672 -> 2108828942336 -> 1054414471168 -> 527207235584 -> 263603617792 -> 131801808896 ->
//    65900904448 -> 32950452224 -> 16475226112 -> 8237613056 -> 4118806528 -> 2059403264 -> 1029701632 -> 514850816 -> 257425408 -> 
//    128712704 -> 64356352 -> 32178176 -> 16089088 -> 8044544 -> 4022272 -> 2011136 -> 1005568 -> 502784 -> 251392 ->
//     125696 -> 62848 -> 31424 -> 15712 -> 7856 -> 3928 -> 1964 -> 982 -> 491 -> 1474 -> 737 -> 2212 -> 1106 -> 553 ->
//      1660 -> 830 -> 415 -> 1246 -> 623 -> 1870 -> 935 -> 2806 -> 1403 -> 4210 -> 2105 -> 6316 -> 3158 -> 1579 -> 4738 ->
//       2369 -> 7108 -> 3554 -> 1777 -> 5332 -> 2666 -> 1333 -> 4000 -> 2000 -> 1000 -> 500 -> 250 -> 125 -> 376 ->
//        188 -> 94 -> 47 -> 142 -> 71 -> 214 -> 107 -> 322 -> 161 -> 484 -> 242 -> 121 -> 364 -> 182 -> 91 ->
//         274 -> 137 -> 412 -> 206 -> 103 -> 310 -> 155 -> 466 -> 233 -> 700 -> 350 -> 175 -> 526 -> 263 ->
//          790 -> 395 -> 1186 -> 593 -> 1780 -> 890 -> 445 -> 1336 -> 668 -> 334 -> 167 -> 502 -> 251 -> 754 -> 377 -> 1132 ->
//           566 -> 283 -> 850 -> 425 -> 1276 -> 638 -> 319 -> 958 -> 479 -> 1438 -> 719 -> 2158 -> 1079 -> 3238 -> 1619 -> 4858 ->
//            2429 -> 7288 -> 3644 -> 1822 -> 911 -> 2734 -> 1367 -> 4102 -> 2051 -> 6154 -> 3077 -> 9232 -> 4616 -> 2308 -> 1154 ->
//             577 -> 1732 -> 866 -> 433 -> 1300 -> 650 -> 325 -> 976 -> 488 -> 244 -> 122 -> 61 -> 184 -> 92 -> 46 -> 23 -> 70 ->
//              35 -> 106 -> 53 -> 160 -> 80 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1