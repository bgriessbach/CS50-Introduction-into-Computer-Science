import cs50
import math

def main():
    #enter number
    while True:
        print ("Number:", end="")
        number = cs50.get_float()
        if number>0:
            break
        
    #count numbers entered
    digits= int(math.log10(number))+1
    
    #get first 2 digits for final type
    first_digits=get_first_digits(number, digits)
    
    #checksum test
    result=checksum(number)
   
    #decide type of Card and print it
    get_result(result, first_digits)

def get_first_digits(number, digits):
    first_digits=number
    while True:
        first_digits//=10
        digits-=1
        if digits==2:
            break
    return first_digits

def checksum(number):
    digit_sum=number
    sum_product=0
    sum_rest=0
    
    while digit_sum>0:
        digit_sum//=10
        product=(digit_sum% 10)*2
        if product>9:
            temp=product%10
            product//=10
            product=temp+(product%10)
        sum_product=product+sum_product
        digit_sum//=10
    
    while number>0:
        sum_rest+=number%10
        number//=100
    result=(int)(sum_rest+sum_product)%10
    return result

def get_result(result, first_digits):
    if result!=0:
        type="INVALID"
    elif first_digits%100==34 or first_digits%100==37:
        type="AMEX"
    elif first_digits%100 in range (51, 51+5):
        type="MASTERCARD"
    elif first_digits//10==4:
        type= "VISA"
    else:
        type="INVALID"
    print("{}".format(type))

if __name__ == "__main__":
    main()
