#!/usr/bin/python3

import random
import subprocess


RUN_COMMAND = "./push_swap {} | ./checker {}"


def generateStack(size, rangeStart, rangeEnd):
    stack = range(rangeStart, rangeEnd)
    return random.sample(stack, size)


def printStack(stack):
    print("before: {}".format(stack))
    print("after: {}".format(sorted(stack)))


def convertToIntList(string):
    strList = string.split(" ")
    strList.remove("")
    intList = [int(i) for i in strList]
    return intList


def convertToStrList(intsList):
    stringInts = [str(i) for i in intsList]
    strOfInts = " ".join(stringInts)
    return strOfInts


def testManyInputs(listMin, listMax):
    for i in range(listMin, listMax):
        inputStack = generateStack(i, -2147483648, 2147483647)
        inputList = convertToStrList(inputStack)
        print("list size: {}".format(i))
        ret = subprocess.run(RUN_COMMAND.format(inputList, inputList), shell=True)
        assert ret.returncode == 0
        with open("result") as f:
            line = f.read()
            output = convertToIntList(line)
        expected = sorted(inputStack)
        assert output == expected


def testIncorretInput():
    inp = "1 25 A"
    ret = subprocess.run(RUN_COMMAND.format(inp, inp), shell=True)
    assert ret.returncode > 0


def main():
    testIncorretInput()
    testManyInputs(499, 500)


main()
