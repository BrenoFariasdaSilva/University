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

def main():
    sumTest()
                
# Execução do programa
if __name__ == "__main__":
    main()