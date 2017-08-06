import dHammingPy
import random
import timeit

THRESHOLD = 90
RAND_SEED = 42

blocks = []

def setup():
    global blocks
    random.seed(RAND_SEED)
    blocks = ["{:064x}".format(random.getrandbits(256)) for i in range(0, 7020)]

def timed_function():
    global blocks
    setup()
    matches = []
    dHL = dHammingPy.CompatHashList()
    for hsh in blocks:
        dHL.Add(hsh)
    dH = dHammingPy.dHamming()
    rawMatch = dH.GetPairsOverHammingThreshold(dHL, THRESHOLD)
    while rawMatch.Advance():
        matches.append((rawMatch.GetLeft(), rawMatch.GetRight()))
    print("Found {} matches".format(len(matches)))

if __name__ == "__main__":
    result = timeit.repeat(stmt="timed_function()", setup="from __main__ import timed_function", repeat=10, number=1)
    print("min:    {}".format(min(result)))
    print("max:    {}".format(max(result)))
    print("median: {}".format(result[len(result)//2]))
