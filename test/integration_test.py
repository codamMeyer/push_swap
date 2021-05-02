#!/usr/bin/python3

from pathlib import Path
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


class CheckerErrorManagement:

    def __init__(self):
        pass

    def _runCheckerInput(self, testName, inp, expected=Status.OK):
        print("\nTest case: " + testName)
        Status.print(expected)
        print("Got:   ")
        cmd = "./checker {}".format(inp)
        ret = subprocess.run(cmd, shell=True)
        assert ret.returncode == int(expected)

    def _runCheckerInstruction(self, testName, inp=None, instruction=None, expected=Status.OK):
        print("\nTest case: " + testName)
        Status.print(expected)
        print("Got:   ")
        cmd = "printf '{}' | ./checker {}".format(instruction, inp)
        ret = subprocess.run(cmd, shell=True)
        assert ret.returncode == int(expected)

    def _testNonNumericParameters(self):
        self._runCheckerInput("Non numeric parameters", "1 A", Status.ERROR)

    def _testDuplicatedNumericParameters(self):
        self._runCheckerInput("Duplicated numeric parameters", "1 2 120 2", Status.ERROR)

    def _testNumericValueBiggerThanIntMax(self):
        self._runCheckerInput("Numeric value bigger than INT_MAX", "1 2 2147483648", Status.ERROR)

    def _testNumericValueSmallerThanIntMin(self):
        self._runCheckerInput("Numeric value smaller than INT_MIN", "1 2 -2147483649", Status.ERROR)

    def _testWithoutAnyInput(self):
        self._runCheckerInput("Whitout any parameters", None, Status.ERROR)

    def _testInvalidInstruction(self):
        self._runCheckerInstruction("Valid parameters, invalid instruction", "r", expected=Status.ERROR)

    def _testSpacesBeforeInstruction(self):
        self._runCheckerInstruction("Valid parameters, valid instruction with spaces before", inp="1 2 3", instruction="  rra", expected=Status.ERROR)

    def _testSpacesAfterInstruction(self):
        self._runCheckerInstruction("Valid parameters, valid instruction with spaces after", inp="1 2 3", instruction="rra   ", expected=Status.ERROR)

    def runTests(self):
        print("-------Input Parser Tests-------")
        self._testNonNumericParameters()
        self._testDuplicatedNumericParameters()
        self._testNumericValueBiggerThanIntMax()
        self._testNumericValueSmallerThanIntMin()
        self._testWithoutAnyInput()
        print("--------------------------------")
        print("----Instruction Parser Tests----")
        self._testInvalidInstruction()
        self._testSpacesBeforeInstruction()
        self._testSpacesAfterInstruction()
        print("--------------------------------")


class CheckerFalseTests:

    def __init__(self):
        pass

    def _runCheckerInstruction(self, testName, inp=None, instruction=None, expected=Status.OK):
        print("\nTest case: " + testName)
        Status.print(expected)
        print("Got:   ")
        cmd = "printf '{}' | ./checker {}".format(instruction, inp)
        ret = subprocess.run(cmd, shell=True)
        assert ret.returncode == int(expected)

    def _testWrongSetOfInstructions(self):
        self._runCheckerInstruction("Valid parameters, wrong sorting instructions", inp="0 9 1 8 2 7 3 6 4 5", instruction="sa\npb\nrrr", expected=Status.KO)

    def runTests(self):
        print("------Checker False tests------")
        self._testWrongSetOfInstructions()
        print("-------------------------------")


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


def main():

    assert Path('./checker').is_file()
    assert Path('./push_swap').is_file()

    CheckerErrorManagement().runTests()
    CheckerFalseTests().runTests()
    

main()
