def start():
    print("Enter 2 Integers to get their modulo, if you enter a float the decimal will get ignored")
    n1 = int(input("Enter a Num: "))
    n2 = int(input("Enter another Num: "))
    if type(n1) != int or type(n2) != int :
        print("Please enter a valid number")
        start()
    elif n2 == 0.0:
        print("Can't devide by Zero!")
    else:
        print("Result : " + str(n1-(n1//n2)*n2))
    nxt = input("Q to stop, R to restart : ").lower()
    if nxt == "r":
        start()
    elif nxt == "q":
        quit()
    else:
        start()
start()