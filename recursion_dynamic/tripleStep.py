#!/usr/bin/env python
cache = {0: 0,
        1: 1,
        2: 2,
        3: 3}
def tripleStep(n):
    if n <= 3:
        return cache[n]
    else:
        return tripleStep(n - 1) + tripleStep(n - 2) + tripleStep(n - 3)

print tripleStep(0)
print tripleStep(1)
print tripleStep(2)
print tripleStep(3)
print tripleStep(4)
print tripleStep(5)
print tripleStep(6)
print tripleStep(7)
print tripleStep(8)
print tripleStep(9)
print tripleStep(10)
print tripleStep(11)
