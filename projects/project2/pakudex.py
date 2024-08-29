from pakuri import Pakuri


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
        action = int(input("What would you like to do? "))
        if action == 1:
            a = self.get_species_list()
            if not a:
                print("No Pakuri currently in the Pakudex!")
            else:
                print("\nPakuri in Pakudex:")
                for paku, i in self.a, range(1, len(self.pakudex) + 1):
                    print(f"{i}. {paku.get_species()}")
            self.main_menu()

    def get_species_list(self) -> list[str]:
        if len(self.pakudex) == 0:
            return None
        return [x.get_species() for x in self.pakudex]

    def get_stats(self,species:str):
        if species not in self.get_species_list():
            return None
        for i in self.pakudex:
            if i.get_species() == species:
                return [i.]





def main():
    return 0






if __name__ == "__main__":
    main()
