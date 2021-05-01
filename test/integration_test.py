#!/usr/bin/python3

import random
import subprocess
from enum import IntEnum

LIGHT_RED = "\033[1;31m"
LIGHT_GREEN = "\033[1;32m"
LIGHT_WHITE = "\033[0;37m"
RUN_COMMAND = "./push_swap {} | ./checker {}"
EXPECT_ERROR = "Expect:\n\033[1;31mError\033[0;37m"
EXPECT_KO = "Expect:\n\033[1;31m[KO]\033[0;37m"
EXPECT_OK = "Expect:\n\033[1;32m[OK]\033[0;37m"


class Status(IntEnum):
    OK = 0
    KO = 1
    ERROR = 2

    @classmethod
    def print(cls, expected):
        if expected == cls.OK:
            print(EXPECT_KO)
        elif expected == cls.KO:
            print(EXPECT_KO)
        else:
            print(EXPECT_ERROR)


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


def testIncorretInputs():
    # inp = "1 25 A"
    # ret = subprocess.run(RUN_COMMAND.format(inp, inp), shell=True)
    # assert ret.returncode > 0
    inp = ""
    ret = subprocess.run(RUN_COMMAND.format(inp, inp), shell=True)
    assert ret.returncode > 0


def testCheckerInputParser(testName, inp=None, expected=Status.OK):
    print("\nTest case: " + testName)
    Status.print(expected)
    print("Got:   ")
    ret = subprocess.run("./checker {}".format(inp), shell=True)
    assert ret.returncode == int(expected)


def testCheckerInstructionParser(testName, inp=None, instruction=None, expected=Status.OK):
    print("\nTest case: " + testName)
    Status.print(expected)
    print("Got:   ")
    ret = subprocess.run("echo -e '{}' | ./checker {}".format(instruction, inp), shell=True)
    assert ret.returncode == expected


def main():
    testCheckerInputParser("Non numeric parameters", "1 A", expected=Status.ERROR)
    testCheckerInputParser("Duplicated numeric parameters", "1 2 120 2", expected=Status.ERROR)
    testCheckerInputParser("Numeric value bigger than INT_MAX", "1 2 2147483648", expected=Status.ERROR)
    testCheckerInputParser("Numeric value bigger than INT_MAX", "1 2 2147483648", expected=Status.ERROR)
    testCheckerInputParser("Whitout any parameters", expected=Status.ERROR)
    testCheckerInstructionParser("Valid parameters, invalid instruction", "r", expected=Status.ERROR)
    testCheckerInstructionParser("Valid parameters, valid instruction with spaces before", inp="1 2 3", instruction="  rra", expected=Status.ERROR)
    testCheckerInstructionParser("Valid parameters, valid instruction with spaces after", inp="1 2 3", instruction="rra   ", expected=Status.ERROR)
    testCheckerInstructionParser("Valid parameters, wrong sorting instructions", inp="0 9 1 8 2 7 3 6 4 5", instruction="sa\npb\nrrr", expected=Status.KO)

    # testIncorretInputs()
    # testManyInputs(1, 20)
    # testManyInputs(100, 101)
    # testManyInputs(500, 501)


main()
