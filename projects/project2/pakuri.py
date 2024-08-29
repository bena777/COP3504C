

class Pakuri:
    def __init__(self,species:str,level:int):
        self.__species = species
        self.__level = level
        self.__attack = (len(species) * 7 + 11) % 16
        self.__defense = (len(species) * 5 + 17) % 16
        self.__stamina = (len(species) * 6 + 13) % 16

    def get_species(self) -> str:
        return self.__species

    def get_attack(self) -> int:
        return self.__attack

    def get_defense(self) -> int:
        return self.__defense

    def get_stamina(self) -> int:
        return self.__stamina

    def set_attack(self, new_attack: int):
        self.__attack = new_attack





