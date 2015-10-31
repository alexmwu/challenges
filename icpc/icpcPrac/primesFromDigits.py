import sys
import math
raw_input()

primes = {}
primes[0] = False
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
    l = permutations(seen, remainingStr, currStr)
    return l

def permutations(seen, remainingStr, currStr):
    numPrimes = 0
    if len(currStr) > 0 and currStr[0] == '0':
        return 0
    if currStr in seen:
        return 0
    else:
        seen[currStr] = 1
    for i in xrange(len(remainingStr)):
        newStr = currStr
        newStr += remainingStr[i]
        val = int(newStr)
        if isPrime(val):
            numPrimes += 1
        numPrimes += permutations(seen, remainingStr[:i] + remainingStr[i+1:], newStr)
    return numPrimes


while 1:
    try:
        line = raw_input().rstrip()
        if not line: break
        print getNumPrimes(line, "")
    except(EOFError):
        break
