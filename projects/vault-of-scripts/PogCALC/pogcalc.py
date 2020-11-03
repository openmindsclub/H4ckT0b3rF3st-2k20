n1 = float(input("enter a num : "))
op = input("enter the operation : + , - , * , / : ")
n2 = float(input("Enter another num : "))

def calc():
    if n1 !=float and n2 != float:
        print("Enter numbers next time!")
    else:
        if op == "+":
            print("the result is " + str(n1+n2))
        elif op == "-":
            print("the result is " + str(n1-n2))
        elif op == "*":
            print("the result is " + str(n1*n2))
        elif op == "/":
            if n2 == 0.0 :
                print("You can't devide by 0")
            else:
                print("the result is " + str(n1/n2))
        else:
            print("not a valid operator")
calc()
so = input("Enter R to restart or Stop to stop : ").lower()
if so == "r":
    calc()
elif so == "stop":
    quit()