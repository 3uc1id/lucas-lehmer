# lucas-lehmer
A simple implementation of the Lucas-Lehmer primality test in C.

This program takes one number $n$ as input and prints either `PRIME` or `COMPOSITE` depending on the primality of $2^n - 1$.

In order to build this you need to have the GMP library, GCC, and GNU Make installed. To build, simply run the command `make` in this directory and you should get an executable called `lucas-lehmer`. To test if the Mersenne number `n` is prime, run the command `./lucas-lehmer n`. For example: `./lucas-lehmer 19937` tests if the number $2^{19,937}-1$ is prime.
