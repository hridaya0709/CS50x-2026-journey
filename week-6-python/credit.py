from cs50 import get_string

# Find the checkSum of the credit number provided


def is_checksum_valid(creditNo):
    checkSum = 0
    counter = 0

    # Traversing from the last index of the credit no.
    for i in range(len(creditNo), -1, -1):

        # Skipping the length because it will cause Index Out Of Bound Exception
        if i != len(creditNo):
            # print("counter", counter, i)

            # When there is a even value of counter
            if counter % 2 == 0:
                # print(int(creditNo[i]))

                # doubling the value
                twiceOfCurrentLastDigit = int(creditNo[i]) * 2
                # print(twiceOfCurrentLastDigit)

                # if the doubled value is >9, find the sum of the digits and add that to checksum
                if (twiceOfCurrentLastDigit > 9):
                    twiceOfCurrentLastDigit = findSumOfDigits(twiceOfCurrentLastDigit)
                    # print("After sum of digits", twiceOfCurrentLastDigit)

                # print(checkSum)
                checkSum = checkSum + twiceOfCurrentLastDigit
                # print("Updated:", checkSum)

            # if counter value is odd value, just add the value to the checksum
            else:
                # print(checkSum)
                # print(int(creditNo[i]))
                checkSum = checkSum + int(creditNo[i])
                # print("Updated", checkSum)

        # increment the counter to track the position
        counter = counter + 1

    # print("Finally", checkSum)

    if checkSum % 10 == 0:
        return True

    return False

# Find the credit card type


def findCreditCardType(creditNo):
    if len(creditNo) == 15 and (creditNo[0:2] in ["34", "37"]):
        print("AMEX")
    elif len(creditNo) == 16 and (creditNo[0:2] in ["51", "52", "53", "54", "55"]):
        print("MASTERCARD")
    elif len(creditNo) in [13, 16] and creditNo[0] == "4":
        print("VISA")
    else:
        print("INVALID")


def main():

    while (True):
        creditNo = get_string("Enter credit card number: ")
        if (creditNo.isnumeric()):
            break

    isCheckSumValid = is_checksum_valid(creditNo)

    if (isCheckSumValid):
        findCreditCardType(creditNo)
    else:
        print("INVALID")


# Find the sum of the digits of a number
def findSumOfDigits(twiceOfCurrentLastDigit):
    sumOfDigits = 0

    while (twiceOfCurrentLastDigit > 0):
        sumOfDigits = sumOfDigits + round(twiceOfCurrentLastDigit % 10)
        twiceOfCurrentLastDigit = twiceOfCurrentLastDigit // 10

    return sumOfDigits


main()
