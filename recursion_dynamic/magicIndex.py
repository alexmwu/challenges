#!/usr/bin/env python
list0 = [-40, -10, -3, -1, 1, 2, 3, 6, 7, 9, 10, 12]
list1 = [-40, -10, 2, 3, 7, 9, 10, 11, 12]
list2 = [-10, -5, 2, 2, 2, 3, 4, 7, 9, 12, 13]
list3 = [ -128, - 127, -68, -40, 100, 101, 101, 500, 800]

# unique
def magic(arr):
    return magicIndex(arr, 0, len(arr) - 1)

def magicIndex(arr, start, end):
    if end < start:
        return False
    if len(arr) == 0:
        return False
    m = (start + end) / 2
    if arr[m] == m:
        return m
    elif arr[m] < m:
        return magicIndex(arr, m + 1, end)
    else:
        return magicIndex(arr, start, m - 1)

# not unique
def modMagic(arr):
    return magicIndex(arr, 0, len(arr) - 1)

def modMagicIndex(arr, start, end):
    if end < start:
        return False
    if len(arr) == 0:
        return False
    m = (start + end) / 2
    if arr[m] == m:
        return m
    newEnd = min(m - 1, arr[m])
    mi = magicIndex(arr, start, newEnd)
    if mi is not False:
        return mi
    newEnd = max(m + 1, arr[m])
    mi = magicIndex(arr, start, newEnd)
    return magicIndex(arr, m - 1, end)

print magic(list0)
print magic(list1)
print magic(list3)
print modMagic(list0)
print modMagic(list1)
print modMagic(list2)
print modMagic(list3)
