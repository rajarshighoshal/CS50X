import cs50

# getting height from user where height >= 0 and <= 23
while True:
    print("Height: ", end = "")
    height = cs50.get_int();
    if height >= 0 and height < 24:
        break


# printing the pyramid
# printing each line
for i in range(height):
    # printing first block of pyramid
    # for space
    for j in range(height - (i + 1)):
        print(" ", end = "")
    # for #
    for j in range(i + 1):
        print("#", end = "")
    #printing space
    print(" ", end = "")
    #printing second block of pyramid
    for j in range(i + 1):
        print("#", end = "")
    
    # printing new line
    print("")
    
    
