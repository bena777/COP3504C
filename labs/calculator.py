import math

# Lab 01, Calculator, By Ben Adelman
# Grade: 11/11

def main():
    result = 0.0
    result = 0.0
    result = 0.0
    result_sum = 0
    calculations = 0
    going = True
    average_last = False
    while going:
        if not average_last:
            print("Current Result: "+str(result))
            print("\nCalculator Menu")
            print("---------------")
            print("0. Exit Program")
            print("1. Addition")
            print("2. Subtraction")
            print("3. Multiplication")
            print("4. Division")
            print("5. Exponentiation")
            print("6. Logarithm")
            print("7. Display Average")
        choice = int(input("\nEnter Menu Selection: "))
        while (choice > 7) or (choice < 0):
            print("\nError: Invalid selection!")
            choice = int(input("\nEnter Menu Selection: "))
        if choice == 0:
            print("\nThanks for using this calculator. Goodbye!")
            going = False
        elif choice == 7:
            if calculations == 0:
                print("\nError: No calculations yet to average!")
            else:
                print("\nSum of calculations: "+str(result_sum))
                print("Number of calculations: "+str(calculations))
                print("Average of calculations: "+str((result_sum/calculations).__round__(2)))
            average_last = True
        else:
            op1 = input("Enter first operand: ")
            op2 = input("Enter second operand: ")
            if op1 == "RESULT":
                op1 = result
            if op2 == "RESULT":
                op2 = result
            op1 = float(op1)
            op2 = float(op2)
            if choice == 1:
                result = op1+op2
            elif choice == 2:
                result = op1-op2
            elif choice == 3:
                result = op1*op2
            elif choice == 4:
                result = op1/op2
            elif choice == 5:
                result = op1**op2
            elif choice == 6:
                result = math.log(op2,op1)
            result_sum+=result
            calculations+=1
            average_last = False
            print("")



if __name__ == "__main__":
    main()
