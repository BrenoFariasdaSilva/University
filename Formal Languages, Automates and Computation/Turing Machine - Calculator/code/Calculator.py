from automata.tm.ntm import NTM

# NTM que faz a operação de adição.
ntmSUM = NTM(
    states={'s0', 's1', 's2', 's3', 'halt'},
    input_symbols={'1', '+'},
    tape_symbols={'1', '+', '#'},
    transitions={
        's0': {
            '#': {('s1', '#', 'R')}
        },
        's1': {
            '1': {('s1', '1', 'R')},
            '+': {('s2', '1', 'R')}
        },
        's2': {
            '1': {('s2', '1', 'R')},
            '#': {('s3', '#', 'L')}
        },
        's3': {
            '1': {('halt', '#', 'N')}
        }
    },
    initial_state='s0',
    blank_symbol='#',
    final_states={'halt'}
)

# NMT que faz a operação de subtração.
ntmSUBTRACTION = NTM(
    states={'s0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 's8', 'halt'},
    input_symbols={'1', '-'},
    tape_symbols={'1', '-', '#'},
    transitions={
        's0': {
            '#': {('s1', '#', 'R')}
        },
        's1': {
            '1': {('s2', '#', 'R')}
        },
        's2': {
            '1': {('s2', '1', 'R')},
            '-': {('s3', '-', 'R')}
        },
        's3': {
            '1': {('s3', '1', 'R')},
            '#': {('s4', '#', 'L')}
        },
        's4': {
            '1': {('s5', '#', 'L')}
        },
        's5': {
            '1': {('s6', '1', 'L')},
            '-': {('halt', '#', 'N')}
        },
        's6': {
            '1': {('s6', '1', 'L')},
            '-': {('s7', '-', 'L')},
        },
        's7': {
            '1': {('s8', '1', 'L')},
            '#': {('halt', '#', 'N')}
        },
        's8': {
            '1': {('s8', '1', 'L')},
            '#': {('s1', '#', 'R')}
        }
    },
    initial_state='s0',
    blank_symbol='#',
    final_states={'halt'}
)
    
# NTM que faz a operação de multiplicação.
ntmMULTIPLICATION = NTM(
    states={'s0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 's8', 's9' ,'halt'},
    input_symbols={'1', '*'},
    tape_symbols={'1', '*', '#', 'Z', 'E'},
    transitions={
        's0': {
            '1': {('s1', '#', 'R')},
            '#': {('s0', '#', 'R')} 
        },
        's1': {
            '1': {('s4', '1', 'R')},
            '*': {('s2', '1', 'R')}
        },
        's2': {
            '1': {('s2', '1', 'R')},
            'Z': {('s2', '1', 'R')},
            '#': {('s3', '#', 'L')}
        },
        's3': {
            '1': {('halt', '#', 'N')}
        },
        's4': {
            '1': {('s4', '1', 'R')},
            '*': {('s5', '*', 'R')}
        },
        's5': {
            '1': {('s6', 'E', 'R')},
            'Z': {('s8', 'Z', 'L')}
        },
        's6': {
            '1': {('s6', '1', 'R')},
            'Z': {('s6', 'Z', 'R')},
            '#': {('s7', 'Z', 'L')}
        },
        's7': {
            '1': {('s7', '1', 'L')},
            'E': {('s5', 'E', 'R')},
            'Z': {('s7', 'Z', 'L')}
        },
        's8': {
            'E': {('s8', '1', 'L')},
            '*': {('s9', '*', 'L')}
        },
        's9': {
            '1': {('s9', '1', 'L')},
            '#': {('s0', '#', 'R')}
        }
    },
    initial_state='s0',
    blank_symbol='#',
    final_states={'halt'}
)

# NTM que faz a operação de divisão.
ntmDIVISION = NTM(
    states={'s0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 's8', 's9', 'halt'},
    input_symbols={'1', '/'},
    tape_symbols={'1', '/', '#', 'Z', 'E'},
    transitions={
        's0': {
            '#': {('s1', '#', 'R')}
        },
        's1': {
            '1': {('s2', '#', 'R')},
            '/': {('s9', '#', 'R')}
        },
        's2': {
            '1': {('s2', '1', 'R')},
            '/': {('s3', '/', 'R')}
        },
        's3': {
            '1': {('s3', '1', 'R')},
            'E': {('s3', 'E', 'R')},
            'Z': {('s4', 'Z', 'L')},
            '#': {('s4', '#', 'L')}
        },
        's4': {
            '1': {('s5', 'E', 'L')},
            'E': {('s4', 'E', 'L')}
        },
        's5': {
            '1': {('s7', '1', 'L')},
            '/': {('s6', '/', 'R')}
        },
        's6': {
            'E': {('s6', '1', 'R')},
            'Z': {('s6', 'Z', 'R')},
            '#': {('s7', 'Z', 'L')}
        },
        's7': {
            '1': {('s7', '1', 'L')},
            'Z': {('s7', 'Z', 'L')},
            '/': {('s8', '/', 'L')}
        },
        's8': {
            '1': {('s8', '1', 'L')},
            '#': {('s1', '#', 'R')}
        },
        's9': {
            '1': {('s9', '#', 'R')},
            'Z': {('s9', '1', 'R')},
            '#': {('halt', '#', 'N')}
        }
    },
    initial_state='s0',
    blank_symbol='#',
    final_states={'halt'}
)

def sumTest():
    print('TURING MACHINE - SUM:')
    
    sumInputs = [
        '#11111+11#',
        '#11111+111#',
        '#111+11#',
        '#1+11#',
        '#11111111+1111111#',
        '#11111+1#'
    ]

    for input in sumInputs:
        print('Validate Input:',  ntmSUM.validate()) # Valida o input
        if ntmSUM.accepts_input(input): # Se o input for aceitável, então o autômato aceita
            ntmSUM.read_input(input).pop().print() # Lê o input e imprime o resultado

def subtractionTest():
    print('TURING MACHINE - SUBTRACTION:')
    
    subtractionInputs = [
        '#11111-11#',
        '#11111-111#',
        '#111-11#',
        '#1-1#',
        '#11111111-1111111#',
        '#11111-1#'
    ]

    for input in subtractionInputs:
        print('Validate Input:',  ntmSUBTRACTION.validate()) # Valida o input
        if ntmSUBTRACTION.accepts_input(input): # Se o input for aceitável, então o autômato aceita
            ntmSUBTRACTION.read_input(input).pop().print() # Lê o input e imprime o resultado

def multiplicationTest():
    print('TURING MACHINE - MULTIPLICATION:')
    
    multiplicationInputs = [
            '#11111*11####',
            '#11111*111####',
            '#11*11####',
            '#1*1####',
            '#11111*111111####',
            '#1111*1####'
    ]

    for input in multiplicationInputs:
        print('Validate Input:',  ntmMULTIPLICATION.validate()) # Valida o input
        if ntmMULTIPLICATION.accepts_input(input): # Se o input for aceitável, então o autômato aceita
            ntmMULTIPLICATION.read_input(input).pop().print() # Lê o input e imprime o resultado

def divisionTest():
    print('TURING MACHINE - DIVISION:')
    
    divisionInputs = [
        '#1111/11####',
        '#111111/11####',
        '#11/11####',
        '#11111111/1111####',
        '#111111/11####',
    ]

    for input in divisionInputs:
        print('Validate Input:',  ntmDIVISION.validate()) # Valida o input
        if ntmDIVISION.accepts_input(input): # Se o input for aceitável, então o autômato aceita
            ntmDIVISION.read_input(input).pop().print() # Lê o input e imprime o resultado

def main():
    sumTest()
    subtractionTest()
    multiplicationTest()
    divisionTest()
                
# Execução do programa
if __name__ == "__main__":
    main()