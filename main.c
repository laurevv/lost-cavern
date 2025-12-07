/**************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying
and applying the concepts learned. I have constructed the functions and their respective
algorithms and corresponding code by myself. The program was run, tested, and debugged
by my own efforts. I further certify that I have not copied in part or whole or otherwise
plagiarized the work of other students and/or persons.
Lauren Jasmin Hannako S. Padua, DLSU ID# 12506990
***************************************************************************

Description: Implemented a text-based adventure game based in a cavern that complies
             with the project's required specifications. 

Programmed by: Lauren Jasmin Hannako S. Padua S16
Last modified: November 23, 2025
Version: 2.1
[Acknowledgements: https://www.geeksforgeeks.org/c/generating-random-number-range-c/
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Displays the ASCII art title of the game
Precondition: None
@param None
@return None
*/
void displayTitle();

/* Displays the cave ASCII art
Precondition: None
@param None
@return None
*/
void displayCave();

/* Displays the starting screen and asks the player if they're ready
Precondition: None
@param None
@return 1 if player chooses to start, 0 otherwise
*/
int starting_screen();

/* Displays the player's current stats (health and score)
Precondition: nHealth and nScore must be valid integers
@param nHealth current health of the player
@param nScore current score of the player
@return None
*/
void checkStats(int nHealth, int nScore);

/* Displays the pause menu with options to continue or check stats
Precondition: nHealth and nScore must be valid integers
@param nHealth current health of the player
@param nScore current score of the player
@return None
*/
void pauseMenu(int nHealth, int nScore);

/* Handles the first room where player chooses one of two paths
Precondition: nHealth and nScore must be valid pointers to integers
@param nHealth pointer to player's health
@param nScore pointer to player's score
@return 1 if left path is chosen, 2 if right path is chosen
*/
int room_one(int *nHealth, int *nScore);

/* Handles the second room where the player loses health
Precondition: nHealth and nScore must be valid pointers
@param nHealth pointer to player's health
@param nScore pointer to player's score
@return None
*/
void room_two(int *nHealth, int *nScore);

/* Handles the third room where the player may pick up a gem
Precondition: nHealth, nScore, and nPickedGem must be valid pointers
@param nHealth pointer to player's health
@param nScore pointer to player's score
@param nPickedGem pointer to flag whether gem was picked
@return None
*/
void room_three(int *nHealth, int *nScore, int *nPickedGem);

/* Handles the fourth room with a water crossing
Precondition: nHealth, nScore, and nPickedGem must be valid pointers
@param nHealth pointer to player's health
@param nScore pointer to player's score
@param nPickedGem pointer to flag whether gem was picked
@return None
*/
void room_four(int *nHealth, int *nScore, int *nPickedGem);

/* Handles the fifth room where player can pick up a torch
Precondition: nHealth, nScore, nTorch, and nPickedGem must be valid pointers
@param nHealth pointer to player's health
@param nScore pointer to player's score
@param nTorch pointer to flag whether torch was taken
@param nPickedGem pointer to flag whether gem was picked
@return None
*/
void room_five(int *nHealth, int *nScore, int *nTorch, int *nPickedGem);

/* Handles the sixth room where bats attack the player
Precondition: nHealth, nScore, nTorch, and nPickedGem must be valid pointers
@param nHealth pointer to player's health
@param nScore pointer to player's score
@param nTorch pointer to flag whether player has torch
@param nPickedGem pointer to flag whether gem was picked
@return None
*/
void room_six(int *nHealth, int *nScore, int *nTorch, int *nPickedGem);

/* Handles the seventh room where the player chooses a path
Precondition: nHealth, nScore, and nPickedGem must be valid pointers
@param nHealth pointer to player's health
@param nScore pointer to player's score
@param nPickedGem pointer to flag whether gem was picked
@return None
*/
void room_seven(int *nHealth, int *nScore, int *nPickedGem);

/* Handles the eighth room where the player can open a door
Precondition: nHealth, nScore, nKey, nPickedGem, and nEndingType must be valid pointers
@param nHealth pointer to player's health
@param nScore pointer to player's score
@param nKey pointer to flag whether player has key
@param nPickedGem pointer to flag whether gem was picked
@param nEndingType pointer to current ending type
@return None
*/
void room_eight(int *nHealth, int *nScore, int *nKey, int *nPickedGem, int *nEndingType);

/* Handles the ninth room where the player finds a key
Precondition: nHealth, nScore, nKey, nPickedGem, and nEndingType must be valid pointers
@param nHealth pointer to player's health
@param nScore pointer to player's score
@param nKey pointer to flag whether player has key
@param nPickedGem pointer to flag whether gem was picked
@param nEndingType pointer to current ending type
@return None
*/
void room_nine(int *nHealth, int *nScore, int *nKey, int *nPickedGem, int *nEndingType);

/* Handles the tenth room where the player reaches the final treasure
Precondition: nHealth, nScore, nPickedGem, nEndingType, and nSword must be valid pointers
@param nHealth pointer to player's health
@param nScore pointer to player's score
@param nPickedGem pointer to flag whether gem was picked
@param nEndingType pointer to ending type
@param nSword pointer to flag whether sword was picked
@return None
*/
void room_ten(int *nHealth, int *nScore, int *nPickedGem, int *nEndingType, int *nSword);

/* Handles the final boss fight if player chooses to or encounters it
Precondition: nHealth and nScore must be valid pointers
@param nSword flag whether player has the sword
@param nHealth pointer to player's health
@param nScore pointer to player's score
@return None
*/
void boss_room(int nSword, int *nHealth, int *nScore, int *nEndingType);

/* Handles displaying the ending scene based on ending type
Precondition: nHealth, nScore, nEndingType, and nSword must be valid pointers
@param nHealth pointer to player's health
@param nScore pointer to player's score
@param nEndingType pointer to ending type
@param nSword pointer to flag whether sword was picked
@return None
*/
void endingScene(int *nHealth, int *nScore, int *nEndingType, int *nSword);

/* Displays the final stats of the player at the end of the game
Precondition: nHealth and nScore must be valid pointers
@param nHealth pointer to player's health
@param nScore pointer to player's score
@return None
*/
void endStats(int *nHealth, int *nScore);

void displayTitle()
{
    printf("\n\n\t\t\t *       _____   .     +      _           __     *  +  \n");
    printf("\t\t\t   +    /__   \\ |__   ___    / /  ___  ___| |_     *     .           \n");
    printf("\t\t\t x   *    / /\\/ '_ \\ / _ \\  / /  / _ \\/ __| __|   .        \n");
    printf("\t\t\t   .     / /  | | | |  __/ / /__| (_) \\__ \\ |_    +   *   .     \n");
    printf("\t\t\t *   +    \\/   |_| |_|\\___| \\____/\\___/|___/\\__|     .       \n");
    printf("\t\t\t      .       +        *         .         +      x                 \n\n");

    printf("          +       *     .                                   _____              .          *      +     \n");
    printf("     *       _____       _____     _______    ______   _____\\    \\ ___________      _____    _____     .\n");
    printf("  .     _____\\    \\_   /      |_   \\      |  |      | /    / |    |\\          \\    |\\    \\   \\    \\    *\n");
    printf("   +   /     /|     | /         \\   |     /  /     /|/    /  /___/| \\    /\\    \\    \\\\    \\   |    |   .\n");
    printf("     x/     / /____/||     /\\    \\  |\\    \\  \\    |/|    |__ |___|/  |   \\_\\    |    \\\\    \\  |    |    +\n");
    printf("  *   |     | |____|/ |    |  |    \\ \\ \\    \\ |    | |       \\        |      ___/      \\|    \\ |    |   .\n");
    printf("   +  |     |  _____  |     \\/      \\ \\|     \\|    | |     __/ __     |      \\  ____    |     \\|    |    *\n");
    printf("  .   |\\     \\\\\\    \\ |\\      /\\     \\ |\\         /| |\\    \\  /  \\   /     /\\ \\/    \\  /     /\\      \\   +\n");
    printf("  *   | \\_____\\|    | | \\_____/ \\_____\\| \\_______/ | | \\____\\/    | /_____/ |\\______| /_____/ /______/|   .\n");
    printf("  +   | |     /____/| | |     | |     | \\ |     | /  | |    |____/| |     | | |     ||      | |     | |   *\n");
    printf("  .    \\|_____|    ||  \\|_____|\\|_____|  \\|_____|/    \\|____|   | | |_____|/ \\|_____||______|/|_____|/    +\n");
    printf("   *         |____|/                                       |___|/                              .     x    \n");
    printf("        +        .        *         .        +        x         *        .         +        *           \n\n\n");

}

void displayCave()
{
    printf("\n\t\t+------------------------------------------------------------------------+\n");
    printf("\t\t|                   /   \\              /'\\       _             *         |\n");
    printf("\t\t|\\_..         /'.,/     \\_         .,'   \\     / \\_          /\\          |\n");
    printf("\t\t|    \\       /            \\      _/       \\_  /    \\     _   ><      *   |\n");
    printf("\t\t|     \\__,. /     your journey has begun... \\/.,   _|  _/ \\  \\/^\\/\\      |\n");
    printf("\t\t|          \\_/              \\  /',.,''\\      \\_ \\_/  \\/    \\_/__\\_/      |\n");
    printf("\t\t|                     _  \\/   /    ',../',.\\    _/      \\     /^^\\    *  |\n");
    printf("\t\t|          *        _/m\\  \\  /    |         \\  /.,/'\\   _\\  _/____\\_     |\n");
    printf("\t\t|           _      /MMmm\\  \\_     |          \\/      \\_/  \\/   /\\   \\    |\n");
    printf("\t\t|          / \\    |MMMMmm|   \\__   \\          \\_       \\   \\_  /__\\   \\_ |\n");
    printf("\t\t|         /   \\  /MMMMMMm|      \\   \\           \\       \\    \\  ><     \\ |\n");
    printf("\t\t|        /    |  |MMMMMMmm\\      \\___            \\_      \\_   \\_/\\_    \\_|\n");
    printf("\t\t|       /     |  |MMMMMMMMmm|____.'  /\\_           \\       \\   \\  \\     \\|\n");
    printf("\t\t|      /      \\  '.,___________...,,'   \\           \\   \\    \\   \\_ \\_  \\|\n");
    printf("\t\t|     /        \\        \\         |      \\    |__    \\   \\_   \\    \\  \\  |\n");
    printf("\t\t+------------------------------------------------------------------------+\n");
}

// START
int starting_screen(){
    char cReady;

    displayTitle();

   do { 
        printf(" >>> Are you ready to start your adventure? [Y/N]: ");
        scanf(" %c", &cReady);

        if (cReady == 'Y' || cReady == 'y') {
            displayCave();
            return 1;  // start game
        } 
        else if (cReady == 'N' || cReady == 'n') {
            printf("\n\nGo rot and die then.\n\n");
            return 0;  // exit game
        } 
        else printf("Invalid choice. Please enter Y or N.\n");
    } while(cChoice != 'Y' && cChoice != 'y' && cChoice != 'N' && cChoice != 'n');
}


// CHECK PLAYER'S STATS
void checkStats(int nHealth, int nScore){
    printf("\n================================== STATS =================================\n\n");

    printf("\tHealth: %d\n", nHealth);
    printf("\tScore:  %d\n", nScore);
}

void pauseMenu(int nHealth, int nScore){
    int nChoice;
    int flag = 1;

    while (flag){
        printf("\n================================== MENU ==================================\n\n");
        printf(" [1] Continue\n");
        printf(" [2] Check Stats\n\n");

        printf(">>> Enter your choice [1/2]: ");
        scanf("%d", &nChoice);

        if (nChoice == 1) flag = 0;
        else if(nChoice == 2) checkStats(nHealth, nScore);
        else printf("Invalid choice.\n"); 
    }
}

// 1ST ROOM - TWO PATHS
int room_one(int *nHealth, int *nScore){
    int nChoice;
    printf("\n\nYou step deeper into the cavern...\n");
    printf("Two paths branch out in front of you...\n\n");

    printf("\t   _________________________________________________________\n");
    printf("\t /|     -_-                                             _-  |\\\n");
    printf("\t/ |_-_- _                                         -_- _-   -| \\   \n");
    printf("\t  |                            _-  _--                      | \n");
    printf("\t  |                            ,                            |\n");
    printf("\t  |      .-'````````'.        '(`        .-'```````'-.      |\n");
    printf("\t  |    .` |           `.      `)'      .` |           `.    |          \n");
    printf("\t  |   /   |   ()        \\      U      /   |    ()       \\   |\n");
    printf("\t  |  |    |    ;         | o   T   o |    |    ;         |  |\n");
    printf("\t  |  |    |     ;        |  .  |  .  |    |    ;         |  |\n");
    printf("\t  |  |    |     ;        |   . | .   |    |    ;         |  |\n");
    printf("\t  |  |    |     ;        |    .|.    |    |    ;         |  |\n");
    printf("\t  |  |    |____;_________|     |     |    |____;_________|  |  \n");
    printf("\t  |  |   /  __ ;   -     |     !     |   /     `'() _ -  |  |\n");
    printf("\t  |  |  / __  ()        -|        -  |  /  __--      -   |  |\n");
    printf("\t  |  | /        __-- _   |   _- _ -  | /        __--_    |  |\n");
    printf("\t  |__|/__________________|___________|/__________________|__|\n");
    printf("\t /                                             _ -           \\\n");
    printf("\t/   -_- _ -             _- _---                       -_-  -_ \\\n\n");                                                 

    do {
        printf("  [1] Go to the left path.\n");
        printf("  [2] Go to the right path.\n\n");

        printf(">>> What would you like to do? [1/2]: ");
        scanf("%d", &nChoice);

        if(nChoice == 1) return 1;
        else if(nChoice == 2) return 2;
        else printf("There are only two paths. Make a decision.\n");
      
    } while (nChoice != 1 && nChoice != 2);
}

// 2ND ROOM - LOSE HEALTH
void room_two(int *nHealth, int *nScore){
    printf("\n==========================================================================\n\n");

    printf(" !!! You slipped and tumbled down onto a pile of rocks !!! \n\n");
    
        *nHealth -= 10;
        *nScore += 2;
    
    printf("You lost 10 health and gained 2 points!\n");

    pauseMenu(*nHealth, *nScore);
    room_four(nHealth, nScore, 0);

}

// 3RD ROOM - SHINY OBJECT
void room_three(int *nHealth, int *nScore, int *nPickedGem){
    printf("\n==========================================================================\n\n");

    printf("You see something shiny in the room.\n");
    printf("You approach the object...\n\n");

    int nChoice;
    *nPickedGem = 0; // to see if the gem was picked up

    // ask about picking up the gem
   do {
        printf("Do you want to pick it up?\n\n");
        printf("  [1] Pick it up\n");
        printf("  [2] Ignore it\n\n");
        printf(">>> Enter your choice [1/2]: ");
        scanf("%d", &nChoice);

        if(nChoice == 1){
            *nScore += 5;
            *nPickedGem = 1;

            printf("\n==========================================================================\n\n");

            printf("\n\t\t   . * _____ ____ _____      .\n");
            printf("\t\t    + /    /      \\    \\ *\n");
            printf("\t\t*   /____ /_________\\____\\   +\n");
            printf("\t\t .  \\    \\          /    /  .\n");
            printf("\t\t       \\  \\        /  /         .\n");
            printf("\t\t +        \\ \\    / /    *. \n");
            printf("\t\t    x       \\ \\/ /       .+\n");
            printf("\t\t *     .      \\/  x   .*    . \n\n");

            printf("\nYou picked up the shiny object and gained 5 points!\n");
        } else if(nChoice == 2) printf("\nYou walk past the shiny object.\n");
        else printf("\nInvalid choice. Please select 1 or 2.\n");
    } while (nChoice != 1 && nChoice != 2);
  
        printf("\nYou continue on deeper into the cave...\n");

        pauseMenu(*nHealth, *nScore);
        room_four(nHealth, nScore, nPickedGem);
}

// 4TH ROOM - BOAT
void room_four(int *nHealth, int *nScore, int *nPickedGem){
    printf("\n==========================================================================\n\n");
    printf("You face a water crossing.\n\n\n");

    printf("           +              v  ~.         v    +              *. \n");
    printf("   .             v           /|   .x             . \n");
    printf("         x                  / |             v           +. \n");
    printf("    .*               v     /__|__\\      v       +*.             . x   \n");
    printf("             *+          \\--------/                . \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~`~~~~~~'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("You can either take the old boat or swim across.\n\n");

    int nChoice;
    int nTorch = 0;

    do{
        printf("  [1] Take the boat\n");
        printf("  [2] Swim across\n\n");
        printf(">>> Enter your choice [1/2]: ");
        scanf("%d", &nChoice);

        if(nChoice == 1){
            printf("\nYou safely crossed the water using the boat!\n");
            break;
        } else if(nChoice == 2){
            *nHealth -= 20;
            printf("\nYou swam across but lost 20 health due to exhaustion.\n");
            break;
        } else printf("\nInvalid choice. Please enter 1 or 2.\n");
    } while (nChoice != 1 && nChoice != 2);

    pauseMenu(*nHealth, *nScore);
    // PASS ADDRESS &torch
    room_five(nHealth, nScore, &nTorch, nPickedGem);
}

// 5TH ROOM - TORCH
void room_five(int *nHealth, int *nScore, int *nTorch, int *nPickedGem){ 
    int nChoice;

    printf("\n==========================================================================\n\n");
    printf("You enter a well-lit room.\n"); 
    printf("You see a torch on the wall.\n\n");
    printf("\t      |\\\n");
    printf("\t      / \\\n");
    printf("\t      \\|/\n");
    printf("\t     .=|-._\n");
    printf("\t     |~'~~|)\n");
    printf("\t     |    |\n");
    printf("\t     |    |)\n");
    printf("\t     |    |\n");
    printf("\t \\// |    | \\|/\n");
    printf("\t  \\//|..  |\\//\n");
    printf("\t_\\\\\\\\\\\\\\__////////_\n");
    printf("\t'/////////\\\\\\\\\\\\\\\\\\`\n");
    printf("\t        //\\\\\n");
    printf("\t         //\\\n\n");

    do {
        // Torch decision
        printf("Would you like to take the torch?\n\n");
        printf("  [1] Yes\n");
        printf("  [2] No\n\n");
        printf(">>> Enter your choice [1/2]: ");
        scanf("%d", &nChoice);

        if(nChoice == 1){
            printf("\nYou took the torch.\n");
            *nTorch = 1;
            pauseMenu(*nHealth, *nScore);
            printf("You move on, the light helps a lot...\n");
            room_six(nHealth, nScore, nTorch, nPickedGem);
            return;
        } 
        else if(nChoice == 2){
            printf("\nYou move on, ignoring the torch.\n");
            *nTorch = 0;
            pauseMenu(*nHealth, *nScore);
            printf("It gets harder to see as you continue on...\n");
            room_six(nHealth, nScore, nTorch, nPickedGem);
            return;
        } 
        else printf("\nInvalid choice. Please enter 1 or 2.\n\n");
    } while (nChoice != 1 && nChoice != 2);       
}

// 6TH ROOM - BATS
void room_six(int *nHealth, int *nScore, int *nTorch, int *nPickedGem){ 
    printf("\n==========================================================================\n\n");
    printf("You entered a very dark room...\n\n");
    printf("....._      \n");
    printf(" `.   ``-.                               .-----.._\n");
    printf("   `,     `-.                          .:      /`\n");
    printf("     :       `\"..                 ..-``       :\n");
    printf("     /   ...--:::`n            n.`::...       :\n");
    printf("     `:``      .` ::          /  `.     ``---..:.\n");
    printf("       `\\    .`  ._:   .-:   ::    `.     .-``\n");
    printf("         :  :    :_\\\\_/: :  .::      `.  /\n");
    printf("         : /      \\\\-../:/_.`-`         \\\\ :\n");
    printf("         :: _.._  q` p ` /`             \\\\|\n");
    printf("         :-`    ``(_. ..-----hh``````/-._:\n");
    printf("                     `:      ``     /     `\n");
    printf("                     E:            /\n");
    printf("                      :          _/ \n");
    printf("                      :    _..-``\n");
    printf("                      l--``\n\n");
    printf(" !!! You are being swarmed by bats !!! \n\n");

    if(*nTorch){
        *nScore += 5;
        printf("Luckily, you have a torch to scare them away.\n\n");
        printf("             ...  \n");
        printf("          :::;(;:::  \n");
        printf("        .::;.) );:::.  \n");
        printf("       :::;`(,' (,;:::  \n");
        printf("      :::;;). (, (';:::  \n");
        printf("      :::;( ) ; ' );;::   \n");
        printf("      '::;')_,_)_(`;::'    \n");
        printf("        '::[_____]::'     \n");
        printf("            \\_ _/          \n");
        printf("             |#|_          \n");
        printf("        __.-'(__ )    \n");
        printf("         '-. \\___ )    \n");
        printf("          _.\\_)__ )  \n");
        printf("        _   (__ )   \n");
        printf("          `' -\\#/'    \n\n");
        printf("The bats flee from the light of your torch.\n\n");
        printf("You gained 5 points!\n");
      
        pauseMenu(*nHealth, *nScore);
    } else {
        *nHealth -= 15;
        printf("Without a torch, the bats attack you! \n");
        printf("You silently regret not taking the torch...\n\n");
        printf("You lost 15 health.\n");
        pauseMenu(*nHealth, *nScore);
    }
    room_seven(nHealth, nScore, nPickedGem); 
}

// 7TH ROOM - TWO PATHS
void room_seven(int *nHealth, int *nScore, int *nPickedGem){ 
    int nChoice;
    int nKey = 0;
    int nEndingType = 0;
    int flag = 1;

    printf("\n==========================================================================\n\n");

    printf("This feels oddly familiar...\n");
    printf("Two paths branch out in front of you... again?\n\n");
    printf("You wonder if you went in a huge circle\n\n");

    printf("\t   ============================================================\n");
    printf("\t  ||    -_-                                            _-     ||\n");
    printf("\t  ||_-_- _                                      -_- _-        ||\n");
    printf("\t  ||                         _-  _--                          ||\n");
    printf("\t  ||                             ,                            ||\n");
    printf("\t  ||     .-\"````````\"-.      '(`        .-\"```````\"-.         ||\n");
    printf("\t  ||   .` |            `.     `)'     .` |            `.      ||\n");
    printf("\t  ||  /   |              \\     U     /   |              \\     ||\n");
    printf("\t  || |    |               | o  T  o |    |               |    ||\n");
    printf("\t  || |    |               |  . | .  |    |               |    ||\n");
    printf("\t  || |    |               |   .|.   |    |               |    ||\n");
    printf("\t  || |    |_______________|    |    |    |_______________|    ||\n");
    printf("\t  || |   /  __     -      |    !    |   /     `'   _ -   |    ||\n");
    printf("\t  || |  / __             -|         |  /  __--      -    |    ||\n");
    printf("\t  || | /        __-- _    |  _- _   | /        __--_     |    ||\n");
    printf("\t  ||_|____________________|_________|_____________________|____||\n");
    printf("\t   \\                                             _ -           /\n");
    printf("\t    \\   -_- _ -            _- _---                       -_-  -/ \n\n");

    while(flag){
        printf("  [1] Go to the left path.\n");
        printf("  [2] Go to the right path.\n\n");

        printf(">>> What would you like to do? [1/2]: ");
        scanf("%d", &nChoice);

        if(nChoice == 1) {
            flag = 0;
            room_eight(nHealth, nScore, &nKey, nPickedGem, &nEndingType);
        }
        else if(nChoice == 2){
            flag = 0;
            room_nine(nHealth, nScore, &nKey, nPickedGem, &nEndingType);
        }
        else printf("There are only two paths. Make a decision.\n");
    }
}

void room_eight(int *nHealth, int *nScore, int *nKey, int *nPickedGem, int *nEndingType){ 
    int nSword = 0;
    int nChoice;
    
    printf("\n==========================================================================\n\n");
    printf("      ______\n");
    printf("   ,-' ;  ! `-.\n");
    printf("  / :  !  :  . \\\n");
    printf(" |_ ;   __:  ;  |\n");
    printf(" )| .  :)(.  !  |\n");
    printf(" |\"    (##)  _  |\n");
    printf(" |  :  ;`'  (_) (\n");
    printf(" |  :  :  .     |\n");
    printf(" )_ !  ,  ;  ;  |\n");
    printf(" || .  .  :  :  |\n");
    printf(" |\" .  |  :  .  |\n");
    printf(" |   _;----.___|\n\n");

    do {
        printf("Do you want to open the door?\n\n");
        printf("  [1] Yes\n");
        printf("  [2] No\n\n");
        printf(">>> Enter your choice [1/2]: ");
        scanf("%d", &nChoice);

        if(nChoice == 1){
            if(*nKey == 1){   
                printf("\n==========================================================================\n\n");
                printf("You unlocked the door using the key!\n");
                printf("You may proceed through the door.\n");

                pauseMenu(*nHealth, *nScore);
                room_ten(nHealth, nScore, nPickedGem, nEndingType, &nSword);
                return;
            }
            else {
            printf("\nYou try opening the door\n");
            printf("The door seems to be locked...\n\n");
            }
        } 
        else if(nChoice == 2){
            printf("\nI'd rather try peeking through...\n");
            printf(" ,,,,,,,,,,,,,,,,,,,,\n");
            printf("&&&&&&&&&&&&&&&&&&&&/\n");
            printf("&&&&&&&M|\" \"|M&&&&&&/\n");
            printf("&&&&&&M|     |M&&&&&/\n");
            printf("&&&&&&&M|   |M&&&&&&/\n");
            printf("&&&&&&&&M| |M&&&&&&&/\n");
            printf("&&&&&&&&M\\_/M&&&&&&&/\n");
            printf("&&&&&&&&&&&&&&&&&&&&/\n\n");
            printf("You see nothing...\n");
        } 
        else {
          printf("\nInvalid choice. Please enter 1 or 2.\n");
          continue;
        }

        printf("You head back and try the other path.\n");
        pauseMenu(*nHealth, *nScore);
        room_seven(nHealth, nScore, nPickedGem);
      
    } while (nChoice != 1 && nChoice != 2);
}

void room_nine(int *nHealth, int *nScore, int *nKey, int *nPickedGem, int *nEndingType){ 
    int nChoice;

    if(nKey == 0){
        printf("There's no use looking around here, you already have the key");
        room_seven(nScore, nHealth, nPickedGem);
    }

    printf("\n==========================================================================\n\n\n");

    printf("    _.-'```\"\"\"``\"-._\n");
    printf("    /\"`                 '.\n");
    printf("    `':.,_   *.,-             \"._\n");
    printf("         \\`'-._                 `'-._\n");
    printf("          \\    `:._                 `'-._          _\n");
    printf("          |      \\ `:_                     `\"--\"--\"``\n");
    printf("          |       \\   `:_\n");
    printf("          |      :|    \\ '.\n");
    printf("          |       |     |  `:_\n");
    printf("          |       |:    |     `:_\n");
    printf("          |:      |     |\n");
    printf("          |       |\n");
    printf("          |\n");
    printf("         |\n");

    printf("! You are met with a sudden flash of light! \n");
    printf("It's been so long since you've seen the sky...\n\n");

    printf("You notice something glistening on the edge of the cliff\n\n");

    do {  
        printf("Do you want to take the risk and climb up?\n\n");
        printf("  [1] Yes\n");
        printf("  [2] No\n\n");
        printf(">>> Enter your choice [1/2]: ");
        scanf("%d", &nChoice);

        if(nChoice == 1){
            *nHealth -= 10;
            if(*nHealth <= 0){
                *nEndingType = 1;
                // you died
                endingScene(nHealth, nScore, nEndingType, 0);
            }
            printf("\n! A rock tumbled down on your way up !\n\n");

            printf(" ,.  __,.\n");
            printf(" /`  -_`\\\n");
            printf("`\\ \\_ ’/\n\n");

            printf("You lost 10 health points!\n");
            pauseMenu(*nHealth, *nScore);

            printf("\n==========================================================================\n\n");
            printf("You approach the edge of the cliff...\n\n");
            printf("              ~>~...:**         ~:                 \n");
            printf("            *=  .~==.  .*.     ~**~                \n");
            printf("           =. :^.    ~=  ^. :>>.  :>>:             \n");
            printf("          := :~       .>  *    .^^                 \n");
            printf("          =: ~.        )  =     ::                 \n");
            printf("          .* :=       :*  *          .             \n");
            printf("           =.  ^:   .^~  ^:          >=             \n");
            printf("            :*.  .:.   ~. .*~      :*~^=.           \n");
            printf("              .**~~~=*~ ~*.  *=      =              \n");
            printf("                          .).  ~^                  \n");
            printf("            ^.              .*~  :*.               \n");
            printf("                .^      ~     :^=  .^:             \n");
            printf("              .=*:^:         ^:  =^   ^~            \n");
            printf("                *^:         .**    :^.=~            \n");
            printf("                 :         ^=+     ~=:              \n");
            printf("                    :(.         ==^.               \n\n");
            printf("A key!\n\n");
            printf("This might just be the key for the door.\n");
          
            *nKey = 1;
          
            pauseMenu(*nHealth, *nScore);
            room_eight(nHealth, nScore, nKey, nPickedGem, nEndingType);
        }
        else if(nChoice == 2){
            printf("The climb is too risky\n\n");
            
            printf("    _.-'```\"\"\"``\"-._\n");
            printf("    /\"`                 '.\n");
            printf("    `':.,_   *.,-             \"._\n");
            printf("         \\`'-._                 `'-._\n");
            printf("          \\    `:._                 `'-._          _\n");
            printf("          |      \\ `:_                     `\"--\"--\"``\n");
            printf("          |       \\   `:_\n");
            printf("  =-0;    |      :|    \\ '.\n");
            printf("          |       |     |  `:_\n");
            printf("          |       |:    |     `:_\n");
            printf("          |:      |     |\n");
            printf("          |       |\n");
            printf("          |\n");
            printf("         |\n");

            printf("!!! The key fell off !!!\n\n");

            printf("You take a quick look down, it fell into a deep pit...\n\n");

            printf("     _-------``_-_. ,\n");
            printf("  _-=;          =+,   \n");
            printf("./,;     =-0;     :`\\\n");
            printf("`\\_,             .__/+/\n");
            printf("   \\-___,..____,/-/\n\n");

            printf("You regret taking the key...\n");
            printf("That was supposed to be the key to the door.\n\n");

            *nEndingType = 2;

            printf("You realize you are trapped after circling through the cave...\n");
            
            pauseMenu(*nHealth, *nScore);
            endingScene(nHealth, nScore, nEndingType, 0);
        }
    } while (nChoice != 1 && nChoice != 2);
}

void room_ten(int *nHealth, int *nScore, int *nPickedGem, int *nEndingType, int *nSword) {
    int nChoice;
    int nFlag = 1;

    printf("\n==========================================================================\n\n");

    printf("Congratulations! You have reached the end of the cavern!\n\n");

    printf("*******************************************************************************\n");
    printf("          |                   |                  |                     |\n");
    printf(" _________|________________.=\"\"_;=.______________|_____________________|_______\n");
    printf("|                   |  ,-\"_,=\"\"     `\"=. |                  |\n");
    printf("|___________________|__\"=._o`\"-._        `\"=.______________|___________________\n");
    printf("          |                `\"=._o`\"=._      _`\"=._                     |\n");
    printf(" _________|_____________________:=._o \"=._.\"_.-=\"'\"=.__________________|_______\n");
    printf("|                   |    __.--\" , ; `\"=._o.\" ,-\"\"\"-._ \".   |\n");
    printf("|___________________|_._\"  ,. .` ` `` ,  `\"-._\"-._   \". '__|___________________\n");
    printf("          |           |o`\"=._` , \"` `; .\". ,  \"-._\"-._; ;              |\n");
    printf(" _________|___________| ;`-.o`\"=._; .\" ` '`.\"\\` . \"-._ /_______________|_______\n");
    printf("|                   | |o;    `\"-.o`\"=._``  '` \" ,__.--o;   |\n");
    printf("|___________________|_| ;     (#) `-.o `\"=. `_.--\"_o.-; ;___|___________________\n");
    printf("____/______/______/___|o;._    \"      `.o|o_.--\"    ;o;____/______/______/____\n");
    printf("/______/______/______/ _\"=._o--._        ; | ;        ; ;/______/______/______/_\n");
    printf("____/______/______/______/__\"=._o--._   ;o|o;     _._;o;____/______/______/____\n");
    printf("/______/______/______/______/____\"=._o._; | ;_.--\"o.--\"_/______/______/______/_\n");
    printf("____/______/______/______/______/_____\"=.o|o_.--\"\"___/______/______/______/____\n");
    printf("/______/______/______/______/______/______/______/______/______/______/______/\n");
    printf("*******************************************************************************\n\n");

    printf("You are left with one final decision...\n");

    while (nFlag) {
        printf(" [1] Leave the Cavern\n");
        printf(" [2] Stay to collect your riches\n\n");
        printf(">>> Enter your choice [1/2]: ");
        scanf("%d", &nChoice);

        if (nChoice == 1) {
            // Player leaves
            *nEndingType = 3;
            nFlag = 0;
        }
        else if (nChoice == 2) {
            // Player stays, gets sword
            printf("\n==========================================================================\n\n");
            printf("Among the riches you also find a sword!\n\n");

            printf("                           ___\n");
            printf("                          ( ((\n");
            printf("                           ) ))\n");
            printf("  .::.                    / /(\n");
            printf(" ' .-;-.-.-.-.-.-.-.-.-/| ((::::::::::::::::::::::::::::::::::::::::::::::.._ \n");
            printf("( ( ( ( ( ( ( ( ( ( ( ( |  ))   -====================================-      _.> \n");
            printf(" ` `-;-`-`-`-`-`-`-`-`-\\| ((::::::::::::::::::::::::::::::::::::::::::::::'' \n");
            printf("  `::'                    \\ \\(\n");
            printf("                           ) ))\n");
            printf("                          (_((\n\n");

            *nSword = 1;
            *nEndingType = 3;
            nFlag = 0;
        }
        else {
            printf("Invalid choice.\n");
        }
    }

    // Award gem bonus AFTER choice, WITHOUT changing ending type
    if (*nPickedGem == 1) {
        printf("\n==========================================================================\n\n");
        printf("Earlier, you picked up the shiny object,\n");
        printf("the gem finally returned to where it belongs thanks to you!\n\n");
        printf("You received a bonus of 20 points!\n");
        *nScore += 20;
    }
    endingScene(nHealth, nScore, nEndingType, nSword);

}


void boss_room(int nSword, int *nHealth, int *nScore, int *nEndingType){
    int nAtk = 0;
    int nBlockedDmg = 3;
    int nBossHp = 40;

    if (nSword == 1) nBlockedDmg = 0;

    printf("\n==========================================================================\n\n");

    printf("You face one final obstacle before you end your adventure... \n!!! A BEAST !!!\n\n");

    printf("                 \\ __\n");
    printf("--==/////////////[})))==*\n");
    printf("                 / \\ '          ,|\n");
    printf("                    `\\`\\      //|                             ,|\n");
    printf("                      \\ `\\  //,/'                           -~ |\n");
    printf("   )             _-~~~\\  |/ / |'|                       _-~  / ,\n");
    printf("  ((            /' )   | \\ / /'/                    _-~   _/_-~|\n");
    printf(" (((            ;  /`  ' )/ /''                 _ -~     _-~ ,/'\n");
    printf(" ) ))           `~~\\   `\\\\/'/|'           __--~~__--\\ _-~  _/, \n");
    printf("((( ))            / ~~    \\ /~      __--~~  --~~  __/~  _-~ /\n");
    printf(" ((\\~\\           |    )   | '      /        __--~~  \\-~~ _-~\n");
    printf("    `\\(\\    __--(   _/    |'\\     /     --~~   __--~' _-~ ~|\n");
    printf("     (  ((~~   __-~        \\~\\   /     ___---~~  ~~\\~~__--~ \n");
    printf("      ~~\\~~~~~~   `\\-~      \\~\\ /           __--~~~'~~/\n");
    printf("                   ;\\ __.-~  ~-/      ~~~~~__\\__---~~ _..--._\n");
    printf("                   ;;;;;;;;'  /      ---~~~/_.-----.-~  _.._ ~\\\n");     
    printf("                  ;;;;;;;'   /      ----~~/         `\\,~    `\\ \\\n");        
    printf("                  ;;;;'     (      ---~~/         `:::|       `\\\\.\n");      
    printf("                  |'  _      `----~~~~'      /      `:|        ()))),\n");      
    printf("            ______/\\/~    |                 /        /         (((((())\n");  
    printf("          /~;;.____/;;'  /          ___.---(   `;;;/             )))'`))\n");
    printf("         / //  _;______;'------~~~~~    |;;/\\    /                ((   (\n");
    printf("        //  \\ \\                        /  |  \\;;,\\                 `   \n");
    printf("       (<_    \\ \\                    /',/-----'  _>\n"); 
    printf("        \\_|     \\\\_                 //~;~~~~~~~~~\n"); 
    printf("                 \\_|               (,~~\n");   
    printf("                                    \\~\\\n");
    printf("                                     ~~\n\n");

    printf("\nBut fear not, if you claimed the Sword of RNG from the previous room, you still have a chance!");

    while(nBossHp >= 0 && *nHealth >= 0){
        printf("\n\n==========================================================================\n\n");
        printf("The boss is attacking you! What do you do?\n\n");
        printf(" [1] Attack!\n");
        printf(" [2] Block!\n");
        printf(" [3] Check Stats\n\n");
        printf(">>> What would you like to do? [1-3] ");

        int nChoice;
        scanf("%d", &nChoice);
        if (nChoice == 1) {
            if (nSword == 1) nAtk = rand() % 10 + 2;
            else if (nSword == 0) nAtk = 2;
            nBossHp -= nAtk;

            int nBossAtk = rand()% 8 + 2;
            *nHealth -= nBossAtk;

            printf("\nYou hit the boss for %d damage!\n", nAtk);
            printf("The boss hit you in return for %d damage!", nBossAtk);
        } else if (nChoice == 2){
            *nHealth -= nBlockedDmg;
            printf("You block an attack from the beast! You take %d damage!\n\n", nBlockedDmg);
        } else if (nChoice == 3){
            checkStats(*nHealth, *nScore);
        } else {
            printf("You couldn't decide! You lost time and the beast launches at you!\n");
            printf("All you can do is try to make puppy eyes with the beast!");
            *nHealth -= 0;
        }
    }

    if (nBossHp <= 0 && *nHealth <= 0){
        printf("\n==========================================================================\n\n");
        printf("Nice try - You went above and beyond! However, the beast clipped on you!\n");
        printf("But fear not! For you aurafarmed while it was at it!\n\n");
        printf("You lose 999 points to conclude your journey!\n");
        printf("At least you slayed the beast as it slayed you too! \n");
        *nEndingType = 1;
        *nScore -= 999;

    } else if (*nHealth <= 0) {
        printf("\n==========================================================================\n\n");
        printf("Nice try - You went above and beyond! However, the beast clipped on you!\n\n");
        printf("You lose 999 points to conclude your journey!\n");
        printf("Why did you even show up.. You could've left... \n");
        *nEndingType = 1;   // You died
        *nScore -= 999;

    } else if (nBossHp <= 0){
        printf("\n==========================================================================\n\n");
        printf("Congratulations! You went above and beyond and aurafarmed on the beast!\n");
        printf("You gain an additional 50 points to conclude your journey!\n");
        *nEndingType = 4;
        *nScore += 50;
    }
    endingScene(nHealth, nScore, nEndingType, &nSword);
}

void endingScene(int *nHealth, int *nScore, int *nEndingType, int *nSword) {
    printf("\n==========================================================================\n\n");

    switch(*nEndingType){
        case 1:
            printf("\t[ YOU DIED ]\n\n");
            printf("                  _<\\\n");
            printf("                 (   >\n");
            printf("                 __)(\n");
            printf("           _____/  //   ___\n");
            printf("          /        \\\\  /  \\\\__\n");
            printf("          |  _     //  \\     ||\n");
            printf("          | | \\\\    \\\\  / _   ||\n");
            printf("          | |  |    \\\\/ | \\  ||\n");
            printf("          | |_/     |/  |  | ||\n");
            printf("          | | \\\\     /|  |_/  ||\n");
            printf("          | |  \\\\    \\|  |     >_ )\n");
            printf("          | |   \\\\. _|\\  |    < _|=\n");
            printf("          |          /_.| .  \\/\n");
            printf("  *       | *   **  / * **  |\\)/)    **\n");
            printf("   \\\\))ejm97/.,(//,,..,,\\\\||(,wo,\\ ).((//\n");
            printf("                             -  \\)\n\n");

            endStats(nHealth, nScore);
            break;

        case 2:
            printf("\t[ YOU ARE TRAPPED FOREVER ]\n\n");
            printf("You failed to obtain the key and are left to rot trapped in the cave.\n\n");
            printf("                  _<\\\n");
            printf("                 (   >\n");
            printf("                 __)(\n");
            printf("           _____/  //   ___\n");
            printf("          /        \\\\  /  \\\\__\n");
            printf("          |  _     //  \\     ||\n");
            printf("          | | \\\\    \\\\  / _   ||\n");
            printf("          | |  |    \\\\/ | \\  ||\n");
            printf("          | |_/     |/  |  | ||\n");
            printf("          | | \\\\     /|  |_/  ||\n");
            printf("          | |  \\\\    \\|  |     >_ )\n");
            printf("          | |   \\\\. _|\\  |    < _|=\n");
            printf("          |          /_.| .  \\/\n");
            printf("  *       | *   **  / * **  |\\)/)    **\n");
            printf("   \\\\))ejm97/.,(//,,..,,\\\\||(,wo,\\ ).((//\n");
            printf("                             -  \\)\n\n");

            endStats(nHealth, nScore);
            break;

        case 3:
        {
            printf("\t[ YOU FOUND YOUR WAY OUT ]\n\n");
            printf("Congratulations! You have reached the end of the cavern!\n\n");
            printf("        _    .  ,   .           .\n");
            printf("    *  / \\_ *  / \\_      _  *        *   /\\'__        *\n");
            printf("      /    \\  /    \\,   ((        .    _/  /  \\  *'.\n");
            printf(" .   /\\/\\  /\\/ :' __ \\_  `          _^/  ^/    `--.\n");
            printf("    /    \\/  \\  _/  \\-'\\      *    /.^_   \\_   .'\\  *\n");
            printf("  /\\  .-   `. \\/     \\ /==~=-=~=-=-;.  _/ \\ -. `_/   \\\n");
            printf(" /  `-.__ ^   / .-'.--\\ =-=~_=-=~=^/  _ `--./ .-'  `-\n");
            printf("/        `.  / /       `.~-^=-=~=^=.-'      '-._ `._\n");

            printf("\n\tor did you..?\n\n");
            printf(" [1] YES! Get me out of here!\n");
            printf(" [2] Perhaps I'm not...\n\n");

            int nChoice;

            printf("Are you satisfied with your journey's end?\n");
            printf(">>> Enter your choice [1/2]: ");
            scanf("%d", &nChoice);

            if (nChoice == 1){
                printf("\nYou make your way out triumphantly with your loot!\n\n");
                endStats(nHealth, nScore);
                return;
            } else if (nChoice == 2) {
                boss_room(*nSword, nHealth, nScore, nEndingType);
                return;
            } else {
                printf("You hesitated and lost your chance.\n");
                endStats(nHealth, nScore);
                return;
            } 
        }
        case 4:
            printf("Congratulations! You defeated the beast of the cavern and escaped proudly!\n\n");
            printf("        _    .  ,   .           .\n");
            printf("    *  / \\_ *  / \\_      _  *        *   /\\'__        *\n");
            printf("      /    \\  /    \\,   ((        .    _/  /  \\  *'.\n");
            printf(" .   /\\/\\  /\\/ :' __ \\_  `          _^/  ^/    `--.\n");
            printf("    /    \\/  \\  _/  \\-'\\      *    /.^_   \\_   .'\\  *\n");
            printf("  /\\  .-   `. \\/     \\ /==~=-=~=-=-;.  _/ \\ -. `_/   \\\n");
            printf(" /  `-.__ ^   / .-'.--\\ =-=~_=-=~=^/  _ `--./ .-'  `-\n");
            printf("/        `.  / /       `.~-^=-=~=^=.-'      '-._ `._\n");
    }
}

void endStats(int *nHealth, int *nScore){
    printf("\n==========================================================================\n\n");
    printf("Final Health: %d | Final Score: %d\n", *nHealth, *nScore);
}

int main(){
    int nHealth, nScore, nPickedGem, nTorch, nKey, nEndingType, nSword;
    int playAgain = 1;

    while(playAgain) {
        // RESET VALUES EVERY GAME
        nHealth = 50;
        nScore = 0;
        nPickedGem = 0;
        nTorch = 0;
        nKey = 0;
        nEndingType = 0;
        nSword = 0;

        if(starting_screen()) {
            int path = room_one(&nHealth, &nScore);

            if(path == 1) room_two(&nHealth, &nScore);
            else if (path == 2) room_three(&nHealth, &nScore, &nPickedGem);
        } else return 0;

        endingScene(&nHealth, &nScore, &nEndingType, &nSword);

        char cChoice;
        printf("Would you like to play again? [Y/N]: ");
        scanf(" %c", &cChoice);

        if (cChoice == 'Y' || cChoice == 'y'){
            playAgain = 1;
        } else if(cChoice == 'N' || cChoice == 'n') {
            printf("\nThanks for playing!\n");
            playAgain = 0;
        } else {
            printf("Invalid choice.");
        }
    }
    return 0;

}
