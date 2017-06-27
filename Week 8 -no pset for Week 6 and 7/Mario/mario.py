import cs50

while True:
    print ("Height:", end="")
    height = cs50.get_int()
    if height>0 and height<25:
        break
    
for row in range (height):
    for left_space in range (height-row-1):
        print(" ", end="")
    for left_hash in range(row+1):
        print("#", end="")
    for right_space in range (2):
        print (" ", end="")
    for right_hash in range(row+1):
        print("#", end="")
    print(" ")


