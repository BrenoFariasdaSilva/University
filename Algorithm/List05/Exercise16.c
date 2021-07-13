#include <stdio.h>

int main() 
{
    int lins = 10;
    int cols = 30;
    int playerLin = lins/2;
    int playerCol = cols/2;

    char dir = 'W';
    
    while(dir != 'Q' && dir != 'q') 
    {   // impressao do tablado
        printf("\n");
        for (int i = 0; i < lins; i++) 
        {
            for (int j = 0; j < cols; j++)
            {
                if (i == playerLin && j == playerCol) 
                {
                    printf("#");
                } 
                else 
                {
                    printf(".");
                }
            }
            printf("\n");
        }
        printf("\n");
        
        printf("Informe WASD ou Q para sair: "); 
        scanf("%c", &dir);

        // tratamento das direcoes
        if (dir == 'W' || dir == 'w')
        {
            playerLin--;
        }

        else
        if (dir == 'S' || dir == 's')
        {
            playerLin++;
        } 
        
        else
        if (dir == 'A' || dir == 'a')
        {
            playerCol--;
        }
         
        else
        if (dir == 'D' || dir == 'd')
        {
            playerCol++;
        } 
    }

    return 0; 
}
