"""
###################### Root Directory ######################
AUTORES:
    - Felipe Archanjo da Cunha Mendes   RA: 2252740
    - Breno Farias da Silva             RA: 2300516
    - Pamella Lissa Sato Tamura         RA: 2254107
    
DEFINIÇÃO:
    - Estrutura que representa o diretório raiz do disco.

PRINCIPAIS ATRIBUTOS:
    - filename: nome da imagem do disco.
    - boot_sector: classe que representa o boot sector do disco.
    - root_pos: posição do diretório raiz no disco.
    - root_path: caminho atual do diretório raiz.
    - current_pos: posição atual no disco.
    - current_path: caminho atual no disco.
    - dir_hierarchy: hierarquia de diretórios do disco.

"""

from src.boot_sector import *

class RootDirectory:
    """
    Classe que representa o diretório raiz do disco.
    """
    def __init__(self, filename, boot_sector, root_pos):
        """
        Construtor da classe.
        """
        self.filename = filename
        self.boot_sector = BootSector(filename)

        self.root_pos = root_pos
        self.root_path = "/"

        self.current_pos = self.root_pos
        self.current_path = self.root_path

        self.dir_hierarchy = [(self.root_pos, self.root_path)]

    def __str__(self):
        """
        Método que retorna uma string que representa o objeto.
        """
        return "RootDirectory"