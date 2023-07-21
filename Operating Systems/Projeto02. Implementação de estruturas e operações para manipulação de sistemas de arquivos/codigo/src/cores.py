""" 
###################### CORES ######################
AUTORES:
    - Breno Farias da Silva             RA: 2300516
    - Felipe Archanjo da Cunha Mendes   RA: 2252740
    - Pamella Lissa Sato Tamura         RA: 2254107
    
DEFINIÇÃO:
    - Classe para busca de cores

"""
class Cores:
    """
    Classe para cores
    """
    def __init__(self):
        self.fonte = {
            'PRETO': '\033[1;30m',
            'VERMELHO': '\033[1;31m',
            'VERDE': '\033[1;32m',
            'AMARELO': '\033[1;33m',
            'AZUL': '\033[1;34m',
            'MAGENTA': '\033[1;35m',
            'CIANO': '\033[1;36m',
            'CINZA_CLARO': '\033[1;37m',
            'CINZA_ESCURO': '\033[1;90m',
            'VERMELHO_CLARO': '\033[1;91m',
            'VERDE_CLARO': '\033[1;92m',
            'AMARELO_CLARO': '\033[1;93m',
            'AZUL_CLARO': '\033[1;94m',
            'MAGENTA_CLARO': '\033[1;95m',
            'CIANO_CLARO': '\033[1;96m',
            'BRANCO': '\033[1;97m',
            'NEGRITO': '\033[1m',
            'INVERTER': '\033[7m',
            'RESET': '\033[0m'
        }

        self.fundo = {
            'PRETO': '\033[1;40m',
            'VERMELHO': '\033[1;41m',
            'VERDE': '\033[1;42m',
            'AMARELO': '\033[1;43m',
            'AZUL': '\033[1;44m',
            'MAGENTA': '\033[1;45m',
            'CIANO': '\033[1;46m',
            'CINZA_CLARO': '\033[1;47m',
            'CINZA_ESCURO': '\033[1;100m',
            'VERMELHO_CLARO': '\033[1;101m',
            'VERDE_CLARO': '\033[1;102m',
            'AMARELO_CLARO': '\033[1;103m',
            'AZUL_CLARO': '\033[1;104m',
            'MAGENTA_CLARO': '\033[1;105m',
            'CIANO_CLARO': '\033[1;106m',
            'BRANCO': '\033[1;107m'
        }

        