""" 
###################### AUTORES ######################
    - Breno Farias da Silva             RA: 2300516
    - Felipe Archanjo da Cunha Mendes   RA: 2252740
    - Pamella Lissa Sato Tamura         RA: 2254107

###################### FAT32Table ######################
DEFINIÇÃO:
    - Classe que representa a tabela FAT

ESTRUTURAS:
    - filename: nome da imagem do disco.
    - boot_sector: classe que representa o boot sector do disco.
    - pos: posição da tabela FAT

"""

import struct


class Fat32Table:
    """
    Classe que representa a tabela FAT do disco.
    """
    def __init__(self, filename, boot_sector, pos):
        """
        Construtor da classe.
        """
        self.filename = filename
        self.boot_sector = boot_sector
        self.pos = pos

    def __str__(self):
        """
        Método que retorna uma string que representa o objeto.
        """
        clusters = []
        with open(self.filename, 'rb') as f:
            f.seek(self.pos)
            for i in range(self.boot_sector.SectorsPerFAT32):
                clusters.append(struct.unpack('<I', f.read(4))[0])
        return str(clusters)
