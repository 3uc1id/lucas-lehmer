/*
    lucas-lehmer: an implementation of the Lucas-Lehmer primality test for Mersenne Primes.
    Copyright (C) 2024  Christian Calderon

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "miller-rabin.h"
#include "lucas-lehmer.h"

int main(int argc, char **argv){
    if(argc < 2){
        fprintf(stderr, "Missing argument.\n");
        return EXIT_FAILURE;
    }
    
    uint64_t p = strtoull(argv[1], NULL, 10);

    // first check if the input is prime using a Miller-RAbin test.
    // These bases give correct results for p < 4,759,123,141
    uint64_t bases[3] = {2, 7, 61};
    for(int i=0; i<3; i++){
        if(!is_probab_prime(p, bases[i])){
            printf("COMPOSITE\n"); // composite p -> 2**p - 1 is composite
            return EXIT_SUCCESS;
        }
    }
    
    if(lucas_lehmer(p)){
        printf("PRIME\n");
    }
    else {
        printf("COMPOSITE\n");
    }

    return EXIT_SUCCESS;
}