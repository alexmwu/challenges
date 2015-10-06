#!/usr/bin/env python

set0 = list(set([1, 2, 3, 4]))
set1 = list(set([1, 2, 2, 3, 4, 10]))
set2 = list(set([1, 1, 2, 2, 2, 2]))

def getSubsets(setList):
    subs = subsets(setList, 0)
    for sub in subs:
        sub.sort()
    return sorted(subs, key = lambda sub: len(sub))

def subsets(setList, index):
    if len(setList) == 0:
        return []
    if index == len(setList) - 1:
        curr = [[]]
        curr.append([setList[index]])
        return curr
    else:
        currSubsets = subsets(setList, index + 1)
        newSubsets = []
        for subset in currSubsets:
            newSubsets.append(subset[:])
            subset.append(setList[index])
        currSubsets += newSubsets
        return currSubsets


print getSubsets([])
print getSubsets(set0)
print getSubsets(set1)
print getSubsets(set2)
