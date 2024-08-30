from pakuri import Pakuri


class Pakudex:
    def __init__(self):
        self.pakudex = []
        print("Welcome to Pakudex: Tracker Extraordinaire!")
        self.main_menu()
    def main_menu(self):
        running = True
        while running:
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
            if action == 1: # list pakuri
                names = self.get_species_list()
                if not names:
                    print("No Pakuri currently in the Pakudex!")
                else:
                    print("\nPakuri in Pakudex:")
                    for paku, i in zip(names, range(1, len(self.pakudex) + 1)):
                        print(f"{i}. {paku}")
                self.main_menu()
            if action == 2: # show pakuri
                species = input("Enter the name of the species to display: ")
                if species in self.get_species_list():
                    print(f"\nSpecies: {species}")
                    print(f"Level: {str(self.get_stats(species)[0])}")
                    print(f"CP: {str(self.get_stats(species)[1])}")
                    print(f"HP: {str(self.get_stats(species)[2])}")
                else:
                    print("Error: No such Pakuri!")
                self.main_menu()
            if action == 3: # add pakuri
                species = input("Species: ")
                if (self.get_species_list()) and (species in self.get_species_list()): # utilizes short-circuiting to check first if the list is not none to prevent error
                    print("Error: Pakudex already contains this species!")
                    break
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
            if action == 4: # remove pakuri
                remove = input("Enter the name of the Pakuri to remove: ")
                removed = self.remove_pakuri(remove)
                if removed:
                    self.pakudex.remove(0) # how can i actually impliment remove function
            if action == 5: # evolve pakuri
                evolve = input("Enter the name of the Pakuri to evolve: ")
                evolved = self.evolve_species(evolve)
                if evolved:
                    self.pakudex

            if action == 7: # exit program
                running = False



    def get_species_list(self) -> list[str]:
        if len(self.pakudex) == 0:
            return None
        return [x.get_species() for x in self.pakudex]

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
            print(f"Pakuri {species} evolved.")
            for pakuri in self.pakudex:
                if pakuri.get_species() == species:
                    pakuri.set_attack(pakuri.get_attack()+1)
                    # impliment for level
            return True
        else:
            print("Error: No such Pakuri!")
            return False


    def get_stats(self,species:str):
        if species not in self.get_species_list():
            return None
        for i in self.pakudex:
            if i.get_species() == species:
                return [1] # returns in order [level,cp,hp]





def main():
    p = Pakudex()
    p.main_menu()






if __name__ == "__main__":
    main()
