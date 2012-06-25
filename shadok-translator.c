#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum Vocabulary {
    FirstWord = 0,
    Meu = FirstWord,
    MeuMeu,
    Bu,
    Zo,
    Ga,
    GaGa,
    WordWount
};

static const char * french[WordWount] = {"moi", "toi", "pompe" , "pomper", "petite", "grosse"};
static const char * gabuzomeu[WordWount] = {"Meu", "MeuMeu", "Bu" , "Zo", "Ga", "GaGa"};

#define WORD_MAX_SIZE 256
const int EMPTY_STACK_INDEX = -1;

int main(int argc, char * argv[])
{
    int index;
    char word[WORD_MAX_SIZE];
    size_t output_size = 0;
    int * output_stack = NULL;
    int output_last = EMPTY_STACK_INDEX;

    /* affiche le dictionnaire si l'option -h est passée */
    if (argc >= 2 && (strncmp(argv[1], "-h", 3) == 0))
    {
        fprintf(stdout, "Dictionnaire Français/GaBuZoMeu :\n");
        for (index = FirstWord; index < WordWount; ++index)
        {
            fprintf(stdout, "%s\t%s\n", french[index], gabuzomeu[index]);
        }
        return 0;
    }

    while (EOF != fscanf(stdin, "%s", word))
    {
        for (index = FirstWord; index < WordWount; ++index)
        {
            if (strncmp(word, french[index], WORD_MAX_SIZE) != 0)
                continue;

            /* redimensionne la pile si elle est pleine */
            if (output_last == output_size - 1)
            {
                output_size += 10;
                output_stack = realloc(output_stack, sizeof(int) * output_size);
            }

            /* ajoute le mot actuel à la pile */
            output_stack[++output_last] = index;
            
            /* si le mot est un adjectif passer au suivant */
            if (index == Ga || index == GaGa)
                break;

            /* afficher le contenu de la pile et passer au suivant*/
            while (output_last > EMPTY_STACK_INDEX)
            {
                fprintf(stdout, "%s", gabuzomeu[output_stack[output_last--]]);
            }
            break;
        }
    }
    fprintf(stdout, "\n");

    free(output_stack);
    return 0;
}
