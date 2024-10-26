# lucas-lehmer
A simple implementation of the Lucas-Lehmer primality test in C.

This program takes one number $n$ as input and prints either `PRIME` or `COMPOSITE` depending on the primality of $2^n - 1$.

In order to build this you need to have the GMP library, GCC, and GNU Make installed. To build, simply run the command `make` in this directory and you should get an executable called `lucas-lehmer`. To test if the Mersenne number `n` is prime, run the command `./lucas-lehmer n`. For example: `./lucas-lehmer 19937` tests if the number $2^{19,937}-1$ is prime.

The way this program works is this: first the input number is checked for primality using the Miller-Rabin test with the bases 2, 7, and 61. With these bases, the test is deterministic for values $n < 4,759,123,141$, which should be good enough for the next few years. If the Miller-Rabin test succeeds then the Lucas-Lehmer test commences.
