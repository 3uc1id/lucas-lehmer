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
#include "miller-rabin.h"


static uint64_t gcd(uint64_t a, uint64_t b) {
    uint64_t temp;
    if(b > a){
        temp = a;
        a = b;
        b = temp;
    }
    while(b!=0){
        temp = b;
        b = a%b;
        a = temp;
    }
    return a;
}


static uint64_t mulmod(uint64_t a, uint64_t b, uint64_t m) {
    //a*b mod m = a*(b_0*2**0 + b_1*2**1 + ... + b_n*2**n) mod m
    //          = (a*b_0*2**0 mod m) + (a*b_1*2**1 mod m)
    uint64_t result = 0;
    // a*b mod m = (a mod m)*(b mod m)
    a %= m;
    b %= m;

    // swap a and b to reduce iterations
    if(__builtin_popcount(a) < __builtin_popcount(b)){
        a ^= b; // a = a^b
        b ^= a; // b = (a^b)^b = a^(b^b) = a
        a ^= b; // a = (a^b)^a = (a^a)^b = b
    }

    for(; b > 0; b >>= 1){
        if(b&1){
            result += a;
            result %= m;
        }
        a <<= 1;
        a %= m;
    }

    return result;
}


static uint64_t powmod(uint64_t a, uint64_t b, uint64_t m) {
    // a**b mod m = a**(b_0*2**0 + b_1*2**1 + ... + b_n*2**n) mod m
    //            = (a**(b_0*2**0) mod m)*(a**(b_1*2**1) mod m)*...*(a**(b_n*2**n) mod m) mod m
    uint64_t result = 1;

    // Update 'a' if it is more than or equal to 'm'
    a %= m;

    while (b > 0) {
        // If b is odd, multiply 'a' with the result
        if (b & 1){
            result = mulmod(result, a, m); //((result % m) * (a % m)) % m;
        }
            
        a = mulmod(a, a, m);
        b >>= 1;
    }
    
    return result;
}


bool is_probab_prime(uint64_t n, uint64_t base){
    if(gcd(n, base) != 1){
        return false;
    }
    uint64_t n1 = n - 1;
    uint64_t s = __builtin_ctz(n1);
    uint64_t d = n1 >> s;
    uint64_t x = powmod(base, d, n);

    if(x == 1 || x == n1){
        return true;
    }

    for(int i = 0; i < s - 1; i++){
        x = mulmod(x, x, n);
        if(x == n1){
            return true;
        }
    }

    return false;
}