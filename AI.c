/* Bismillahir Rahmanir Raheem
   Author: Farid Islam
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define MAX_SIZE 100000

typedef struct conditional_data Conditional_data;
struct conditional_data
{
    char condition[300];
    int move;
    int value;
};

// Global variable declare

char BP[11]; // Board Position
Conditional_data O_win_con[MAX_SIZE], O_draw_con[MAX_SIZE], X_win_con[MAX_SIZE], X_draw_con[MAX_SIZE];
int num_OWC = 0, num_ODC = 0, num_XWC = 0, num_XDC = 0;
Conditional_data temp_Omove[5], temp_Xmove[5];
int index_Omove, index_Xmove;
int isUserFirstMove = 1;

// Function prototype declare

void menu();
void play();
void display_board();
void reset_board();
void data_read_from_file();
int winning_check();
void O_Turn();
void X_Turn();
int move_from_DB(char player);
int move_from_user();
void display_clean();
void temporary_data_processing(Conditional_data *temp_data, int *index, int move);
void get_board_condition(char *board_condition);
void data_save_to_file();
void data_merge(char game_result, int game_status);
void board_print(char *string);
void display_data(int input);
void display_database_info();
void user_vs_computer();
void computer_vs_user();

int main()
{
    srand(time(NULL));
    data_read_from_file();
    _getch();

    while (1)
    {
        system("cls");

        display_database_info();
        menu();

        printf("Enter choice: ");
        char choice = _getch();
        printf("%c\n", choice);

        switch (choice)
        {
        case '1':
            display_data(1);
            break;
        case '2':
            display_data(2);
            break;
        case '3':
            display_data(3);
            break;
        case '4':
            display_data(4);
            break;
        case '5':
            display_data(5);
            break;
        case 'p':
            play();
            break;
        case 'e':
            return 0;

        default:
            printf("Wrong input!!!\n");
            break;
        }

        printf("Enter to continue to go main menu...");
        _getch();
        //printf("\n\n\n");
    }

    return 0;
}

void board_print(char *string)
{
    int next_digit_found = 0, next_quote_found = 0;
    int temp_digit;
    char temp_char;

    for (int i = 0; string[i] != '\0'; i++)
    {
        if (next_digit_found == 1 && next_quote_found == 1)
        {
            // printf("%d = %c\n", temp_digit, string[i]);
            // _getch();
            BP[temp_digit] = string[i];
            next_digit_found = 0;
        }
        else
        {
            if ('1' <= string[i] && '9' >= string[i])
            {
                next_digit_found = 1;
                temp_digit = string[i] - '0';
            }
            if (string[i] == '\'')
            {
                // printf("%c\n", string[i]);
                // _getch();
                next_quote_found = !next_quote_found;
            }
        }
    }

    printf("\n");
    printf("\t  %c | %c | %c\n", BP[1], BP[2], BP[3]);
    printf("\t____|___|____\n");
    printf("\t  %c | %c | %c\n", BP[4], BP[5], BP[6]);
    printf("\t____|___|____\n");
    printf("\t  %c | %c | %c\n", BP[7], BP[8], BP[9]);
    printf("\t    |   |     \n");

    return;
}

void display_database_info()
{
    printf("\n\n");
    printf("MAX_SIZE = %d\n", MAX_SIZE);
    printf("num_OWC = %d\n", num_OWC);
    printf("num_ODC = %d\n", num_ODC);
    printf("num_XWC = %d\n", num_XWC);
    printf("num_XDC = %d\n", num_XDC);
    printf("\n\n");
}

void display_data(int input)
{
    printf("\n\nMAX_SIZE = %d\n\n", MAX_SIZE);

    if (input == 1)
    {
        printf("num_OWC = %d\n\n", num_OWC);
        for (int i = 0; i < num_OWC; i++)
        {
            printf("%s = %d = %d\n", O_win_con[i].condition, O_win_con[i].move, O_win_con[i].value);
            board_print(O_win_con[i].condition);
        }
    }
    else if (input == 2)
    {
        printf("num_ODC = %d\n\n", num_ODC);
        for (int i = 0; i < num_ODC; i++)
        {
            printf("%s = %d = %d\n", O_draw_con[i].condition, O_draw_con[i].move, O_draw_con[i].value);
            board_print(O_draw_con[i].condition);
        }
    }
    else if (input == 3)
    {
        printf("num_XWC = %d\n\n", num_XWC);
        for (int i = 0; i < num_XWC; i++)
        {
            printf("%s = %d = %d\n", X_win_con[i].condition, X_win_con[i].move, X_win_con[i].value);
            board_print(X_win_con[i].condition);
        }
    }
    else if (input == 4)
    {
        printf("num_XDC = %d\n\n", num_XDC);
        for (int i = 0; i < num_XDC; i++)
        {
            printf("%s = %d = %d\n", X_draw_con[i].condition, X_draw_con[i].move, X_draw_con[i].value);
            board_print(X_draw_con[i].condition);
        }
    }
    else if (input == 5)
    {
        printf("\n\n\n");

        printf("num_OWC = %d\n\n", num_OWC);
        for (int i = 0; i < num_OWC; i++)
        {
            printf("%s = %d = %d\n", O_win_con[i].condition, O_win_con[i].move, O_win_con[i].value);
            //board_print(O_win_con[i].condition);
        }

        printf("\n\n\n");

        printf("num_ODC = %d\n\n", num_ODC);
        for (int i = 0; i < num_ODC; i++)
        {
            printf("%s = %d = %d\n", O_draw_con[i].condition, O_draw_con[i].move, O_draw_con[i].value);
            //board_print(O_draw_con[i].condition);
        }

        printf("\n\n\n");

        printf("num_XWC = %d\n\n", num_XWC);
        for (int i = 0; i < num_XWC; i++)
        {
            printf("%s = %d = %d\n", X_win_con[i].condition, X_win_con[i].move, X_win_con[i].value);
            //board_print(X_win_con[i].condition);
        }

        printf("\n\n\n");

        printf("num_XDC = %d\n\n", num_XDC);
        for (int i = 0; i < num_XDC; i++)
        {
            printf("%s = %d = %d\n", X_draw_con[i].condition, X_draw_con[i].move, X_draw_con[i].value);
            //board_print(X_draw_con[i].condition);
        }

        printf("\n\n\n");
    }
}

void data_read_from_file()
{
    int flag = 1;

    // O win Condition read
    FILE *fp = fopen("O_win_con.bin", "r");

    if (fp != NULL)
    {
        if (fread(&num_OWC, sizeof(int), 1, fp) != 1)
        {
            puts("Error! Couldn't read num_OWC");
            _getch();
            flag = 0;
            exit(1);
        }
        if (fread(O_win_con, sizeof(Conditional_data), num_OWC, fp) != num_OWC)
        {
            puts("Error! Couldn't read O_win_con file.");
            _getch();
            flag = 0;
            exit(1);
        }

        fclose(fp);
    }
    else
    {
        puts("Error! Couldn't open O_win_con file for reading");
        _getch();
        flag = 0;
        //exit(1);
    }

    // O draw Condition read
    fp = fopen("O_draw_con.bin", "r");

    if (fp != NULL)
    {
        if (fread(&num_ODC, sizeof(int), 1, fp) != 1)
        {
            puts("Error! Couldn't read num_ODC");
            _getch();
            flag = 0;
            exit(1);
        }
        if (fread(O_draw_con, sizeof(Conditional_data), num_ODC, fp) != num_ODC)
        {
            puts("Error! Couldn't read O_draw_con file.");
            _getch();
            flag = 0;
            exit(1);
        }

        fclose(fp);
    }
    else
    {
        puts("Error! Couldn't open O_draw_con file for reading");
        _getch();
        flag = 0;
        //exit(1);
    }

    // X win Condition read
    fp = fopen("X_win_con.bin", "r");

    if (fp != NULL)
    {
        if (fread(&num_XWC, sizeof(int), 1, fp) != 1)
        {
            puts("Error! Couldn't read num_XWC");
            _getch();
            flag = 0;
            exit(1);
        }
        if (fread(X_win_con, sizeof(Conditional_data), num_XWC, fp) != num_XWC)
        {
            puts("Error! Couldn't read X_win_con file.");
            _getch();
            flag = 0;
            exit(1);
        }

        fclose(fp);
    }
    else
    {
        puts("Error! Couldn't open X_win_con file for reading");
        _getch();
        flag = 0;
        //exit(1);
    }

    // X draw Condition read
    fp = fopen("X_draw_con.bin", "r");

    if (fp != NULL)
    {
        if (fread(&num_XDC, sizeof(int), 1, fp) != 1)
        {
            puts("Error! Couldn't read num_XDC");
            _getch();
            flag = 0;
            exit(1);
        }
        if (fread(X_draw_con, sizeof(Conditional_data), num_XDC, fp) != num_XDC)
        {
            puts("Error! Couldn't read X_draw_con file.");
            _getch();
            flag = 0;
            exit(1);
        }

        fclose(fp);
    }
    else
    {
        puts("Error! Couldn't open X_draw_con file for reading");
        _getch();
        flag = 0;
        //exit(1);
    }

    if (flag)
        puts("Data read successfully");

    return;
}

void reset_board()
{
    for (int i = 0; i <= 9; i++)
    {
        BP[i] = ' ';
    }
    BP[10] = '\0';

    index_Omove = 0;
    index_Xmove = 0;
}

void display_board()
{
    printf("\n\n");

    printf("\t  %c | %c | %c\n", BP[1], BP[2], BP[3]);
    printf("\t____|___|____\n");
    printf("\t  %c | %c | %c\n", BP[4], BP[5], BP[6]);
    printf("\t____|___|____\n");
    printf("\t  %c | %c | %c\n", BP[7], BP[8], BP[9]);
    printf("\t    |   |     \n\n");

    printf("\n\n");
}

void display_clean()
{
    system("cls");
    display_database_info();
    display_board();
}

void user_vs_computer()
{
    reset_board();
    int turn_count = 0;
    char game_result;
    int game_status, WIN = 1, DRAW = 0;

    while (1)
    {
        display_clean();

        O_Turn();
        turn_count++;

        display_clean();

        if (winning_check())
        {
            if (isUserFirstMove)
            {
                printf("\n\nYou win\n\n");
            }
            else
            {
                printf("\n\nYou lose\n\n");
            }

            printf("Enter to continue...\n");
            _getch();
            game_result = 'O';
            game_status = WIN;
            break;
        }

        if (turn_count == 9) // When turn_count will be 9 then Game will be draw
        {
            printf("\n\nGame Draw\n\n");
            printf("Enter to continue...\n");
            _getch();
            game_status = DRAW;
            break;
        }

        X_Turn();
        turn_count++;

        display_clean();

        if (winning_check())
        {
            if (isUserFirstMove)
            {
                printf("\n\nYou lose\n\n");
            }
            else
            {
                printf("\n\nYou win\n\n");
            }

            printf("Enter to continue...\n");
            _getch();
            game_result = 'X';
            game_status = WIN;
            break;
        }
    }

    data_merge(game_result, game_status);
    data_save_to_file();

    // for (int i = 0; i < index_Omove; i++)
    // {
    //     printf("%s = move = %d value = %d\n", temp_Omove[i].condition, temp_Omove[i].move, temp_Omove[i].value);
    // }
    // printf("\n\n\n");
    // for (int i = 0; i < index_Xmove; i++)
    // {
    //     printf("%s = move = %d value = %d\n", temp_Xmove[i].condition, temp_Xmove[i].move, temp_Xmove[i].value);
    // }
}

void computer_vs_user()
{
    reset_board();
    int turn_count = 0;
    char game_result;
    int game_status, WIN = 1, DRAW = 0;

    while (1)
    {
        display_clean();

        O_Turn();
        turn_count++;

        display_clean();

        if (winning_check())
        {
            if (isUserFirstMove)
            {
                printf("\n\nYou win\n\n");
            }
            else
            {
                printf("\n\nYou lose\n\n");
            }
            printf("Enter to continue...\n");
            _getch();
            game_result = 'O';
            game_status = WIN;
            break;
        }

        if (turn_count == 9) // When turn_count will be 9 then Game will be draw
        {
            printf("\n\nGame Draw\n\n");
            printf("Enter to continue...\n");
            _getch();
            game_status = DRAW;
            break;
        }

        X_Turn();
        turn_count++;

        display_clean();

        if (winning_check())
        {
            if (isUserFirstMove)
            {
                printf("\n\nYou lose\n\n");
            }
            else
            {
                printf("\n\nYou win\n\n");
            }
            printf("Enter to continue...\n");
            _getch();
            game_result = 'X';
            game_status = WIN;
            break;
        }
    }

    data_merge(game_result, game_status);
    data_save_to_file();

    // for (int i = 0; i < index_Omove; i++)
    // {
    //     printf("%s = move = %d value = %d\n", temp_Omove[i].condition, temp_Omove[i].move, temp_Omove[i].value);
    // }
    // printf("\n\n\n");
    // for (int i = 0; i < index_Xmove; i++)
    // {
    //     printf("%s = move = %d value = %d\n", temp_Xmove[i].condition, temp_Xmove[i].move, temp_Xmove[i].value);
    // }
}

void play()
{
    int play_times = 1;
    while (play_times--)
    {
        user_vs_computer();
        isUserFirstMove = !isUserFirstMove;
        computer_vs_user();
        isUserFirstMove = !isUserFirstMove;

        //break;
    }
}

void data_merge(char game_result, int game_status) // data_merge will be optimized
{
    int flag;

    if (game_status == 1)
    {
        if (game_result == 'O')
        {
            for (int i = 0; i < index_Omove; i++)
            {
                flag = 1;

                for (int j = 0; j < num_OWC; j++)
                {
                    if (strcmp(O_win_con[j].condition, temp_Omove[i].condition) == 0)
                    {
                        if (O_win_con[j].move == temp_Omove[i].move)
                        {
                            O_win_con[j].value++;
                            flag = 0;
                        }
                    }
                }

                if (flag)
                {
                    if (num_OWC + 1 < MAX_SIZE)
                    {
                        O_win_con[num_OWC++] = temp_Omove[i];
                    }
                    else
                    {
                        printf("\nO_win_con out of space = %d\n", num_OWC);
                    }
                }
            }
        }
        else if (game_result == 'X')
        {
            for (int i = 0; i < index_Xmove; i++)
            {
                flag = 1;

                for (int j = 0; j < num_XWC; j++)
                {
                    if (strcmp(X_win_con[j].condition, temp_Xmove[i].condition) == 0)
                    {
                        if (X_win_con[j].move == temp_Xmove[i].move)
                        {
                            X_win_con[j].value++;
                            flag = 0;
                        }
                    }
                }

                if (flag)
                {
                    if (num_XWC + 1 < MAX_SIZE)
                    {
                        X_win_con[num_XWC++] = temp_Xmove[i];
                    }
                    else
                    {
                        printf("\nX_win_con out of space = %d\n", num_XWC);
                    }
                }
            }
        }
    }
    else
    {
        // O draw condition merge
        for (int i = 0; i < index_Omove; i++)
        {
            flag = 1;

            for (int j = 0; j < num_ODC; j++)
            {
                if (strcmp(O_draw_con[j].condition, temp_Omove[i].condition) == 0)
                {
                    if (O_draw_con[j].move == temp_Omove[i].move)
                    {
                        O_draw_con[j].value++;
                        flag = 0;
                    }
                }
            }

            if (flag)
            {
                if (num_ODC + 1 < MAX_SIZE)
                {
                    O_draw_con[num_ODC++] = temp_Omove[i];
                }
                else
                {
                    printf("\nO_draw_con out of space = %d\n", num_ODC);
                }
            }
        }

        // X draw condition merge
        for (int i = 0; i < index_Xmove; i++)
        {
            flag = 1;

            for (int j = 0; j < num_XDC; j++)
            {
                if (strcmp(X_draw_con[j].condition, temp_Xmove[i].condition) == 0)
                {
                    if (X_draw_con[j].move == temp_Xmove[i].move)
                    {
                        X_draw_con[j].value++;
                        flag = 0;
                    }
                }
            }

            if (flag)
            {
                if (num_XDC + 1 < MAX_SIZE)
                {
                    X_draw_con[num_XDC++] = temp_Xmove[i];
                }
                else
                {
                    printf("\nX_draw_con out of space = %d\n", num_XDC);
                }
            }
        }
    }
}

void data_save_to_file()
{
    int flag = 1;

    // O win Condition write
    FILE *fp = fopen("O_win_con.bin", "w");

    if (fp != NULL)
    {
        if (fwrite(&num_OWC, sizeof(int), 1, fp) != 1)
        {
            puts("Error! Couldn't write num_OWC");
            _getch();
            flag = 0;
            exit(1);
        }
        if (fwrite(O_win_con, sizeof(Conditional_data), num_OWC, fp) != num_OWC)
        {
            puts("Error! Couldn't write O_win_con file.");
            _getch();
            flag = 0;
            exit(1);
        }

        fclose(fp);
    }
    else
    {
        puts("Error! Couldn't open O_win_con file for writing");
        _getch();
        flag = 0;
        exit(1);
    }

    // O draw Condition write
    fp = fopen("O_draw_con.bin", "w");

    if (fp != NULL)
    {
        if (fwrite(&num_ODC, sizeof(int), 1, fp) != 1)
        {
            puts("Error! Couldn't write num_ODC");
            _getch();
            flag = 0;
            exit(1);
        }
        if (fwrite(O_draw_con, sizeof(Conditional_data), num_ODC, fp) != num_ODC)
        {
            puts("Error! Couldn't write O_draw_con file.");
            _getch();
            flag = 0;
            exit(1);
        }

        fclose(fp);
    }
    else
    {
        puts("Error! Couldn't open O_draw_con file for writing");
        _getch();
        flag = 0;
        exit(1);
    }

    // X win Condition write
    fp = fopen("X_win_con.bin", "w");

    if (fp != NULL)
    {
        if (fwrite(&num_XWC, sizeof(int), 1, fp) != 1)
        {
            puts("Error! Couldn't write num_XWC");
            _getch();
            flag = 0;
            exit(1);
        }
        if (fwrite(X_win_con, sizeof(Conditional_data), num_XWC, fp) != num_XWC)
        {
            puts("Error! Couldn't write X_win_con file.");
            _getch();
            flag = 0;
            exit(1);
        }

        fclose(fp);
    }
    else
    {
        puts("Error! Couldn't open X_win_con file for writing");
        _getch();
        flag = 0;
        exit(1);
    }

    // X draw Condition write
    fp = fopen("X_draw_con.bin", "w");

    if (fp != NULL)
    {
        if (fwrite(&num_XDC, sizeof(int), 1, fp) != 1)
        {
            puts("Error! Couldn't write num_XDC");
            _getch();
            flag = 0;
            exit(1);
        }
        if (fwrite(X_draw_con, sizeof(Conditional_data), num_XDC, fp) != num_XDC)
        {
            puts("Error! Couldn't write X_draw_con file.");
            _getch();
            flag = 0;
            exit(1);
        }

        fclose(fp);
    }
    else
    {
        puts("Error! Couldn't open X_draw_con file for writing");
        _getch();
        flag = 0;
        exit(1);
    }

    if (flag)
        puts("Data write successfully");

    return;
}

void get_board_condition(char *board_condition)
{
    FILE *fp = fopen("temp_data.txt", "w");

    if (fp != NULL)
    {
        fprintf(fp, "if(BP[1] == '%c' && BP[2] == '%c' && BP[3] == '%c' && BP[4] == '%c' && BP[5] == '%c' && BP[6] == '%c' && BP[7] == '%c' && BP[8] == '%c' && BP[9] == '%c')", BP[1], BP[2], BP[3], BP[4], BP[5], BP[6], BP[7], BP[8], BP[9]);
        fclose(fp);
    }
    else
    {
        puts("Error! temp_data Couldn't open for writing");
        exit(1);
    }

    fp = fopen("temp_data.txt", "r");

    if (fp != NULL)
    {
        fgets(board_condition, 300, fp);
        fclose(fp);
    }
    else
    {
        puts("Error! temp_data Couldn't open for reading");
        exit(1);
    }
}

int move_from_DB(char player)
{
    char board_condition[300];
    int max_value = 0;
    int move, flag = 0;

    get_board_condition(board_condition);

    if (player == 'O')
    {
        //Finding in O win conditon database
        for (int i = 0; i < num_OWC; i++)
        {
            if (strcmp(O_win_con[i].condition, board_condition) == 0)
            {
                flag = 1;
                if (O_win_con[i].value > max_value)
                {
                    max_value = O_win_con[i].value;
                    move = O_win_con[i].move;
                }
            }
        }
        if (flag)
        {
            printf("\nMove from O_win_con database\n");
            return move;
        }

        //Finding in O draw conditon database
        for (int i = 0; i < num_ODC; i++)
        {
            if (strcmp(O_draw_con[i].condition, board_condition) == 0)
            {
                flag = 1;
                if (O_draw_con[i].value > max_value)
                {
                    max_value = O_draw_con[i].value;
                    move = O_draw_con[i].move;
                }
            }
        }
        if (flag)
        {
            printf("\nMove from O_draw_con database\n");
            return move;
        }

        printf("\nMove from Randomly...\n");
        // Move from randomly
        while (1)
        {
            move = (rand() % 9) + 1;

            if (BP[move] != ' ')
                continue;

            return move;
        }
    }
    else if (player == 'X')
    {
        // Finding in X win conditon database
        for (int i = 0; i < num_XWC; i++)
        {
            if (strcmp(X_win_con[i].condition, board_condition) == 0)
            {
                flag = 1;
                if (X_win_con[i].value > max_value)
                {
                    max_value = X_win_con[i].value;
                    move = X_win_con[i].move;
                }
            }
        }
        if (flag)
        {
            printf("\nMove from X_win_con database\n");
            return move;
        }

        //Finding in X draw conditon database
        for (int i = 0; i < num_XDC; i++)
        {
            if (strcmp(X_draw_con[i].condition, board_condition) == 0)
            {
                flag = 1;
                if (X_draw_con[i].value > max_value)
                {
                    max_value = X_draw_con[i].value;
                    move = X_draw_con[i].move;
                }
            }
        }
        if (flag)
        {
            printf("\nMove from X_draw_con database\n");
            return move;
        }

        printf("\nMove from Randomly...\n");
        //Move from randomly
        while (1)
        {
            move = (rand() % 9) + 1;

            if (BP[move] != ' ')
                continue;

            return move;
        }
    }
}

int move_from_user()
{
    char move;

    while (1)
    {
        move = _getch() - '0';

        if (1 <= move && 9 >= move)
        {
            if (BP[move] != ' ')
                continue;

            return move;
        }
    }
}

void temporary_data_processing(Conditional_data *temp_data, int *index, int move)
{
    FILE *fp = fopen("temp_data.txt", "w");

    if (fp != NULL)
    {
        fprintf(fp, "if(BP[1] == '%c' && BP[2] == '%c' && BP[3] == '%c' && BP[4] == '%c' && BP[5] == '%c' && BP[6] == '%c' && BP[7] == '%c' && BP[8] == '%c' && BP[9] == '%c')", BP[1], BP[2], BP[3], BP[4], BP[5], BP[6], BP[7], BP[8], BP[9]);
        fclose(fp);
    }
    else
    {
        puts("Error! temp_data Couldn't open for writing");
        exit(1);
    }

    fp = fopen("temp_data.txt", "r");

    if (fp != NULL)
    {
        fgets(temp_data[*index].condition, 300, fp);
        temp_data[*index].move = move;
        temp_data[*index].value = 1;

        // printf("%s\n", temp_data[*index].condition);
        // printf("Move = %d\n", temp_data[*index].move);
        // printf("Value = %d\n", temp_data[*index].value);
        // _getch();

        (*index)++;

        fclose(fp);
    }
    else
    {
        puts("Error! temp_data Couldn't open for reading");
        exit(1);
    }
}

void O_Turn()
{
    int move;

    if (isUserFirstMove)
    {
        printf("Your Turn: ");
        move = move_from_user();
        // move = move_from_DB('O');
        printf("%d\n", move);
    }
    else
    {
        move = move_from_DB('O');
        printf("Computer Turn: ");
        printf("%d\n", move);
        _getch();
    }

    // Temporary data processing for Omove
    temporary_data_processing(temp_Omove, &index_Omove, move);

    BP[move] = 'O';
}

void X_Turn()
{
    int move;

    if (isUserFirstMove)
    {
        move = move_from_DB('X');
        printf("Computer Turn: ");
        printf("%d\n", move);
        _getch();
    }
    else
    {
        printf("Your Turn: ");
        move = move_from_user();
        // move = move_from_DB('X');
        printf("%d\n", move);
    }

    // Temporary data processing for Xmove
    temporary_data_processing(temp_Xmove, &index_Xmove, move);

    BP[move] = 'X';
}

int winning_check()
{
    if (BP[1] == BP[2] && BP[2] == BP[3] && BP[1] != ' ')
    {
        return 1;
    }
    else if (BP[4] == BP[5] && BP[5] == BP[6] && BP[4] != ' ')
    {
        return 1;
    }
    else if (BP[7] == BP[8] && BP[8] == BP[9] && BP[7] != ' ')
    {
        return 1;
    }

    else if (BP[1] == BP[4] && BP[4] == BP[7] && BP[1] != ' ')
    {
        return 1;
    }
    else if (BP[2] == BP[5] && BP[5] == BP[8] && BP[2] != ' ')
    {
        return 1;
    }
    else if (BP[3] == BP[6] && BP[6] == BP[9] && BP[3] != ' ')
    {
        return 1;
    }

    else if (BP[1] == BP[5] && BP[5] == BP[9] && BP[1] != ' ')
    {
        return 1;
    }
    else if (BP[7] == BP[5] && BP[5] == BP[3] && BP[7] != ' ')
    {
        return 1;
    }

    return 0;
}

void menu()
{
    printf("\n\n\n");

    printf("O_win_Con     = 1\n");
    printf("O_draw_con    = 2\n");
    printf("X_win_con     = 3\n");
    printf("X_draw_con    = 4\n");
    printf("All Condition = 5\n");
    printf("Play          = p\n");
    printf("Exit          = e\n");

    printf("\n\n\n");
}
