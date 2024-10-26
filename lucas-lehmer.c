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
#include "lucas-lehmer.h"


bool lucas_lehmer(uint64_t p){
    mpz_t s, temp;
    mpz_init_set_ui(s, 4);
    mpz_init(temp);
    for(uint64_t i=0; i<p-2; i++){
        mpz_mul(s, s, s);
        mpz_sub_ui(s, s, 2);
        while(mpz_sizeinbase(s, 2) > p){
            mpz_tdiv_q_2exp(temp, s, p); // temp = s >> p
            mpz_tdiv_r_2exp(s, s, p);    // s = s % 2**p
            mpz_add(s, s, temp);         // s = s + temp
        }
    }
    bool result = mpz_scan0(s, 0)==p && mpz_sizeinbase(s, 2)==p;
    mpz_clears(s, temp, NULL);
    return result;
}
