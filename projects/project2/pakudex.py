from pakuri import Pakuri


class Pakudex:
    def __init__(self):
        self.pakudex = []
        print("Welcome to Pakudex: Tracker Extraordinaire!")
        self.going = True
        self.main_menu()
    def main_menu(self):
        try:
            while self.going:
                print("\nPakudex Main Menu")
                print("-----------------")
                print("1. List Pakuri")
                print("2. Show Pakuri")
                print("3. Add Pakuri")
                print("4. Remove Pakuri")
                print("5. Evolve Pakuri")
                print("6. Sort Pakuri")
                print("7. Exit")
                print("")
                action = input("What would you like to do? ")
                try:
                    action = int(action)
                    if (action > 7) or (action < 1):
                        action = action + " " # throws intentional error
                    if action == 1: # list pakuri
                        names = self.get_species_list()
                        if not names:
                            print("No Pakuri currently in the Pakudex!")
                        else:
                            print("\nPakuri in Pakudex:")
                            for paku, i in zip(names, range(1, len(self.pakudex) + 1)):
                                print(f"{i}. {paku}")
                    elif action == 2: # show pakuri
                        species = input("Enter the name of the species to display: ")
                        if (self.get_species_list()) and (species in self.get_species_list()):
                            print(f"\nSpecies: {species}")
                            print(f"Level: {str(self.get_stats(species)[0])}")
                            print(f"CP: {str(self.get_stats(species)[1])}")
                            print(f"HP: {str(self.get_stats(species)[2])}")
                        else:
                            print("Error: No such Pakuri!")
                    elif action == 3: # add pakuri
                        species = input("Species: ")
                        if (self.get_species_list()) and (species in self.get_species_list()): # utilizes short-circuiting to check first if the list is not none to prevent error
                            print("Error: Pakudex already contains this species!")
                            continue
                        global level_input
                        level_input = input("Level: ")
                        again = self.add_pakuri(species,level_input)
                        while not again:
                            if (self.get_species_list()) and (species in self.get_species_list()):
                                species = input("Species: ")
                            else:
                                level_input = input("Level: ")
                            again = self.add_pakuri(species,level_input)
                        print(f"Pakuri species {species} (level {str(level_input)}) added!")
                    elif action == 4: # remove pakuri
                        remove = input("Enter the name of the Pakuri to remove: ")
                        self.remove_pakuri(remove)
                    elif action == 5: # evolve pakuri
                        evolve = input("Enter the name of the species to evolve: ")
                        self.evolve_species(evolve)
                    elif action == 6: # sort pakuri
                        if self.get_species_list():
                            self.sort_pakuri()
                        print("Pakuri have been sorted!")
                    elif action == 7: # exit program
                        print("Thanks for using Pakudex! Bye!")
                        self.going = False
                        break
                except:
                    print("Unrecognized menu selection!")
        except:
            pass


    def get_species_list(self) -> list[str]:
        if len(self.pakudex) == 0:
            return None
        return [x.get_species() for x in self.pakudex]

    def sort_pakuri(self):
        self.pakudex = sorted(self.pakudex, key=lambda p: p.get_species())  # help from https://stackoverflow.com/questions/403421/how-do-i-sort-a-list-of-objects-based-on-an-attribute-of-the-objects
    def add_pakuri(self,species:str,level) -> bool:
        try:
            level = int(level)
            if level >= 0:
                self.pakudex.append(Pakuri(species,level))
                return True
            else:
                print("Level cannot be negative.")
                return False
        except:
            print("Invalid level!")
            return False

    def remove_pakuri(self, species):
        if (self.get_species_list()) and (species in self.get_species_list()):
            print(f"Pakuri {species} removed.")
            for pakuri in self.pakudex:
                if pakuri.get_species() == species:
                    self.pakudex.remove(pakuri)
            return True
        else:
            print("Error: No such Pakuri!")
            return False

    def evolve_species(self,species):
        if (self.get_species_list()) and (species in self.get_species_list()):
            print(f"{species} has evolved!")
            for pakuri in self.pakudex:
                if pakuri.get_species() == species:
                    pakuri.set_attack(pakuri.get_attack()+1)
                    pakuri.level = pakuri.level*2
            return True
        else:
            print("Error: No such Pakuri!")
            return False


    def get_stats(self,species:str):
        if species not in self.get_species_list():
            return None
        for i in self.pakudex:
            if i.get_species() == species:
                return [i.level,i.cp,i.hp] # returns in order [level,cp,hp]


def main():
    p = Pakudex()
    p.main_menu()


if __name__ == "__main__":
    main()
