#!/usr/bin/env python

import sys
import math
# raw_input()

primes = {}
primes[1] = False

def isPrime(i):
    if i in primes:
        return primes[i]
    for j in xrange(2, int(math.sqrt(i)) + 1):
        if i % j == 0:
            primes[i] = False
            return False
    primes[i] = True
    return True

def getNumPrimes(remainingStr, currStr):
    seen = {}
    return permutations(seen, remainingStr, currStr)

def permutations(seen, remainingStr, currStr):
    numPrimes = 0
    for i in xrange(len(remainingStr)):
        newStr = currStr
        newStr += remainingStr[i]
        val = int(newStr)
        if val in seen:
            continue
        else:
            seen[val] = 1
        if isPrime(val):
            numPrimes += 1
        numPrimes += permutations(seen, remainingStr[:i] + remainingStr[i+1:], newStr)
    return numPrimes


while 1:
    line = raw_input()
    if not line: break
    print getNumPrimes(line, "")
