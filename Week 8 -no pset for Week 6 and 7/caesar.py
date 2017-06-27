import cs50
import sys

def main():
    #pass in key and plaintext
    if len(sys.argv)!=2:
        print("Please enter one non-negative number")
        exit(1)
    print("plaintext:", end="")
    plaintext=cs50.get_string()
    print("ciphertext:", end="")
    
    #cipher text
    if plaintext!=None:
        key=int(sys.argv[1])
        cipher_text(plaintext, key)


def cipher_text(plaintext, key):
    for i in plaintext:
            
            if 65<=ord(i)<=90:
                letter=ord(i)
                letter-=65
                letter=(letter+key)%26
                letter+=65
                print("{}".format(chr(letter)), end="")
            elif 97<=ord(i)<=122:
                letter=ord(i)
                letter-=97
                letter=(letter+key)%26
                letter+=97
                print("{}".format(chr(letter)), end="")
            else:
                print("{}".format(i), end="")
    print()

if __name__ == "__main__":
    main()
