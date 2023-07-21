""" 
###################### Projeto 02 ######################
DESCRIÇÃO:
    - Implementação de Sistema de Arquivos FAT32

DISCIPLINA:
    - Sistemas Operacionais

PROFESSOR:
    - Rodrigo Campiolo

AUTORES:
    - Breno Farias da Silva             RA: 2300516
    - Felipe Archanjo da Cunha Mendes   RA: 2252740
    - Pamella Lissa Sato Tamura         RA: 2254107

DATA:
    - 24/06/2022
    
"""

from src.boot_sector import *
from src.fat_table import *
from src.shell import *
from src.cores import *

filename = "./imagem/myimagefat32.img"


def main():
    """
    Método principal do programa.
    """

    shell = FatShell(filename)
    cores = Cores()

    while True:
        args = input(
            cores.fonte['MAGENTA'] + "fatshell:" +
            cores.fonte['AZUL'] + "[img" + shell.caminho_atual + "]" +
            cores.fonte['VERDE'] + "$ " + cores.fonte['RESET']).split()

        shell.run(args)
        


if __name__ == "__main__":
    main()
    