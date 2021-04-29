import random
import os


def generateStack(size, rangeStart, rangeEnd):
    stack = range(rangeStart, rangeEnd)
    return random.sample(stack, size)


def printStack(stack):
    print("before: {}".format(stack))
    print("after: {}".format(sorted(stack)))


def convertToIntList(string):
    li = list(string.split(" "))
    for i in range(0, len(li)):
        li[i] = int(li[i])
    return li


def convertToStrList(intsList):
    stringInts = [str(int) for int in intsList]
    strOfInts = " ".join(stringInts)
    return strOfInts


def compareOutputWithExpected(output, expected):
    if expected == output:
        print("Correct")
    else:
        print("Incorrect")


def testManyInputs(listRange):
    for i in range(50, listRange):
        inputStack = generateStack(i, -2147483648, 2147483647)
        # expected = sorted(inputStack)
        inputList = convertToStrList(inputStack)
        print("\n input: {}".format(inputList))
        os.system("./push_swap {} | ./checker {}".format(inputList, inputList))
        # compareOutputWithExpected(output, ex)


def testIncorretInput():
    incorrect = "1 25 A"
    print("\n input: {}".format(incorrect))
    os.system("./push_swap {} | ./checker {}".format(incorrect, incorrect))


def main():
    # output = "1 2 3 4 5"
    # output = convertToIntList(output)
    os.system("make re")
    testManyInputs(500)
    testIncorretInput()


main()
