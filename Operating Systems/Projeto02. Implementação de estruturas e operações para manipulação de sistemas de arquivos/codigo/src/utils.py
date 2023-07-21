""" 
###################### FUNÇÕES ######################
AUTORES:
    - Breno Farias da Silva             RA: 2300516
    - Felipe Archanjo da Cunha Mendes   RA: 2252740
    - Pamella Lissa Sato Tamura         RA: 2254107
    
DEFINIÇÃO:
    - Funções uteis para o desenvolvimento do projeto

Funções:
    - SearchFile: procura um arquivo no diretorio atual
    - get_attr: retorna o atributo do arquivo
    - find_pos_empty_entry: retorna a posição do primeiro entry vazio
    - print_error: imprime um erro na tela
"""

import struct
from src.cores import *

cores = Cores()

def SearchFile(search_name, file_position, filename):
    """
    Procura um arquivo no diretorio atual
    """
    quant_long_entry = 0
    with open(filename, 'rb') as f:
        f.seek(file_position)
        while True:
            # pula o nome do arquivo
            f.seek(f.tell() + 11)
            # Lê o atributo do arquivo
            attr = struct.unpack('<B', f.read(1))[0]
            # Se não houver mais arquivos, sai do loop
            if attr == 0:
                return False
                break
            # Se o arquivo for um longEntry, pule
            if attr == 0x0F:
                f.seek(f.tell() - 12 + 32)
                quant_long_entry += 1
                continue
            
            # Se for arquivo deletado, pule
            if attr == 0xE5:
                f.seek(f.tell() - 12 + 32)
                continue

            # Se o arquivo for um arquivo, compare
            if attr == 0x20:
                # Lê o nome do arquivo
                f.seek(f.tell() - 12)
                name = f.read(8)
                name = name.replace(b'\x00', b'')
                name = name.decode('utf-8')
                name = name.strip()

                ext = f.read(3)
                ext = ext.replace(b'\x00', b'')
                ext = ext.decode('utf-8')
                ext = ext.strip()
                ext = ext.lower()

                if not ext:
                    name_ext = name
                else:
                    name_ext = name + "." + ext

                # Verifica se o arquivo é o desejado
                if name_ext == search_name:
                    found_pos = f.tell() - 11 - 32 * quant_long_entry
                    pos_and_QuantLE = (found_pos, quant_long_entry)
                    return pos_and_QuantLE
                    break
                # Se não, pula para o próximo arquivo
                else:
                    f.seek(f.tell() - 11 + 32)
                    quant_long_entry = 0
                    continue
                
            # Se o arquivo for um diretorio, compare
            if attr == 0x10:
                # Lê o nome do arquivo
                f.seek(f.tell() - 12)
                name = f.read(11)
                name = name.replace(b'\x00', b'')
                name = name.decode('utf-8')
                name = name.split()
                name = "".join(name)

                # Verifica se o arquivo é o desejado
                if name == search_name:
                    found_pos = f.tell() - 11 - 32 * quant_long_entry
                    pos_and_QuantLE = (found_pos, quant_long_entry)
                    return pos_and_QuantLE
                    break
                # Se não, pula para o próximo arquivo
                else:
                    f.seek(f.tell() - 11 + 32)
                    quant_long_entry = 0
                    continue
        f.close()


def get_attr(file_position, number_of_LE, filename):
    """
    Retorna o atributo do arquivo
    """
    with open(filename, 'rb') as f:
        # Posiciona o cursor
        f.seek(file_position + 32 * number_of_LE + 11)
        # Lê o atributo do arquivo
        attr = struct.unpack('<B', f.read(1))[0]
        f.close()

    if attr == 0x10:
        return 'd'
    elif attr == 0x20:
        return 'f'
    else:
        return '-'


def find_pos_empty_entry(dir_position, filename):
    """
    Retorna a posição do primeiro entry vazio
    """
    with open(filename, 'rb') as f:
        # Posiciona o cursor
        f.seek(dir_position)

        while True:
            f.seek(f.tell() + 11)

            # Verifica se há atributo
            attr = struct.unpack('<B', f.read(1))[0]

            if attr == 0:
                pos_new_file = f.tell() - 12
                return pos_new_file
            else:
                f.seek(f.tell() - 12 + 32)

        f.close()


def dir_is_empty(dir_position, quant_LE, posRD, numRC, BPS, filename):
    """
    Verifica se o diretorio está vazio
    """
    with open(filename, 'rb') as f:
        # Posiciona o cursor no subdirectorio
        pos = find_data_pos(dir_position, quant_LE, posRD, numRC, BPS, filename) + 64
        f.seek(pos)
            
        while True:
            f.seek(f.tell() + 11)
            attr = struct.unpack('<B', f.read(1))[0]

            if attr == 0x0F:
                f.seek(f.tell() - 12 + 32)
                continue
            elif attr == 0xE5 or attr == 0:
                return True
            else:
                return False
                break

        f.close()


def find_data_pos(dir_position, quant_LE, posRD, numRC, BPS, filename):
    """
    Retorna a posição do diretorio de dados
    """
    with open(filename, 'rb') as f:
        # Posiciona o cursor no short entry
        pos = dir_position + 32 * quant_LE

        # Le o high cluster
        f.seek(pos + 20)
        high_cluster = struct.unpack('<H', f.read(2))[0]
        # Le o low cluster
        f.seek(pos + 26)
        low_cluster = struct.unpack('<H', f.read(2))[0]

        # Transforma o high e low cluster em um numero inteiro
        cluster = (high_cluster << 16) + low_cluster
        
        # Posiciona o cursor no cluster
        f.seek(posRD - numRC * BPS + cluster * BPS)
        return f.tell()


def find_empty_cluster(pos_fat_table, filename):
    """
    Retorna a posição do primeiro cluster vazio
    """
    with open(filename, 'rb') as f:
        # Posiciona o cursor no inicio da FAT
        f.seek(pos_fat_table)
        
        # Varre todos os clusters
        for i in range(0, 100793):
            # Lê o valor do cluster
            cluster = f.read(4)
            cluster = struct.unpack('<I', cluster)[0]
            if cluster == 0:
                dec_cluster = i

                hex_cluster = hex(dec_cluster)
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

                return hex_cluster_high, hex_cluster_low, dec_cluster

        f.close()
        return -1

def print_error(error):
    """
    Imprime um erro na tela
    """
    print(
            cores.fonte['VERMELHO'] +
            error +
            cores.fonte['RESET']
        )
