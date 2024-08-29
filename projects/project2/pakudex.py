from pakuri import Pakuri
import random

random.randint()
class Pakudex:
    def __init__(self):
        self.pakudex = []
        print("Welcome to Pakudex: Tracker Extraordinaire!")
        self.main_menu()
    def main_menu(self):
        print("\nPakudex Main Menu")
        print("---------------------")
        print("1. List Pakuri")
        print("2. Show Pakuri")
        print("3. Add Pakuri")
        print("4. Remove Pakuri")
        print("5. Evolve Pakuri")
        print("6. Sort Pakuri")
        print("7. Exit")
        print("")
        action = input("What would you like to do? ")

    def get_species_list(self) -> list[str]:
        if len(self.pakudex) == 0:
            print("No Pakuri currently in the Pakudex!")
            self.main_menu()
            return None

p = Pakudex()
p.get_species_list()

def main():
    return 0






if __name__ == "__main__":
    main()
