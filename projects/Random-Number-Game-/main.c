#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for rand(); ( random number generator) function
#include <windows.h> // library that include cmd instructions like cls , dir , cd

int main()
{
    int number_Mystere, number_Added, i, repeat, choice; // mystere for function rand . added for added number by user
    int MAX, MIN = 1; // the max-min of random number
    srand(time(NULL)); // init the random number generator function

    // loop statement for asking user to repeat again
    do
    {
        system("cls"); // for clearing the text after repeat = 1 (by user)
        printf("  \t\tRANDOM-NUMBER-GENERATOR GAME\n\n");
        printf("You must find the mystery number \n\n");
        // Choosing the level of game
        printf("Choose the Game Difficulty\n\n");
        printf("1- MIN = 1 , MAX = 100\n");
        printf("2- MIN = 1 , MAX = 1000\n");
        printf("3- MIN = 1 , MAX = 10000\n");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                MAX = 100;
            break;

            case 2:
                MAX = 1000;
            break;

            case 3:
                MAX = 10000;
            break;

            default:
                printf("choose the difficulty, enter the MAX : ");
                scanf("%d", &MAX);
            break;
        }
        printf("The number is between %d and %d , Try now \n\n", MAX, MIN);
        number_Mystere = (rand() % (MAX - MIN + 1)) + MIN;
        i = 0; // initializing the value variable that count how much player plays .
        // the main loop statement
        do
        {
            printf("Add the number : ");
            scanf("%d", &number_Added);
            if(number_Added > number_Mystere)
            {
                printf("The added number is bigger than the mystery\n\n");
                printf("Try again : ");
            }
            else if (number_Added < number_Mystere)
            {
                printf("The added number is smaller than the mystery\n\n");
                printf("Try again : ");
            }
            i++;
        }while(number_Added != number_Mystere);
        printf("Congratulations , You find the number : %d in %d time\n\n", number_Mystere, i);
        printf("If you want to play again type 1 ; if not type 0 : ");
        scanf("%d", &repeat);

    } while(repeat != 0); // end of first loop of playing again

    return 0;
}
