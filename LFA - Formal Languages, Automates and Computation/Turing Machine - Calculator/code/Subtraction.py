from automata.tm.ntm import NTM

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

def main():
    subtractionTest()
                
# Execução do programa
if __name__ == '__main__':
    main()