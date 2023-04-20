#include <stdio.h>

int main()
{
    char caracter = 0;

    printf("Digite um caractere: ");
    scanf("%c", &caracter);

    if ((caracter >= 48) && (caracter <= 57))
    {
        printf("O caracter %c e um numero! \n", caracter);
    }

    if ((caracter >= 'a' && caracter <= 'z') || (caracter >= 'A' && caracter <= 'Z'))
    {
        if ((caracter == 'a') || (caracter == 'A'))
        {
            printf("O caracter %c e uma vogal! \n", caracter);
        }

        else
        {
            if ((caracter == 'e') || (caracter == 'E'))
            {
                printf("O caracter %c e uma vogal! \n", caracter);
            }

            else
            {
                if ((caracter == 'i') || (caracter == 'I'))
                {
                    printf("O caracter %c e uma vogal! \n", caracter);
                }

                else
                {
                    if ((caracter == 'o') || (caracter == 'O'))
                    {
                        printf("O caracter %c e uma vogal! \n", caracter);
                    }

                    else
                    {
                        if ((caracter == 'u') || (caracter == 'U'))
                        {
                            printf("O caracter %c e uma vogal! \n", caracter);
                        }

                        else
                        {
                            printf("O caracter %c e uma consoante!! \n", caracter);
                        }
                    }
                }
            }
        }
    }

    else
    {
        printf("O caracter %c e um simbolo! \n", caracter);
    }

    return 0;
}
