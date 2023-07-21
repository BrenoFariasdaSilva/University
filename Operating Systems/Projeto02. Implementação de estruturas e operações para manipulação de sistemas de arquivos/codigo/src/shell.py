""" 

###################### Fat Shell ######################
AUTORES:
    - Breno Farias da Silva             RA: 2300516
    - Felipe Archanjo da Cunha Mendes   RA: 2252740
    - Pamella Lissa Sato Tamura         RA: 2254107
    
DEFINIÇÃO:
    - Shell do programa FAT32.

METODOS:
    - info: exibe informações do disco e da FAT.
    - cluster <num>: exibe o conteúdo do bloco num no formato texto.
    - pwd: exibe o diretório corrente (caminho absoluto).
    - attr <file | dir>: exibe os atributos de um arquivo (file) ou diretório (dir).
    - cd <path>: altera o diretório corrente para o definido como path.
    - touch <file>: cria o arquivo file com conteúdo vazio.
    - mkdir <dir>: cria o diretório dir vazio.
    - rm <file>: remove o arquivo file do sistema.
    - rmdir <dir>: remove o diretório dir, se estiver vazio.
    - cp <source_path> <target_path>: copia um arquivo de origem (source_path) para destino (target_path).
    - mv <source_path> <target_path>: move um arquivo de origem (source_path) para destino (target_path).
    - rename <file> <newfilename> : renomeia arquivo file para newfilename.
    - ls: listar os arquivos e diretórios do diretório corrente.
    
"""


from src.fat32 import *
from src.cores import *
from src.utils import *

class FatShell:
    def __init__(self, filename):
        self.cores = Cores()
        self.fat32 = Fat32(filename)
        self.caminho_atual = self.fat32.root_directory.current_path

        self.comandos = {}
        self.comandos['info'] = self.info
        self.comandos['cluster'] = self.cluster
        self.comandos['pwd'] = self.pwd
        self.comandos['attr'] = self.attr
        self.comandos['cd'] = self.cd
        self.comandos['touch'] = self.touch
        self.comandos['mkdir'] = self.mkdir
        self.comandos['rm'] = self.rm
        self.comandos['rmdir'] = self.rmdir
        self.comandos['cp'] = self.cp
        self.comandos['mv'] = self.mv
        self.comandos['rename'] = self.rename
        self.comandos['ls'] = self.ls
        self.comandos['quit'] = self.quit
        self.comandos['help'] = self.help
        self.comandos['clear'] = self.clear

    def info(self, args):                   # OK
        self.fat32.info()

    def cluster(self, args):                # OK
        pos_cluster = int(args[0])
        self.fat32.cluster(pos_cluster)

    def pwd(self, args):                    # OK
        self.fat32.pwd()

    def attr(self, args):                   # OK
        self.fat32.attr(args[0])

    def cd(self, args):                     # OK
        self.fat32.cd(args[0])
        self.caminho_atual = self.fat32.root_directory.current_path

    def touch(self, args):                  # OK
        self.fat32.touch(args[0])

    def mkdir(self, args):                  # OK
        self.fat32.mkdir(args[0])

    def rm(self, args):                     # OK
        self.fat32.rm(args[0])

    def rmdir(self, args):                  # OK
        self.fat32.rmdir(args[0])

    def cp(self, args):
        self.fat32.cp(args[0], args[1])

    def mv(self, args):
        self.fat32.mv(args[0], args[1])

    def rename(self, args):                 # OK
        self.fat32.rename(args[0], args[1])

    def ls(self, args):                     # OK
        self.fat32.ls()

    def clear(self, args):                  # OK
        self.fat32.clear()

    def quit(self, args):                   # OK
        exit()

    def help(self, args):                   # OK
        self.fat32.help()

    def run(self, args):
        if args[0] in self.comandos:
            self.comandos[args[0]](args[1:])
        else:
            print_error("Comando não encontrado.")