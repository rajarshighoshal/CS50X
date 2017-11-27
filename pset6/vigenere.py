import cs50
import sys

# checking for porper commmnd line argument
if len(sys.argv) != 2:
    print("Usage: python vigenere.py k")
    exit(1)
# checking if command line argument is made of alphabetical characters only
if not sys.argv[1].isalpha():
    print("Usage: python vigenere.py k")
    exit(2)

# getting plintext from user
print("Plaintext: ", end = "")
ptxt = cs50.get_string()

# enciphering process
key = sys.argv[1]
ciphertext = ""
# length of the key
keylen = len(key)
# looping through each word in  plaintext
countAlpha = 0
for c in ptxt:
    if c.isalpha():
        # variable to access key's characters properly
        j = countAlpha % keylen
        # if character is upper
        if c.isupper():
            ciphertext += chr((ord(c) - ord("A") + ord(key[j]) - ord("A" if key[j].isupper() else "a")) % 26 + ord("A"))
        # if character is lower
        else:
            ciphertext += chr((ord(c) - ord("a") + ord(key[j]) - ord("A" if key[j].isupper() else "a")) % 26 + ord("a"))
            
        countAlpha += 1
    else:
        ciphertext += c

# output
print("Ciphertext: {}".format(ciphertext))