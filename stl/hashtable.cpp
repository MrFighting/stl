//
// Created by Administrator on 2016/8/16.
//

#include "hashtable.h"
namespace stl {
    unsigned long prime_list[stl::num_primes] =
            {
                    5ul, 53ul, 97ul, 193ul, 389ul,
                    769ul, 1543ul, 3079ul, 6151ul, 12289ul,
                    24593ul, 49157ul, 98317ul, 196613ul, 393241ul,
                    786433ul, 1572869ul, 3145739ul, 6291469ul, 12582917ul,
                    25165843ul, 50331653ul, 100663319ul, 201326611ul, 402653189ul,
                    805306457ul, 1610612741ul, 3221225473ul, 4294967291ul
            };
    unsigned long next_prime(unsigned long n) {
        auto pos = std::lower_bound(begin(prime_list), end(prime_list), n);
        return pos == end(prime_list) ?
               prime_list[stl::num_primes - 1] : *pos;
    }
}
