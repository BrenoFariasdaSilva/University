""" 
###################### BOOT SECTOR ######################
AUTORES:
    - Breno Farias da Silva             RA: 2300516
    - Felipe Archanjo da Cunha Mendes   RA: 2252740
    - Pamella Lissa Sato Tamura         RA: 2254107
    
DEFINIÇÃO:
    - O boot sector é o primeiro bloco do disco.

ESTRUTURAS:
    - OemName: string de até 8 caracteres que identifica o sistema operacional. (0x03 - 0x0B)
    - BytesPerSector: inteiro de 2 bytes que representa o número de bytes que cada setor do disco tem. (0x0B - 0x0D)
    - SectorsPerCluster: inteiro de 1 byte que representa o número de setores que cada cluster do disco tem. (0x0D - 0x0E)
    - ReservedSectors: inteiro de 2 bytes que representa o número de setores que o sistema operacional reserva para o sistema. (0x0E - 0x10)
    - NumberOfFATs: inteiro de 1 byte que representa o número de FATs que o sistema operacional utiliza. (0x10 - 0x11)
    - MaxRootDirEntries: inteiro de 2 bytes que representa o número de entradas na árvore de diretórios raiz. (0x11 - 0x13)
    - NumberOfSectors16: inteiro de 2 bytes que representa o número de setores do disco. (0x13 - 0x15)
    - MediaDescriptor: inteiro de 1 byte que representa o tipo de mídia do disco. (0x15 - 0x16)
    - SectorsPerFAT16: inteiro de 2 bytes que representa o número de setores que cada FAT16 do disco tem. (0x16 - 0x18)
    - SectorsPerTrack: inteiro de 2 bytes que representa o número de setores que cada trilha do disco tem. (0x18 - 0x1A)
    - HeadsPerCylinder: inteiro de 2 bytes que representa o número de trilhas do disco. (0x1A - 0x1C)
    - NumHiddenSectors: inteiro de 4 bytes que representa o número de setores que o sistema operacional oculta do disco. (0x1C - 0x20)
    - NumberOfSectors32: inteiro de 4 bytes que representa o número de setores do disco. (0x20 - 0x24)
    - SectorsPerFAT32: inteiro de 4 bytes que representa o número de setores que cada FAT32 do disco tem. (0x24 - 0x28)
    - flags: inteiro de 2 bytes que representa os flags do sistema operacional. (0x28 - 0x2A)
    - version: inteiro de 2 bytes que representa a versão do sistema operacional. (0x2A - 0x2C)
    - RootCluster: inteiro de 4 bytes que representa o cluster da árvore de diretórios raiz. (0x2C - 0x30)
    - InfoSector: inteiro de 2 bytes que representa o cluster do registro de informações do sistema operacional. (0x30 - 0x32)
    - BootBackupStart: inteiro de 2 bytes que representa o cluster do registro de backup do boot sector. (0x32 - 0x34)
    - Reserved: inteiro de 12 bytes que representa os setores reservados. (0x34 - 0x40)
    - DriveNumber: inteiro de 1 byte que representa o número do disco. (0x40 - 0x41)
    - Unused: inteiro de 1 byte que representa o número de setores que o sistema operacional oculta do disco. (0x41 - 0x42)
    - ExtBootSignature: inteiro de 1 byte que representa o sinalizador de boot do sistema operacional. (0x42 - 0x43)
    - SerialNumber: inteiro de 4 bytes que representa o número de série do sistema operacional. (0x43 - 0x47)
    - VolumeLabel: string de 11 bytes que representa o nome do volume. (0x47 - 0x52)
    - FileSystemLabel: string de 8 bytes que representa o nome do sistema operacional. (0x52 - 0x5A)
    - BootCode: string de 448 bytes que representa o código de boot do sistema operacional. (0x5A - 0x1FE)
    - EndOfSectorMarker: string de 2 bytes que representa o marcador de fim de setor. (0x1FE - 0x200)
"""

import struct

class BootSector:
    def __init__(self, filename):
        # Abertura da imagem para leitura
        with open(filename, 'rb') as f:
            # Ponteiro no inicio do Boot Sector
            f.seek(0x03)

            # Leitura das informações do Boot Sector
            self.OemName = f.read(8).decode('utf-8').rstrip('\x00')

            self.BytesPerSector = struct.unpack('<H', f.read(2))[0]

            self.SectorsPerCluster = struct.unpack('<B', f.read(1))[0]

            self.ReservedSectors = struct.unpack('<H', f.read(2))[0]

            self.NumberOfFATs = struct.unpack('<B', f.read(1))[0]

            self.MaxRootDirEntries = struct.unpack('<H', f.read(2))[0]

            self.NumberOfSectors16 = struct.unpack('<H', f.read(2))[0]

            self.MediaDescriptor = struct.unpack('<B', f.read(1))[0]

            self.SectorsPerFAT16 = struct.unpack('<H', f.read(2))[0]

            self.SectorsPerTrack = struct.unpack('<H', f.read(2))[0]

            self.HeadsPerCylinder = struct.unpack('<H', f.read(2))[0]

            self.NumHiddenSectors = struct.unpack('<I', f.read(4))[0]

            self.NumberOfSectors32 = struct.unpack('<I', f.read(4))[0]

            self.SectorsPerFAT32 = struct.unpack('<I', f.read(4))[0]

            self.flags = struct.unpack('<H', f.read(2))[0]

            self.version = struct.unpack('<H', f.read(2))[0]

            self.RootCluster = struct.unpack('<I', f.read(4))[0]

            self.InfoSector = struct.unpack('<H', f.read(2))[0]

            self.BootBackupStart = struct.unpack('<H', f.read(2))[0]

            self.Reserved = f.read(12).decode('utf-8').rstrip('\x00')

            self.DriveNumber = struct.unpack('<B', f.read(1))[0]

            self.Unused = struct.unpack('<B', f.read(1))[0]

            self.ExtBootSignature = struct.unpack('<B', f.read(1))[0]

            self.SerialNumber = struct.unpack('<I', f.read(4))[0]

            self.VolumeLabel = f.read(11).decode('utf-8').rstrip('\x00')

            self.FileSystemLabel = f.read(8).decode('utf-8').rstrip('\x00')

            self.BootCode = f.read(448)

            self.EndOfSectorMarker = f.read(2).decode('utf-8').rstrip('\x00')

            # Fechamento da imagem
            f.close()
    
    def __str__(self):
        
        return "OemName: {}\nBytesPerSector: {}\nSectorsPerCluster: {}\nReservedSectors: {}\nNumberOfFATs: {}\nMaxRootDirEntries: {}\nNumberOfSectors16: {}\nMediaDescriptor: {}\nSectorsPerFAT16: {}\nSectorsPerTrack: {}\nHeadsPerCylinder: {}\nNumHiddenSectors: {}\nNumberOfSectors32: {}\nSectorsPerFAT32: {}\nflags: {}\nversion: {}\nRootCluster: {}\nInfoSector: {}\nBootBackupStart: {}\nReserved: {}\nDriveNumber: {}\nUnused: {}\nExtBootSignature: {}\nSerialNumber: {}\nVolumeLabel: {}\nFileSystemLabel: {}\nBootCode: {}\nEndOfSectorMarker: {}".format(self.OemName, self.BytesPerSector, self.SectorsPerCluster, self.ReservedSectors, self.NumberOfFATs, self.MaxRootDirEntries, self.NumberOfSectors16, self.MediaDescriptor, self.SectorsPerFAT16, self.SectorsPerTrack, self.HeadsPerCylinder, self.NumHiddenSectors, self.NumberOfSectors32, self.SectorsPerFAT32, self.flags, self.version, self.RootCluster, self.InfoSector, self.BootBackupStart, self.Reserved, self.DriveNumber, self.Unused, self.ExtBootSignature, self.SerialNumber, self.VolumeLabel, self.FileSystemLabel, self.BootCode, self.EndOfSectorMarker)
            

        