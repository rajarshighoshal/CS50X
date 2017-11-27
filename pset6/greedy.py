import cs50

# getting input from user
while True:
    print("O hai! How much change is owed?")
    balance = cs50.get_float()
    if balance > 0:
        break

# rounding balance
balance = round(balance * 100)

# coins 
q = 25
d = 10
n = 5
p = 1

# counting variable
count = 0

# 25 cents count
count += balance // q
balance = balance % q

# 10 cents count
count += balance // d
balance = balance % d

# 5 cents count
count += balance // n
balance = balance % n

# 1 cents count
count += balance // p

# output
print(count)