#!/usr/bin/env python
import time

def recursiveMultiply(a, b):
    if a > b:
        # return multiply(a, b)
        # return shiftMultiply(a, b, 0)
        return evenMultiply(b, a)
    else:
        # return multiply(b,a)
        # return shiftMultiply(b, a, 0)
        return evenMultiply(b, a)

# slowest multiply
def multiply(a, b):
    if a == 0 or b == 0:
        return 0
    else:
        return multiply(a, b - 1) + a

# using bitshifts
def shiftMultiply(a, b, bitsShifted):
    if a == 0 or b == 0:
        return 0
    shifted = 1 << bitsShifted
    if (1 << (bitsShifted + 1)) - b >= 0:
        return multiply(a, (b - shifted)) + (a << bitsShifted)
    else:
        return shiftMultiply(a, b, bitsShifted + 1)

# O(log(smaller))
def evenMultiply(a, b):
    if b == 0:
        return 0
    elif b == 1:
        return a
    if b % 2 == 0:
        dividedBy2 = evenMultiply(a, b >> 1)
        return dividedBy2 + dividedBy2
    else:
        dividedBy2 = evenMultiply(a, b >> 1)
        dividedBy2MinusOne = evenMultiply(a, (b >> 1) + 1)
        return dividedBy2 + dividedBy2MinusOne

start = time.time()
print recursiveMultiply(5, 2)
print recursiveMultiply(5, 13)
print recursiveMultiply(0, 13)
print recursiveMultiply(5, 0)
print recursiveMultiply(0, 0)
print recursiveMultiply(10, 210)
print recursiveMultiply(128, 2348)
print recursiveMultiply(12345820984, 22342384920)     # only works on last (evenMultiply) function

print 'time: ' + str(time.time() - start)
