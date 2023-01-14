#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

/* Rock Paper Scissors (RPS) */
typedef enum {
    WIN,
    LOSS,
    DRAW,
    INVALID
}rps_result; 

int play_again(char val)
{
    int ret = 0;
    
    if(val == 'Y' || val == 'y')
        ret = 1;
    
    return ret;
}

/*
Checks the result based on the inputs from the user and computer.
When both values are same, that means it is a DRAW.
[Rock, Paper, Scissors]
From the above line we can form a logic that the current beats the previous: 
    - paper beats rock
    - scissors beats paper
    - rock beats scissors
So we need to check whether the comp_val is the next of the user_val. 
*/
int check_result(int user_val, int comp_val)
{
    if(user_val == -1)
        return INVALID;

    else if(user_val == comp_val)
        return DRAW;
   
    else if(comp_val == (user_val+1)%3)
        return LOSS;
    
    else
        return WIN;
}

/* 
Converts the user input to the integer value, based on 
the number 
0 = Rock
1 = Paper
2 = Scissors
*/
void user_played(char input, int *user_val)
{
    switch(input)
    {
        case 'R':
        case 'r':
            *user_val = 0;
        break;

        case 'P':
        case 'p':
            *user_val = 1;
        break;

        case 'S':
        case 's':
            *user_val = 2;
        break;
        
        default:
            *user_val = -1;
        break;
    }
}

/*
Function that copies the computer value into the char array,
so that we can display it to the user.
*/
void computer_played(int val, char *comp_p)
{
    switch (val)
    {
    case 0:
        strcpy(comp_p, "ROCK");
        break;
    
    case 1:
        strcpy(comp_p, "PAPER");
        break;

    case 2:
        strcpy(comp_p, "SCISSOR");
        break;

    default:
        break;
    }
}

int main()
{
    char input, retry;
    int comp_val, user_val, games_played = 0, result, wins = 0, losses = 0, draw = 0;
    char comp_p[8] = {0}; 

    srand(time(0));

    do
    {
        ++games_played;

        printf("\nEnter Rock(R)/Paper(P)/Scissor(S): ");
        scanf(" %c", &input);

        user_played(input, &user_val);

        comp_val = rand() % 3;

        computer_played(comp_val, comp_p);
        printf("Computer Played: %s\n", comp_p);

        result = check_result(user_val, comp_val);
        if(result == INVALID)
        {
            printf("Invalid value entered: %c\n", input);
            printf("Please enter correct Value (Rock(R)/Paper(P)/Scissor(S))\n");
        }
        else if(result == WIN)
        {
            ++wins;
            printf("YOU WON !!!\n");
        }
        else if(result == LOSS)
        {
            ++losses;
            printf("Sorry, you lost\n");
        }
        else
        {
            ++draw;
            printf("It's a DRAW !\n");
        }
        
        printf("\nWant to Play Again? (Y/N) : ");
        scanf(" %c", &retry);

    }while(play_again(retry));

    printf("\nTotal Games Played: %d\n", games_played);
    printf("Games Won: %d\n", wins);
    printf("Games Lost: %d\n", losses);
    printf("Games Draw: %d\n", draw);
    printf("Win Percentage: %lf\n", ((float)wins/(float)games_played)*100);
}
