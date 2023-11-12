from automata.tm.ntm import NTM

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

def main():
    multiplicationTest()
                
# Execução do programa
if __name__ == "__main__":
    main()