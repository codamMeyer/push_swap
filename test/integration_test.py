#!/usr/bin/python3

from pathlib import Path
import random
import subprocess
from enum import IntEnum

LIGHT_RED = "\033[1;31m"
LIGHT_GREEN = "\033[1;32m"
LIGHT_PURPLE = "\033[1;35m"
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
            print(EXPECT_OK)
        elif expected == cls.KO:
            print(EXPECT_KO)
        else:
            print(EXPECT_ERROR)


def printTestBanner(testName):
    print("{}======================================================================{}".format(LIGHT_PURPLE, LIGHT_WHITE))
    print("                          {}".format(testName))
    print("{}======================================================================{}".format(LIGHT_PURPLE, LIGHT_WHITE))


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
        print("\nWhitout any parameters, should just return")
        assert subprocess.run("./checker", shell=True).returncode > 0
        print("\n")

    def _testInvalidInstruction(self):
        self._runCheckerInstruction("Valid parameters, invalid instruction", "1 2 3", "r", Status.ERROR)

    def _testSpacesBeforeInstruction(self):
        self._runCheckerInstruction("Valid instruction with spaces before", "1 2 3", "  rra", Status.ERROR)

    def _testSpacesAfterInstruction(self):
        self._runCheckerInstruction("Valid instruction with spaces after", "1 2 3", "rra   ", Status.ERROR)

    def runTests(self):
        printTestBanner("Checker Error management")
        self._testNonNumericParameters()
        self._testDuplicatedNumericParameters()
        self._testNumericValueBiggerThanIntMax()
        self._testNumericValueSmallerThanIntMin()
        self._testWithoutAnyInput()
        self._testInvalidInstruction()
        self._testSpacesBeforeInstruction()
        self._testSpacesAfterInstruction()


class CheckerFalseTests:

    def __init__(self):
        pass

    def _runCheckerInstruction(self, testName, inp=None, instruction=None, expected=Status.OK):
        print("\nTest case: " + testName)
        Status.print(expected)
        print("Got:   ")
        cmd = "printf '{}' | ./checker -v {}".format(instruction, inp)
        ret = subprocess.run(cmd, shell=True)
        assert ret.returncode == int(expected)

    def _testWrongSetOfInstructions(self, inp, instructions):
        self._runCheckerInstruction("Valid parameters, wrong sorting instructions", inp, instructions, Status.KO)

    def runTests(self):
        printTestBanner("Checker False tests")
        self._testWrongSetOfInstructions("0 9 1 8 2 7 3 6 4 5", "sa\npb\nrrr")
        self._testWrongSetOfInstructions("5 1 2 3 4", "pb")


class CheckerRightTests:

    def __init__(self):
        pass

    def _runCheckerInstruction(self, testName, inp=None, instruction=None, expected=Status.OK):
        print("\nTest case: " + testName)
        Status.print(expected)
        print("Got:   ")
        cmd = "printf '{}' | ./checker -v {}".format(instruction, inp)
        ret = subprocess.run(cmd, shell=True)
        assert ret.returncode == int(expected)

    def _testRightSetOfInstructions(self, inp, instructions):
        self._runCheckerInstruction("Right sorting instructions", inp, instructions, Status.OK)

    def runTests(self):
        printTestBanner("Checker Right tests")
        self._testRightSetOfInstructions("0 1 2", "")
        self._testRightSetOfInstructions("0 9 1 8 2", "pb\nra\npb\nra\nsa\nra\npa\npa")


class PushSwapIdentityTests:

    def __init__(self):
        pass

    def _runPushSwap(self, testName, inp=None, expected=""):
        print("\nTest case: " + testName)
        print("Expected: {}".format(expected))
        print("Got:    ")
        cmd = "./push_swap {}".format(inp)
        subprocess.run(cmd, shell=True)

    def _testOnlyOneElement(self):
        self._runPushSwap("Only one element", "42")

    def _testWithSortedElements(self, inp):
        self._runPushSwap("Sorted elements '{}'".format(inp), inp)

    def runTests(self):
        printTestBanner("Push Swap Identity tests")
        self._testOnlyOneElement()
        self._testWithSortedElements("0 1 2 3")
        self._testWithSortedElements("0 1 2 3 4 5 6 7 8 9")


class StackGenerator:
    def __init__(self):
        pass

    def _generateStack(self, size, rangeStart, rangeEnd):
        stack = range(rangeStart, rangeEnd)
        return random.sample(stack, size)

    def _convertToIntList(self, string):
        strList = string.split(" ")
        strList.remove("")
        intList = [int(i) for i in strList]
        return intList

    def _convertToStrList(self, intsList):
        stringInts = [str(i) for i in intsList]
        strOfInts = " ".join(stringInts)
        return strOfInts

    def run(self, stackSize):
        inputStack = self._generateStack(stackSize, -2147483648, 2147483647)
        return self._convertToStrList(inputStack)
        # ret = subprocess.run(RUN_COMMAND.format(inputList, inputList), shell=True)
        # assert ret.returncode == 0
        # with open("result") as f:
        #     line = f.read()
        #     output = self._convertToIntList(line)
        # expected = sorted(inputStack)
        # assert output == expected


class PushSwapSortingTests:

    def __init__(self, name):
        self.name = name

    def _runPushSwap(self, testName, inp, expected, maxMoves):
        print("\nTest case: " + testName)
        Status.print(expected)
        print("Expected less than {} moves\nGot:    ".format(maxMoves))
        cmd = "./push_swap {} | ./checker -t {}".format(inp, inp)
        ret = subprocess.run(cmd, shell=True).returncode
        assert ret == expected

    def _testFiveElementes(self):
        self._runPushSwap("Five Elements [{}]".format("5 1 2 4 3"), "5 1 2 4 3", Status.OK, 12)

    def runSimpleVersionTests(self):
        printTestBanner(self.name)
        self._testFiveElementes()
        stack = StackGenerator().run(5)
        self._runPushSwap("Five Elements [{}]".format(stack), stack, Status.OK, 12)

    def runMiddleVersionTests(self):
        printTestBanner(self.name)
        stack = StackGenerator().run(100)
        self._runPushSwap("100 Elements", stack, Status.OK, 1500)

    def runAdvancedVersionTests(self):
        printTestBanner(self.name)
        stack = StackGenerator().run(500)
        self._runPushSwap("500 Elements", stack, Status.OK, 11500)


def main():

    assert Path('./checker').is_file()
    assert Path('./push_swap').is_file()

    CheckerErrorManagement().runTests()
    CheckerFalseTests().runTests()
    CheckerRightTests().runTests()
    PushSwapIdentityTests().runTests()
    PushSwapSortingTests("Simple Version Tests").runSimpleVersionTests()
    PushSwapSortingTests("Middle Version Tests").runMiddleVersionTests()
    PushSwapSortingTests("Advanced Version Tests").runAdvancedVersionTests()


main()
