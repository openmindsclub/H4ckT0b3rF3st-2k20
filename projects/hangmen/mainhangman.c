#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include <time.h>





#include "functions.h"

#include "save/save.h"

#include "display/displayFunc.h"

#include "wordManip/plWordInit.h"

#include "wordManip/letterInclud.h"

#include "wordManip/getWord.h"

#define SOLO_MODE 1

#define MULTI_MODE 2

#define ALL_VS_CPU 1

#define P_V_P 2

#ifndef MAX_SIZE

    #define MAX_SIZE 100

#endif



int main () {

    const char menuFile[] = "display/menu.txt";       //the file containing the menu

    char cpuWord[MAX_SIZE], ourWord[MAX_SIZE], wordsFile[MAX_SIZE], savingFile[MAX_SIZE];

    int i, j, mult, trials, roundsNbr;;       //will be used in several places as an int

    PlInf *pointerOnPlayer = NULL;       //will be used in the "letteeinclud" function



    dispalyFunc(menuFile, linesConter(menuFile));      //displaying the menu (check the file dispaly/menu.txt)



    do {                                                //chosing the mode

        printf("\t\t\t\ttype your choice number\t\t\t\n\n");

        printf("\t\t\t\t\t ");scanf("%d", &mult);printf("\t\t\t\t\t");

    }while ((mult < SOLO_MODE) || (mult > MULTI_MODE));  //the choice must be "1" or "2" not else



    if (mult == SOLO_MODE) {       //solo mode

        const char soloRulesScoreFile[] = "display/solo/rules_score.txt";     //the file that contains the ruels

        PlInf player = {"", ' ', 0000, 0, 0, 1, 0, 0, 0, 0};       //initializig the player data {pseudonym, letter, score, win, position}

        pointerOnPlayer = &player;



        do {        //chosing to read the rules or not to

            cleanBuffer();      //remouve the '\n' from the buffer

            printf("\t\t\t  do you want to read the rules ? \t\t\t\n");

            printf("\t\t     if yes write -- y -- if no write -- n --\t\t\n");

            printf("\t\t\t\t\t ");scanf("%c", &mult);printf("\n");

        }while ((mult != 'y') && (mult != 'n'));     //the choice must be "y" for yes or "n" fore no



        if (mult == 'y') {     //if the user chose to read the rules

            dispalyFunc(soloRulesScoreFile, linesConter(soloRulesScoreFile));       //displaying the rules (check the file "isplay/rules_score.txt")

        }



        do {                     //chosing the langueg of the words

            cleanBuffer();

            printf("\t\tif you want the words to be in frensh type --- f ---\n");

            printf("\t\tif you want the words to be in english type --- e ---\n");

            printf("\t\t\t\t\t ");scanf("%c", &mult);printf("\n");

        } while ((mult != 'f') && (mult != 'e'));     //the choice must be "f" for frensh or "e" fore english



        if (mult == 'e') {                 //selecting the english words

            stringAffect("wordManip/words/dictionaryEnglish.txt", wordsFile);      //the list of english words

        } else if (mult == 'f') {          //selecting the frensh words

            stringAffect("wordManip/words/dictionaryFrancais.txt", wordsFile);     //the list of frensh words

        }



        stringAffect("save/test.txt", savingFile);

        profileInit(pointerOnPlayer, savingFile);

        printf("\t\t\t\tokay let's go %s\n", player.pseudonym);

        printf("\t\t\tHow many rounds do you want to play ?\n");        //geting the rounds number

        printf("\t\t\t\t\t");scanf("%d", &roundsNbr);



        for (i = 1; i <= roundsNbr; i++) {    //the biginig of  the "i + 1" round

            getWord(wordsFile, cpuWord);        //geting a word from the ditionary (the file is in wordManip/words)

            trials = atempsInit(cpuWord);

            plWordInit(cpuWord, ourWord);       //initializing the player word

            printf("\t\t\t\t-----  Round %d  -----\n", i);

            printf("\t\tThe computer has chosen a word, it's your turn now !!\n");



            do {     //the part wher the round hapens

                cleanBuffer();      //we must clean the buffer

                printf("\t\t\tyou have %d attempts\n", trials);     //the number of the atempts remained to player

                printf("\t\t\t\t%s \n", ourWord);       //to helpe the player

                printf("\t\t\t\ttry a letter\n");        //the player givs a letter

                printf("\t\t\t\t\t");scanf("%c", &player.letter);

                letterInclud(cpuWord, ourWord, pointerOnPlayer);        //including the letter chosen by the player in his word

                trials--;       //mines one trial

            } while ((strcmp(ourWord, cpuWord) != 0) && (trials != 0));       //(strcmp compair the strings) if the player word is the same with the cpu word then he has fond it



            if (strcmp(ourWord, cpuWord) != 0) {      //if the player didn't fond the cpu word

                printf("\t\t\tyou didn't find the word\n");

                printf("\t\t\tthe word was : %s\n", cpuWord);

                player.score /= 2;      //the player score is divided by 2

            } else {       //if the player has fond the cpu word

                printf("\t\t\t\t%s\n", ourWord);

                printf("\t\tGreat you found the word !!\n");

                player.score += 25;     //he fond the word so he erned 25 pts

                player.win += 1;        //he won and has 1 mor win in his player info structur (check the struct header)

                printf("\t\t\tyou have %d wins\n", player.win);     //writing the palyer's win number

            }



            printf("\t\t\tyour score is : %d\n", player.score);     //writing the player's score

        }

    } else if (mult == MULTI_MODE) {      //multiplayers mode

        const char gameTypesFile[] = "display/multi/multiGameType.txt";         //the file that containes the multi menu

        const char multiAllVsCpuFile[] = "display/multi/allVsCpu/rules_score.txt";      //the file that containes the all vs cpu ruels

        const char multPlVsPlFile[] = "display/multi/playerVsPlayer/rules_score.txt";       //the file that containes player vs player rules

        const char multiScoreTabFile[] = "display/multi/scoreTab.txt";      //the file that contains the scors

        int playersNbr;     // to store the player's number

        PlInf *players = NULL;      //the array that contains the players data

        PlInf actuPlayer, tehSelectPlayer;       //the player that is going to play and the one who is going to chose the word



        do {     //geting the number of players (can't be less then 2)

        printf("\t\t\t\tHow many players ?\n");

        printf("\t\t\t\t\t ");scanf("%d", &playersNbr);

        } while (playersNbr < 2);     //must be more then 1 player



        players = malloc(sizeof(PlInf) * playersNbr);        //allocating memory to store the players data



        if (players == NULL) {     //checking that the allocation succeeded (if not we exit the programe)

            printf("allocation faild");

            exit(0);        //here we exit the file

        }



        for (i = 0; i < playersNbr; i++) {     //here start the interisting things... seting the players data

            printf("\n\t\t\t     player %d type your pseudonym\n", i + 1);      //geting the players pseudonyms

            printf("\t\t\t\t\t");scanf("%s", players[i].pseudonym);

            players[i].pseudonym[17] = '\0';        //finiching the stings

            players[i].score = 0;       //seting the score

            players[i].win = 0;     //seting the wins

            players[i].position = i + 1;        //the initial positions are seted by introducing order but will change after the first round

            players[i].plNbr = i + 1;       //each player has a number (player 1, player 2...)

        }



        dispalyFunc(gameTypesFile, linesConter(gameTypesFile));         //displaying the game types menu



        do {     //chosing the game type

            printf("\t\t\t\ttype your choice number\n");

            printf("\n\t\t\t\t\t");scanf("%d", &mult);

        } while ((mult != 1) && (mult != 2));



        if (mult == ALL_VS_CPU) {      //the all vs cpu mode

            do {      //chosing to read the rules or not to

                cleanBuffer();      //remouve the '\n' from the buffer

                printf("\t\t\t  do you want to read the rules ? \t\t\t\n");

                printf("\t\t     if yes write -- y -- if no write -- n --\t\t\n");

                printf("\t\t\t\t\t ");scanf("%c", &mult);printf("\n");

            } while ((mult != 'y') && (mult != 'n'));     //the choice must be "y" for yes or "n" fore no



            if (mult == 'y') {     //displaying the rules

                dispalyFunc(multiAllVsCpuFile, linesConter(multiAllVsCpuFile));     //displaying the rules fille (check display/multi/allVsCpu/rules_score.txt)

            }



            do {     //chosing the langueg of the words

                cleanBuffer();

                printf("\t\tif you want the words to be in frensh type --- f ---\n");

                printf("\t\tif you want the words to be in english type --- e ---\n");

                printf("\t\t\t\t\t ");scanf("%c", &mult);printf("\n");

            } while ((mult != 'f') && (mult != 'e'));     //the choice must be "f" for frensh or "e" fore english



            if (mult == 'e') {      //selecting the english words

                stringAffect("wordManip/words/dictionaryEnglish.txt", wordsFile);      //the list of english words

            } else if (mult == 'f') {       //selecting the frensh words

                stringAffect("wordManip/words/dictionaryFrancais.txt", wordsFile);     //the list of frensh words

            }



            printf("\t\t\tHow many rounds do you want to play ?\n");        //geting the round's number

            printf("\t\t\t\t\t");scanf("%d", &roundsNbr);



            for (i = 0; i < roundsNbr; i++) {       //the biginig of the "i + 1" round

                getWord(wordsFile, cpuWord);        //geting a word from the ditionary (the file is in wordManip/words)

                trials = atempsInit(cpuWord),       //seting the trials number according to the word length

                plWordInit(cpuWord, ourWord);       //initializing the players word

                printf("\t\t\t\t-----  Round %d  -----\n", i + 1);

                printf("\t\tThe computer has chosen a word, it's your turn now !!\n");

                mult = 0;       //to know who's turn it is



                do {      //here the game begins

                    mult = (mult % playersNbr) + 1;     //to get wich player will playe acording to his position

                    cleanBuffer();      //we must clean the buffer

                    printf("\t\t\tyou have %d attempts\n", trials);     //the number of the atempts remained to player

                    printf("\t\t\t\t%s \n", ourWord);       //to helpe the player

                    actuPlayer = playerSelect(mult, playersNbr, players);       //storing the actual player data

                    pointerOnPlayer = &actuPlayer;      //initializing the pointer valu so it points to where the player data is stored

                    printf("\t\t%s it your turn to chose a letter\n", actuPlayer.pseudonym);

                    printf("\t\t\t\t\t");scanf("%c", &actuPlayer.letter);

                    letterInclud(cpuWord, ourWord, pointerOnPlayer);        //including the letter chosen by the player in his word

                    players[mult - 1].score = actuPlayer.score;     //puting the actual player score in the array that holds the players data

                    trials--;

                } while ((strcmp(ourWord, cpuWord) != 0) && (trials != 0));       //if the player fond the word or  has no more trials



                if (strcmp(ourWord, cpuWord) != 0) {       //if the word hasn't been fond

                    printf("\t\t\tyou didn't find the word\n");

                    printf("\t\t\tthe word was : %s\n", cpuWord);



                    for (j = 0; j < playersNbr; j++) {       //the score of all the players will be divided by 2

                        players[j].score /= 2;

                    }

                }else {        //if the word has been fond

                    printf("\t\t\t\t%s\n", ourWord);

                    printf("\t\tGreat %s found the word !!\n", players[mult - 1].pseudonym);

                    players[mult - 1].score += 25;      //the player tha fond the word erns 25 pts

                    printf("\t\t\t%s has won this round\n", players[0].pseudonym);

                    players[mult - 1].win++;       //the player tha fond the word get one more win

                }



                playersClasser(players, playersNbr);    //clasing the players according to their score

                ScoreFileileFormating(multiScoreTabFile, playersNbr, players);      //writing the scores in the score file

                dispalyFunc(multiScoreTabFile, linesConter(multiScoreTabFile));     //displaind the scors file

            }

        } else if (mult == P_V_P) {

            do {      //chosing to read the rules or not to

                cleanBuffer();      //remouve the '\n' from the buffer

                printf("\t\t\t  do you want to read the rules ? \t\t\t\n");

                printf("\t\t     if yes write -- y -- if no write -- n --\t\t\n");

                printf("\t\t\t\t\t ");scanf("%c", &mult);printf("\n");

            } while ((mult != 'y') && (mult != 'n'));     //the choice must be "y" for yes or "n" fore no



            if (mult == 'y') {      //displaying the rules

                dispalyFunc(multPlVsPlFile, linesConter(multPlVsPlFile));     //displaying the rules fille (check display/multi/allVsCpu/rules_score.txt)

            }



            for (i = 1; i <= playersNbr; i++) {       //the "i" player choses the word

                tehSelectPlayer = playerSelectP_V_P(i, playersNbr, players);        //selecting the player who givs the word

                printf("\t\t\t%s it's your turn to give a word\n", tehSelectPlayer.pseudonym);        //asking the player to give a word

                printf("\t\t\t\t    ");scanf("%s", cpuWord);printf("\n");



                for (mult = 0; mult < strlen(cpuWord); mult++) {       //puting the word in caps

                    cpuWord[mult] = toupper(cpuWord[mult]);

                }



                plWordInit(cpuWord, ourWord);       //initializing the players word

                trials = atempsInit(cpuWord) + playersNbr / 2;      //seting the atemps number

                mult = 0;



                do {

                    mult = (mult % playersNbr) + 1;     //to get wich player will playe acording to his position

                    cleanBuffer();      //we must clean the buffer

                    printf("\t\t\tyou have %d attempts\n", trials);     //the number of the atempts remained to player

                    printf("\t\t\t\t%s \n", ourWord);       //to helpe the player

                    actuPlayer = playerSelect(mult, playersNbr, players);       //geting the actual player data



                    if (actuPlayer.plNbr == tehSelectPlayer.plNbr) {       //if the actual player is the player that chosed the word we move to the next player

                        mult++;

                        actuPlayer = playerSelect(mult, playersNbr, players);

                    }

;

                    pointerOnPlayer = &actuPlayer;      //seting the poiter to point on the actual player data location

                    printf("\t\t%s it your turn to chose a letter\n", actuPlayer.pseudonym);

                    printf("\t\t\t\t\t");scanf("%c", &actuPlayer.letter);

                    letterInclud(cpuWord, ourWord, pointerOnPlayer);        //including the letter chosen by the player in his word (and changing his scor)

                    players[mult - 1].score = actuPlayer.score;     //puting the actual player score in the array of th players

                    trials--;

                } while ((strcmp(ourWord, cpuWord) != 0) && (trials != 0));



                if (strcasecmp(ourWord, cpuWord) != 0) {       //if the word hasn't been fond

                    printf("\t\t\tyou didn't find the word\n");

                    printf("\t\t\tthe word was : %s\n", cpuWord);

                    printf("\t\t\t%s you get %d pts\n",tehSelectPlayer.pseudonym, 25 + 10 * playersNbr);        //the player who chosed the word gets 25 pts and 10 pts for each player

                    tehSelectPlayer.score += 25 + 10 * playersNbr;      //the player who chosed the word gets 25 pts and 10 pts for each player

                    tehSelectPlayer.win++;      //the player tha selected the word earns one more win



                    for (j = 0; j < playersNbr; j++) {      //dividing the score of the others by two

                        if (players[j].plNbr != tehSelectPlayer.plNbr) {       //the player that chosed the word wont be afected

                            players[j].score /= 2;

                        }

                    }

                }else {

                    printf("\t\t\t\t%s\n", ourWord);

                    printf("\t\tGreat %s found the word !!\n", players[mult - 1].pseudonym);

                    players[mult - 1].score += 25;      //the player tha fond the word erns 25 pts

                    printf("\t\t\t%s has won this round\n", players[mult - 1].pseudonym);

                    players[mult - 1].win++;       //the player tha fond the word get one more win

                    tehSelectPlayer.score /= 2;     //the player who chosed the word gets his score divided by two

                }



                for (j = 0; j < playersNbr; j++) {

                    if (players[j].plNbr == tehSelectPlayer.plNbr) {

                        players[j].score = tehSelectPlayer.score;

                        players[j].win = tehSelectPlayer.win;

                    }

                }



                playersClasser(players, playersNbr);    //clasing the players according to their score

                ScoreFileileFormating(multiScoreTabFile, playersNbr, players);      //writing the scores in the score file

                dispalyFunc(multiScoreTabFile, linesConter(multiScoreTabFile));     //displaind the scors file

            }

        }

    }



    return 0;

}
