"""
###################### FAT32 ######################
AUTORES:
    - Felipe Archanjo da Cunha Mendes   RA: 2252740
    - Breno Farias da Silva             RA: 2300516
    - Pamella Lissa Sato Tamura         RA: 2254107

DEFINIÇÃO:
    - Classe que representa o sistema de arquivos FAT32

PRINCIPAIS ATRIBUTOS:
    - BootSector: classe que representa o boot sector do disco.
    - Fat32Table_0: classe que representa a FAT32 do disco.
    - Fat32Table_1: classe que representa a FAT32 do disco.
    - RootDirectory: classe que representa o diretório raiz do disco.

"""

import struct
from src.boot_sector import *
from src.fat_table import *
from src.root_directory import *
from src.utils import *
from src.cores import *
from datetime import datetime
import os
from time import sleep

class Fat32:
    """
    Classe que representa o FAT32 do disco.
    """
    def __init__(self, filename):
        """
        Construtor da classe.
        """

        self.cores = Cores()

        self.filename = filename

        # Boot Sector
        self.boot_sector = BootSector(self.filename)

        # Fat0
        self.pos_fat0 = self.boot_sector.ReservedSectors * self.boot_sector.BytesPerSector
        self.fat32_table_0 = Fat32Table(self.filename, self.boot_sector, self.pos_fat0)

        # Fat1
        self.pos_fat1 = self.pos_fat0 + self.boot_sector.SectorsPerFAT32 * self.boot_sector.BytesPerSector
        self.fat32_table_1 = Fat32Table(self.filename, self.boot_sector, self.pos_fat1)

        # Root Directory
        self.pos_root_dir = self.pos_fat1 + self.boot_sector.SectorsPerFAT32 * self.boot_sector.BytesPerSector
        self.root_directory = RootDirectory(self.filename, self.boot_sector, self.pos_root_dir)

    def info(self):
        """
        info: exibe informações do disco e da FAT.
        """
        print(
            f"{'OemName ':-<25} {self.boot_sector.OemName}\n" +
            f"{'BytesPerSector ':-<25} {self.boot_sector.BytesPerSector}\n" +
            f"{'SectorsPerCluster ':-<25} {self.boot_sector.SectorsPerCluster}\n" +
            f"{'ReservedSectors ':-<25} {self.boot_sector.ReservedSectors}\n" +
            f"{'NumberOfFATs ':-<25} {self.boot_sector.NumberOfFATs}\n" +
            f"{'MaxRootDirEntries ':-<25} {self.boot_sector.MaxRootDirEntries}\n" +
            f"{'NumberOfSectors16 ':-<25} {self.boot_sector.NumberOfSectors16}\n" +
            f"{'MediaDescriptor ':-<25} {self.boot_sector.MediaDescriptor}\n"
            f"{'SectorsPerFAT16 ':-<25} {self.boot_sector.SectorsPerFAT16}\n"
            f"{'SectorsPerTrack ':-<25} {self.boot_sector.SectorsPerTrack}\n"
            f"{'HeadsPerCylinder ':-<25} {self.boot_sector.HeadsPerCylinder}\n"
            f"{'NumHiddenSectors ':-<25} {self.boot_sector.NumHiddenSectors}\n"
            f"{'NumberOfSectors32 ':-<25} {self.boot_sector.NumberOfSectors32}\n"
            f"{'SectorsPerFAT32 ':-<25} {self.boot_sector.SectorsPerFAT32}\n"
            f"{'flags ':-<25} {self.boot_sector.flags}\n"
            f"{'version ':-<25} {self.boot_sector.version}\n"
            f"{'RootCluster ':-<25} {self.boot_sector.RootCluster}\n"
            f"{'InfoSector ':-<25} {self.boot_sector.InfoSector}\n"
            f"{'BootBackupStart ':-<25} {self.boot_sector.BootBackupStart}\n"
            f"{'Reserved ':-<25} {self.boot_sector.Reserved}\n"
            f"{'DriveNumber ':-<25} {self.boot_sector.DriveNumber}\n"
            f"{'Unused ':-<25} {self.boot_sector.Unused}\n"
            f"{'ExtBootSignature ':-<25} {self.boot_sector.ExtBootSignature}\n"
            f"{'SerialNumber ':-<25} {self.boot_sector.SerialNumber}\n"
            f"{'VolumeLabel ':-<25} {self.boot_sector.VolumeLabel}\n"
            f"{'FileSystemLabel ':-<25} {self.boot_sector.FileSystemLabel}\n"
            f"{'EndOfSectorMarker ':-<25} {self.boot_sector.EndOfSectorMarker}\n"
        )
    

    def help(self):
        """
        help: exibe a ajuda do programa.
        """
        print(
            f"{'info ':-<25} Exibe informações do disco e da FAT.\n" +
            f"{'cluster <num>':-<25} Exibe o conteúdo do bloco num no formato texto.\n"
            f"{'pwd':-<25} Exibe o diretório corrente (caminho absoluto).\n" +
            f"{'attr <file | dir>':-<25} Exibe os atributos de um arquivo (file) ou diretório (dir).\n"
            f"{'cd <path>':-<25} Altera o diretório corrente para o definido como path.\n"
            f"{'touch <file>':-<25} Cria o arquivo file com conteúdo vazio.\n"
            f"{'mkdir <dir>':-<25} Cria o diretório dir vazio.\n"
            f"{'rm <file>':-<25} Remove o arquivo file do sistema.\n"
            f"{'rmdir <dir>':-<25} Remove o diretório dir, se estiver vazio.\n"
            f"{'cp <s_path> <t_path>':-<25} Copia um arquivo de origem (source_path) para destino (target_path).\n"
            f"{'mv <s_path> <t_path>':-<25} Move um arquivo de origem (source_path) para destino (target_path).\n"
            f"{'rename <file> <newName>':-<25} Renomeia arquivo file para newfilename.\n"
            f"{'ls':-<25} Listar os arquivos e diretórios do diretório corrente.\n"
            f"{'quit':-<25} Sai do programa.\n"
            f"{'clear':-<25} Limpa a tela.\n"
            f"{'help':-<25} Exibe a lista de comandos do sistema.\n"
        )
    
    def cluster(self, cluster_number):
        """
        cluster <num>: exibe o conteúdo do bloco num no formato texto.
        """
        if cluster_number < 0 or cluster_number > self.boot_sector.NumberOfSectors32:
            print_error(f"Cluster {cluster_number} não existe.")
            return
            
        with open(self.filename, 'rb') as f:
            f.seek(self.pos_root_dir - self.boot_sector.RootCluster * self.boot_sector.BytesPerSector + cluster_number * self.boot_sector.BytesPerSector)
            data = f.read(self.boot_sector.BytesPerSector)
            print(data)
    

    def pwd(self):
        """
        pwd: exibe o diretório corrente.
        """
        print(f"{self.root_directory.current_path}")
    

    def attr(self, search_name):
        """
        attr <filename>: exibe o atributo do arquivo.
        """
        # Verificar se tem ./
        if './' in search_name:
            search_name = search_name.replace('./', '')

        requ_file = SearchFile(search_name, self.root_directory.current_pos, self.filename)

        if requ_file:
            # Lê os atributos do arquivo
            with open(self.filename, 'rb') as f:
                # Posicionamento do cursor
                f.seek(requ_file[0] + 32 * requ_file[1])
                # Lê as informações do arquivo
                print("Name: ", f.read(8).decode('utf-8').rstrip('\x00'))
                print("Extension: ", f.read(3).decode('utf-8').rstrip('\x00'))
                print("Attributes: ", struct.unpack('<B', f.read(1))[0])
                print("Reserved: ", struct.unpack('<B', f.read(1))[0])
                print("Creation Time 10ms: ", struct.unpack('<B', f.read(1))[0])
                print("Creation Time: ", struct.unpack('<H', f.read(2))[0])
                print("Creation Date: ", struct.unpack('<H', f.read(2))[0])
                print("Last Access Date: ", struct.unpack('<H', f.read(2))[0])
                print("High Cluster: ", struct.unpack('<H', f.read(2))[0])
                print("Updated Time: ", struct.unpack('<H', f.read(2))[0])
                print("Updated Date: ", struct.unpack('<H', f.read(2))[0])
                print("Low Cluster: ", struct.unpack('<H', f.read(2))[0])
                print("File Size: ", struct.unpack('<I', f.read(4))[0])
                f.close()
        else:
            print_error(f"Arquivo {search_name} não encontrado.")

    def ls(self):
        """
        ls: exibe os arquivos do diretório corrente.
        """
        with open(self.filename, 'rb') as f:
            # Posicionamento do cursor (Diretorio corrente)
            f.seek(self.root_directory.current_pos)

            while True:
                f.seek(f.tell() + 11)

                # Lê o atributo do arquivo
                attr = struct.unpack('<B', f.read(1))[0]

                ## Checar se é long entry
                # Se não houver mais arquivos, sai do loop
                if attr == 0:
                    break
                # Se o arquivo for long entry, pule
                if attr == 0x0F:
                    f.seek(f.tell() - 12 + 32)
                    continue
                
                ## Checa se é arquivo deletado
                if attr == 0xE5:
                    f.seek(f.tell() - 12 + 32)
                    continue
                
                ## Checar se é arquivo
                if attr == 0x20:
                    # Reposiciona o cursor
                    f.seek(f.tell() - 12)
                    # Lê o nome do arquivo
                    name = f.read(8)
                    name = name.replace(b'\x00', b'')
                    name = name.decode('utf-8')
                    name = name.strip()

                    ext = f.read(3)
                    ext = ext.replace(b'\x00', b'')
                    ext = ext.decode('utf-8')
                    ext = ext.strip()
                    ext = ext.lower()

                    # Exibe o nome do arquivo
                    if not ext:
                        print(f"{name}", end='    ')
                    else:
                        print(f"{name}.{ext}", end='    ')
                    # Procura pelo proximo arquivo
                    f.seek(f.tell() - 11 + 32)
                    continue

                ## Checar se é diretório
                if attr == 0x10:
                    # Reposiciona o cursor
                    f.seek(f.tell() - 12)
                    # Lê o nome do arquivo
                    name = f.read(11)
                    name = name.replace(b'\x00', b'')
                    name = name.decode('utf-8')
                    name = name.split()
                    name = "".join(name)
                    # Exibe o nome do arquivo
                    print(
                        cores.fonte['AZUL'] +
                        name +
                        cores.fonte['RESET'], end = '    '
                    )
                    # Procura pelo proximo arquivo
                    f.seek(f.tell() - 11 + 32)
                    continue
            print()
            f.close()


    def cd(self, path):
        """
        cd <path>: altera o diretório corrente.
        """
        # Se for caminho absoluto
        if path[0] == '/':
            # Adiciona os caminhos em uma lista
            paths = path[1:].split('/')
        else:
            # Adiciona os caminhos em uma lista
            paths = path.split('/')

        for p in paths:

            if p == '.':
                continue
            elif p == '..':
                if self.root_directory.current_path == '/':
                    continue
                else:
                    # Remover o último caminho da lista
                    retirado = self.root_directory.dir_hierarchy.pop()

                    # Atualiza o caminho corrente
                    self.root_directory.current_path = self.root_directory.current_path.replace(retirado[1] + '/', '')

                    if self.root_directory.current_path == '/':
                        pos = self.root_directory.root_pos
                    else:
                        # Encontra a quantidade de longEntries
                        q_LE = 0
                        with open(self.filename, 'rb') as f:
                            f.seek(self.root_directory.dir_hierarchy[-1][0] + 11)
                            while True:
                                attr = struct.unpack('<B', f.read(1))[0]
                                if attr == 0:
                                    break
                                if attr == 0x0F:
                                    q_LE += 1
                                    f.seek(f.tell() - 12 + 32)
                                else:
                                    f.seek(f.tell() - 12 + 32)
                            
                        # Atualiza o posicionamento do diretório corrente
                        pos = find_data_pos(
                            self.root_directory.dir_hierarchy[-1][0], 
                            q_LE, 
                            self.pos_root_dir, 
                            self.boot_sector.RootCluster, 
                            self.boot_sector.BytesPerSector, 
                            self.filename)


                    self.root_directory.current_pos = pos
            else:
                # Verificar se o arquivo existe
                requ_file = SearchFile(p, self.root_directory.current_pos, self.filename)

                if requ_file:
                    # Verificar se é diretorio ou arquivo
                    att = get_attr(requ_file[0], requ_file[1], self.filename)

                    if att == 'd':
                        
                        # Adicionar esse caminho da lista de hierarquia de diretorios
                        self.root_directory.dir_hierarchy.append((requ_file[0], p))
                        
                        # Atualizar o caminho corrente
                        if self.root_directory.current_path == '/':
                            self.root_directory.current_path = self.root_directory.current_path + p + '/'
                        else:
                            self.root_directory.current_path = self.root_directory.current_path + p + '/'

                        # Atualizar o posicionamento do diretorio corrente
                        self.root_directory.current_pos = find_data_pos(requ_file[0], requ_file[1], self.pos_root_dir, self.boot_sector.RootCluster, self.boot_sector.BytesPerSector, self.filename)

                    else:
                        print_error(f"{p} não é um diretório.")
                        return

                else:
                    print_error(f"Arquivo {p} não existe.")
                    return
                

    def rename(self, old_name, new_name):
        """
        rename <old_name> <new_name>: renomeia um arquivo.
        """

        # Verificar se tem ./
        if './' in old_name:
            old_name = old_name.replace('./', '')

         # Verificação extra
        if len(new_name) == 1 and new_name[0] == '.':
            print('Nome inválido')
            return

        if new_name[-1] == '.':
            new_name = new_name[:-1]

        # Dividir o nome em nome e extensão
        name_split = new_name.split('.')
        if len(name_split) == 1:
            name = name_split[0]
            ext = ''
            fullName = name
        else:
            ext = name_split[-1]
            name = '.'.join(name_split[:-1])
            fullName = name + '.' + ext

        # Verificar o tamanho do nome do arquivo
        if len(fullName) <= 11:
            if len(name) > 8:
                print_error('Nome do arquivo muito grande.')
                return
            
            if len(ext) > 3:
                print_error('Extensão do arquivo muito grande.')
                return
        else:
            print_error('Nome do arquivo muito grande.')
        
        # Verificar se o arquivo existe
        requ_file = SearchFile(old_name, self.root_directory.current_pos, self.filename)

        if requ_file:
            # Verifica se o arquivo é apenas arquivo
            attr = get_attr(requ_file[0], requ_file[1], self.filename)

            if attr == 'f':
                with open(self.filename, 'rb+') as f:
                    # Posicionamento do cursor (Arquivo de alteração)
                    f.seek(requ_file[0])
                    # Pula os long entries
                    f.seek(f.tell() + 32 * requ_file[1])
                    # Escreve o nome
                    for i in range(8):
                        if i < len(name):
                            f.write(name[i].encode('utf-8'))
                        else:
                            f.write(" ".encode('utf-8'))
                    
                    # Escreve a extensão
                    for i in range(3):
                        if i < len(ext):
                            f.write(ext[i].encode('utf-8'))
                        else:
                            f.write(" ".encode('utf-8'))

                    f.close()

            else:
                print_error("Você não pode renomear um diretório.")
                return
        else:
            print_error("Arquivo não encontrado.")
            return


    def mkdir(self, name):
        """
        mkdir <name>: cria um diretório.
        """
        # Verificar se o diretório existe
        requ_file = SearchFile(name, self.root_directory.current_pos, self.filename)

        if requ_file:
            print_error("Diretório já existe.")
            return

        # Pegar a posição onde o diretorio será criado
        pos_new_dir = find_pos_empty_entry(self.root_directory.current_pos, self.filename)
        
        # Verificar o tamnho do nome do diretorio
        if len(name) > 8:
            print_error("Nome do diretório muito longo.")
            return

        # Procurar o cluster livre
        cluster_free = find_empty_cluster(self.pos_fat0, self.filename)

        # Criar o diretorio
        with open(self.filename, 'rb+') as f:
            # Posicionamento do cursor
            f.seek(pos_new_dir)

            # Nome 8h
            for i in range(8):
                if i < len(name):
                    f.write(name[i].encode('utf-8'))
                else:
                    f.write(b'\x20')

            # Extensão 3h
            f.write(b'\x20\x20\x20')

            # Atributos
            f.write(b'\x10')

            # Reserved 1h
            f.write(b'\x00')

            # CreatedTime10ms 1h
            f.write(b'\x00')

            # Created Time 2h
            f.write(b'\x00\x00')

            # Created Date 2h 
            f.write(b'\x00\x00')

            # Last Accessed Date 2h
            f.write(b'\x00\x00')

            # High Cluster em bytes 2h
            f.write(cluster_free[0])

            # Updated Time 2h
            f.write(b'\x00\x00')

            # Updated Date 2h
            f.write(b'\x00\x00')

            # Low Cluster em bytes 2h
            f.write(cluster_free[1])

            # Size File 4h
            f.write(b'\x00\x00\x00\x00')

            # Posiciona o cursor no cluster livre da FAT_Table_0 e escreve no mesmo
            f.seek(self.pos_fat0 + cluster_free[2] * 4)
            f.write(b'\xFF\xFF\xFF\xFF')

            # Posiciona o cursor no cluster livre da FAT_Table_1 e escreve no mesmo
            f.seek(self.pos_fat1 + cluster_free[2] * 4)
            f.write(b'\xFF\xFF\xFF\xFF')

            ## Cria o diretorio .
            # Posicionamento do cursor
            f.seek(self.pos_root_dir - self.boot_sector.RootCluster * self.boot_sector.BytesPerSector + cluster_free[2] * self.boot_sector.BytesPerSector)
            # Nome 8h (.)
            f.write(b'\x2E\x20\x20\x20\x20\x20\x20\x20')
            # Extensão 3h
            f.write(b'\x20\x20\x20')
            # Atributos
            f.write(b'\x10')
            # Reserved 1h
            f.write(b'\x00')
            # CreatedTime10ms 1h
            f.write(b'\x00')
            # Created Time 2h
            f.write(b'\x00\x00')
            # Created Date 2h 
            f.write(b'\x00\x00')
            # Last Accessed Date 2h
            f.write(b'\x00\x00')
            # High Cluster em bytes 2h
            f.write(cluster_free[0])
            # Updated Time 2h
            f.write(b'\x00\x00')
            # Updated Date 2h
            f.write(b'\x00\x00')
            # Low Cluster em bytes 2h
            f.write(cluster_free[1])
            # Size File 4h
            f.write(b'\x00\x00\x00\x00')

            ## Cria o diretorio ..
            # Pegar o valor do Cluster do diretorio pai
            if self.root_directory.current_path == '/':
                cluster_parent = self.boot_sector.RootCluster

                hex_cluster = hex(cluster_parent)
                # Transformar em 4 bytes
                hex_cluster = hex_cluster[2:]
                hex_cluster = hex_cluster.zfill(8)
                hex_cluster = bytes.fromhex(hex_cluster)
                # Dividir em duas partes
                hex_cluster_high = hex_cluster[0:2]
                hex_cluster_low = hex_cluster[2:4]
                # Inverter
                hex_cluster_high = hex_cluster_high[::-1]
                hex_cluster_low = hex_cluster_low[::-1]

            else:
                while True:
                    # pula o nome do arquivo
                    f.seek(self.root_directory.current_pos + 11)
                    # Lê o atributo do arquivo
                    attr = struct.unpack('<B', f.read(1))[0]
                    # Se o arquivo for um longEntry, pule
                    if attr == 0x0F:
                        f.seek(f.tell() - 12 + 32)
                        continue
                    else:
                        break
                # Pega o cluster do diretorio pai
                f.seek(self.root_directory.current_pos + 20)
                hex_cluster_high = f.read(2)

                # Posiciona o cursor no low cluster e pega seu valor
                f.seek(self.root_directory.current_pos + 26)
                hex_cluster_low = f.read(2)

            # Posicionamento do cursor
            f.seek(self.pos_root_dir - self.boot_sector.RootCluster * self.boot_sector.BytesPerSector + cluster_free[2] * self.boot_sector.BytesPerSector + 32)
            # Nome 8h (..)
            f.write(b'\x2E\x2E\x20\x20\x20\x20\x20\x20')
            # Extensão 3h
            f.write(b'\x20\x20\x20')
            # Atributos
            f.write(b'\x10')
            # Reserved 1h
            f.write(b'\x00')
            # CreatedTime10ms 1h
            f.write(b'\x00')
            # Created Time 2h
            f.write(b'\x00\x00')
            # Created Date 2h
            f.write(b'\x00\x00')
            # Last Accessed Date 2h
            f.write(b'\x00\x00')
            # High Cluster em bytes 2h
            f.write(hex_cluster_high)
            # Updated Time 2h
            f.write(b'\x00\x00')
            # Updated Date 2h
            f.write(b'\x00\x00')
            # Low Cluster em bytes 2h
            f.write(hex_cluster_low)
            # Size File 4h
            f.write(b'\x00\x00\x00\x00')

            f.close()




    def touch(self, name):
        """
        touch <name>: cria um arquivo vazio.
        """

        # Verificação extra
        if len(name) == 1 and name[0] == '.':
            print('Nome inválido')
            return

        if name[-1] == '.':
            name = name[:-1]

        if name[0] == '.':
            name = name[1:]

        # Dividir o nome em nome e extensão
        name_split = name.split('.')
        if len(name_split) == 1:
            name = name_split[0]
            ext = ''
            fullName = name
        else:
            ext = name_split[-1]
            name = '.'.join(name_split[:-1])
            fullName = name + '.' + ext
        

        # Verificar o tamanho do nome do arquivo
        if len(fullName) <= 11:
            if len(name) > 8:
                print_error('Nome do arquivo muito grande.')
                return
            
            if len(ext) > 3:
                print_error('Extensão do arquivo muito grande.')
                return
        else:
            print_error('Nome do arquivo muito grande.')

        # Verificar se o arquivo existe
        requ_file = SearchFile(fullName, self.root_directory.current_pos, self.filename)

        if requ_file:
            print_error("Arquivo já existe.")
            return

        # Pegar a posição onde o arquivo será criado
        pos_new_file = find_pos_empty_entry(self.root_directory.current_pos, self.filename)
        
        # Procurar o cluster livre
        cluster_free = find_empty_cluster(self.pos_fat0, self.filename)

        # Criar o arquivo
        with open(self.filename, 'rb+') as f:
            # Posicionamento do cursor
            f.seek(pos_new_file)

            # Escrita dos atributos
            # Nome 8h
            for i in range(8):
                if i < len(name):
                    f.write(name[i].encode('utf-8'))
                else:
                    f.write(" ".encode('utf-8'))
            
            # Extensão 3h
            for i in range(3):
                if i < len(ext):
                    f.write(ext[i].encode('utf-8'))
                else:
                    f.write(" ".encode('utf-8'))


            # Atributo file 1h
            f.write(b'\x20')

            # Reserved 1h
            f.write(b'\x00')

            # CreatedTime10ms 1h
            f.write(b'\x00')

            # Created Time 2h
            f.write(b'\x00\x00')

            # Created Date 2h 
            f.write(b'\x00\x00')

            # Last Accessed Date 2h
            f.write(b'\x00\x00')

            # High Cluster em bytes 2h
            f.write(cluster_free[0])

            # Updated Time 2h
            f.write(b'\x00\x00')

            # Updated Date 2h
            f.write(b'\x00\x00')

            # Low Cluster em bytes 2h
            f.write(cluster_free[1])

            # Size File 4h
            f.write(b'\x00\x00\x00\x00')

            # Posiciona o cursor no cluster livre da FAT_Table_0 e escreve no mesmo
            f.seek(self.pos_fat0 + cluster_free[2] * 4)
            f.write(b'\xFF\xFF\xFF\xFF')

            # Posiciona o cursor no cluster livre da FAT_Table_1 e escreve no mesmo
            f.seek(self.pos_fat1 + cluster_free[2] * 4)
            f.write(b'\xFF\xFF\xFF\xFF')

            f.close()

    def rm(self, name):
        """
        rm <name>: remove um arquivo.
        """
        # Verificar se tem ., ./nome, .., nome
        if len(name) == 1 and name == '.':
            print_error("Não é possível realizar essa operação.")
            return
        
        if len(name) == 2 and name == '..':
            print_error("Não é possível realizar essa operação.")
            return
        
        if './' in name:
            name = name.replace('./', '')
        
        # Abre o arquivo para escrita
        with open(self.filename, 'rb+') as f:
            # Posicionamento do cursor
            f.seek(self.root_directory.current_pos)

            # Pula os long entries
            f.seek(f.tell() + 32 * self.root_directory.current_pos)

            # Verifica se o arquivo existe
            requ_file = SearchFile(name, self.root_directory.current_pos, self.filename)

            if requ_file:
                # Verifica se o arquivo é apenas arquivo
                attr = get_attr(requ_file[0], requ_file[1], self.filename)

                if attr == 'f':
                    # Posicionamento do cursor (Arquivo de alteração)
                    f.seek(requ_file[0])
                    # Pula os long entries
                    f.seek(f.tell() + 32 * requ_file[1])
                    # Escreve o nome do arquivo
                    for i in range(11):
                        f.write(b'\x00')
                    # Escreve o atributo do arquivo
                    f.write(b'\xE5')

                    # Posiciona o cursor no high cluster e pega seu valor em decimal
                    f.seek(requ_file[0] + 32 * requ_file[1] + 20)
                    high_cluster = f.read(2)
                    high_cluster = int.from_bytes(high_cluster, byteorder='little')

                    # Posiciona o cursor no low cluster e pega seu valor
                    f.seek(requ_file[0] + 32 * requ_file[1] + 26)
                    low_cluster = f.read(2)
                    low_cluster = int.from_bytes(low_cluster, byteorder='little')

                    # Concatena os dois clusters
                    cluster = high_cluster + low_cluster
                    
                    # Lista para armazenar os clusters
                    clusters = []
                    clusters.append(cluster)

                    ## Obtem os clusters do arquivo
                    # Posiciona o cursor no cluster e verifica seu valor
                    f.seek(self.pos_fat0 + cluster * 4)
                    while True:
                        # Pega o valor do cluster
                        cluster_value = f.read(4)
                        cluster_value = int.from_bytes(cluster_value, byteorder='little')
                        # Verifica so valor do cluster
                        if cluster_value == 0x0FFFFFFF or cluster_value == 0xFFFFFFFF:
                            break
                        else:
                            clusters.append(cluster_value)
                            f.seek(self.pos_fat0 + cluster_value * 4)

                    ## Remove o/os cluster/s da fatTable0
                    for c in clusters:
                        # Posiciona o cursor no cluster e verifica seu valor
                        f.seek(self.pos_fat0 + c * 4)
                        # Escreve o valor do cluster (FREE CLUSTER)
                        f.write(b'\x00\x00\x00\x00')
                    
                    ## Remove o/os cluster/s da fatTable1
                    for c in clusters:
                        # Posiciona o cursor no cluster e verifica seu valor
                        f.seek(self.pos_fat1 + c * 4)
                        # Escreve o valor do cluster (FREE CLUSTER)
                        f.write(b'\x00\x00\x00\x00')
                    
                    ## Remove os dados do/s cluster/s
                    for c in clusters:
                        # Posiciona o cursor no cluster e verifica seu valor
                        f.seek(f.seek(self.pos_root_dir - self.boot_sector.RootCluster * self.boot_sector.BytesPerSector + c * self.boot_sector.BytesPerSector))
                        # Limpa o cluster
                        f.write(b'\x00' * self.boot_sector.BytesPerSector)

                    f.close()

                else:
                    print_error("Você não pode remover um diretório.")
                    return
            else:
                print_error("Arquivo não encontrado.")
                return
        
    def rmdir(self, name):
        """
        rmdir <name>: remove um diretório.
        """
        # Verificar se tem ., ./nome, .., nome
        if len(name) == 1 and name == '.':
            print_error("Não é possível realizar essa operação.")
            return
        
        if len(name) == 2 and name == '..':
            print_error("Não é possível realizar essa operação.")
            return
        
        if './' in name:
            name = name.replace('./', '')

        # Abre o arquivo para escrita
        with open(self.filename, 'rb+') as f:
            # Posicionamento do cursor
            f.seek(self.root_directory.current_pos)

            # Pula os long entries
            f.seek(f.tell() + 32 * self.root_directory.current_pos)

            # Verifica se o arquivo existe
            requ_file = SearchFile(name, self.root_directory.current_pos, self.filename)

            if requ_file:
                # Verifica se o arquivo é apenas arquivo
                attr = get_attr(requ_file[0], requ_file[1], self.filename)

                if attr == 'd':
                    # Verificar se o diretório está vazio
                    vazio = dir_is_empty(requ_file[0], requ_file[1], self.pos_root_dir, self.boot_sector.RootCluster, self.boot_sector.BytesPerSector, self.filename)

                    if vazio:
                        # Alterar o atributo do arquivo
                        f.seek(requ_file[0] + 32 * requ_file[1])
                        # Escreve o nome do arquivo
                        for i in range(11):
                            f.write(b'\x00')
                        # Escreve o atributo do arquivo
                        f.write(b'\xE5')

                        # Posiciona o cursor no high cluster e pega seu valor em decimal
                        f.seek(requ_file[0] + 32 * requ_file[1] + 20)
                        high_cluster = f.read(2)
                        high_cluster = int.from_bytes(high_cluster, byteorder='little')

                        # Posiciona o cursor no low cluster e pega seu valor
                        f.seek(requ_file[0] + 32 * requ_file[1] + 26)
                        low_cluster = f.read(2)
                        low_cluster = int.from_bytes(low_cluster, byteorder='little')

                        # Concatena os dois clusters
                        cluster = high_cluster + low_cluster
                        
                        # Lista para armazenar os clusters
                        clusters = []
                        clusters.append(cluster)

                        ## Obtem os clusters do arquivo
                        # Posiciona o cursor no cluster e verifica seu valor
                        f.seek(self.pos_fat0 + cluster * 4)
                        while True:
                            # Pega o valor do cluster
                            cluster_value = f.read(4)
                            cluster_value = int.from_bytes(cluster_value, byteorder='little')
                            # Verifica so valor do cluster
                            if cluster_value == 0x0FFFFFFF or cluster_value == 0xFFFFFFFF:
                                break
                            else:
                                clusters.append(cluster_value)
                                f.seek(self.pos_fat0 + cluster_value * 4)

                        ## Remove o/os cluster/s da fatTable0
                        for c in clusters:
                            # Posiciona o cursor no cluster e verifica seu valor
                            f.seek(self.pos_fat0 + c * 4)
                            # Escreve o valor do cluster (FREE CLUSTER)
                            f.write(b'\x00\x00\x00\x00')
                        
                        ## Remove o/os cluster/s da fatTable1
                        for c in clusters:
                            # Posiciona o cursor no cluster e verifica seu valor
                            f.seek(self.pos_fat1 + c * 4)
                            # Escreve o valor do cluster (FREE CLUSTER)
                            f.write(b'\x00\x00\x00\x00')
                        
                        ## Remove os dados do/s cluster/s
                        for c in clusters:
                            # Posiciona o cursor no cluster e verifica seu valor
                            f.seek(f.seek(self.pos_root_dir - self.boot_sector.RootCluster * self.boot_sector.BytesPerSector + c * self.boot_sector.BytesPerSector))
                            # Limpa o cluster
                            f.write(b'\x00' * self.boot_sector.BytesPerSector)

                        f.close()
                    else:
                        print_error("O diretório não está vazio.")
                        return
                else:
                    print_error("Você não pode remover um arquivo.")
                    return
            else:
                print_error("Diretório não encontrado.")
                return



    def cp(self, name1, name2):
        """
        cp <name1> <name2>: copia um arquivo.
        """
        self.not_done()
        
    
    def mv(self, name1, name2):
        """
        mv <name1> <name2>: move um arquivo.
        """
        self.not_done()
    
    def clear(self):
        """
        clear: limpa o terminal.
        """
        os.system('cls' if os.name == 'nt' else 'clear')

    def not_done(self):
        print(
            self.cores.fonte['VERMELHO'] +
            "Comando não implementado." +
            self.cores.fonte['RESET']
        )
            
    def __str__(self):
        """
        Método que retorna uma string que representa o objeto.
        """
        return "Fat32"