from cs50 import get_float

while (True):
    cash = get_float("Change: ")
    if (cash > 0.0):
        break

count = 0
while (cash > 0.0):
    if cash >= 0.25:
        cash = round(cash - 0.25, 2)
        count = count + 1
        # print("0.25",  count, cash)
    elif cash >= 0.10:
        cash = round(cash - 0.10, 2)
        count = count + 1
        # print("0.10", count, cash)
    elif cash >= 0.05:
        cash = round(cash - 0.05, 2)
        count = count + 1
        # print("0.05", count, cash)
    else:
        cash = round(cash - 0.01, 2)
        count = count + 1
        # print("0.01", count, cash)

print(count)
