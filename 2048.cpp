/*
 * 2048.cpp
 * COMP11 Project 1, Spring 2019, Tufts University
 * Modified by: Auguste Brown
 * Date: 3/13/19
 */

#include <iostream>
#include <iostream>
#include <time.h>
#include <sstream>
using namespace std;

// CONSTANTS (IF ANY) GO HERE
const int BOARD_HEIGHT = 4;
const int BOARD_WIDTH = 4;
const string UP = "w";
const string RIGHT = "d";
const string DOWN = "s";
const string LEFT = "a";
const string QUIT = "q";
const string EMPTY = "-";


// FUNCTION PROTOTYPES GO HERE
int string2int(string s);
string int2string(int num);
void print_padded_string(string s);
void play();
bool game_is_over(string board[][BOARD_HEIGHT]);
void print_board(string board[][BOARD_HEIGHT]);
string get_input();
int move(string input, string board[][BOARD_HEIGHT]);
void slide_right(string board[][BOARD_HEIGHT]);
int add_right(string board[][BOARD_HEIGHT]);
void slide_left(string board[][BOARD_HEIGHT]);
int add_left(string board[][BOARD_HEIGHT]);
void slide_up(string board[][BOARD_HEIGHT]);
int add_up(string board[][BOARD_HEIGHT]);
void slide_down(string board[][BOARD_HEIGHT]);
int add_down(string board[][BOARD_HEIGHT]);
bool empty_spot(string board[][BOARD_HEIGHT]);
bool is_empty(string spot);
void two_or_four(string board[][BOARD_HEIGHT]);
void add_value(string value, string board[][BOARD_HEIGHT]);

int main() {
    play();
    return 0;
}

//void play
//Purpose: initializes the board and contains the main gameplay loop
//Paramaters: none
//Returns: nothing
void play() {
    //initialize board
    string board[BOARD_HEIGHT][BOARD_WIDTH];
    for (int row = 0; row < BOARD_HEIGHT; row++){
        for (int col = 0; col < BOARD_WIDTH; col++){
            board[row][col] = EMPTY; //add a dash to each spot in the board
        }
    }

    string user_input = ""; //stores a valid character the user entered
    int score = 0; //stores the current score
    bool is_over = false;
    add_value("2", board); //add a 2 to a random spot in the board
    add_value("2", board); //add a 2 to a random spot in the board

    cout << "Starting game!" << endl;

    do{
        is_over = game_is_over(board);
        cout << "Current score: " << score << endl;
        print_board(board); //display the board to the user
        user_input = get_input(); //gets a valid character from the user
        score += move(user_input, board);
        two_or_four(board); //add a random 2 or 4 to the board after each move
    }while(user_input != "q" and !is_over);

    cout << "Game Over! Your score is " << score << endl;
}

//bool game_is_over
//Purpose: checks the board[] array to see if the game is over
//Paramaters: board[]
//Returns: boolean. true = game is over. false = game is continuing
bool game_is_over(string board[][BOARD_WIDTH]){
    bool no_adjacent = true; //true if no two adjacent values are equal

    for (int row = 0; row < BOARD_HEIGHT; row++){    
        for (int col = 0; col < BOARD_WIDTH; col++){
                if (board[row][col] == board[row][col + 1] 
                    or board[row][col] == board[row + 1][col])
                    no_adjacent = false; //if two adjacent values are equal
        }
    }

    if (!empty_spot(board) and no_adjacent){ //game ending conditions
        return true;
    }
    return false; //otherwise the game is still going
}

//void print_board
//Purpose: prints the board to the console
//Paramaters: board[]
//Returns: nothing
void print_board(string board[][BOARD_WIDTH]){
    for (int row = 0; row < BOARD_HEIGHT; row++){    
        for (int col = 0; col < BOARD_WIDTH; col++)
            print_padded_string(board[row][col]);
        cout << endl; //print a new line after each row
    }
}

//int get_input
//Purpose: gets input from the user. If it is valid, return it. Otherwise,
//         print a message and get another value until they enter a valid value
//Paramaters: none
//Returns: the user input (string)
string get_input(){
    string input = "";

    cin >> input;

    //loop checks to make sure the user is entering a valid input
    //loop is only exited when a valid input is entered
    while (input != UP and input != DOWN and input != LEFT and 
           input != RIGHT and input != QUIT){
        cout << "Command not recognized. Please try again.\n";
        cin >> input;
    }

    return input;
}

//int move
//Purpose: checks chich direction the user wants to move and calls helper
//         functions to execute that move
//Paramaters: string input, board[]
//Returns: the change to the user's score
int move(string input, string board[][BOARD_WIDTH]){
    int score = 0;

    if (input == RIGHT){
        slide_right(board);
        score = add_right(board);
        slide_right(board);
    }
    else if (input == LEFT){
        slide_left(board);
        score = add_left(board);
        slide_left(board);
    }
    else if (input == UP){
        slide_up(board);
        score = add_up(board);
        slide_up(board);
    }
    else if (input == DOWN){
        slide_down(board);
        score = add_down(board);
        slide_down(board);
    }

    return score;
}

//void slide_right
//Purpose: helper function which slides all values as far right as possible
//Paramaters: board[]
//Returns: nothing
void slide_right(string board[][BOARD_WIDTH]){
    for (int row = 0; row < BOARD_HEIGHT; row++){    
        for (int col = 0; col < BOARD_WIDTH - 1; col++){
            if (board[row][col + 1] == EMPTY and board[row][col] != EMPTY){
                //set value to the right equal to current value and
                //set current value to empty
                board[row][col + 1] = board[row][col];
                board[row][col] = EMPTY;
                col = -1; //if a value is moved, this might create room to
                          //move values behind it, so the loop is restarted
            }
        }
    }
}

//void add_right
//Purpose: helper function. Adds all possible values in the right direction
//Paramaters: board[]
//Returns: nothing
int add_right(string board[][BOARD_WIDTH]){
    int score = 0;

    for (int row = 0; row < BOARD_HEIGHT; row++){
        for (int col = BOARD_WIDTH - 1; col > 0; col--){
            if(board[row][col]==board[row][col - 1] and board[row][col]!=EMPTY){
                board[row][col] = int2string(string2int(board[row][col]) * 2);
                score += string2int(board[row][col]);
                board[row][col - 1] = EMPTY;
            }
        }
    }

    return score;
}

//void slide_left
//Purpose: helper function which slides all values as far left as possible
//Paramaters: board[]
//Returns: nothing
void slide_left(string board[][BOARD_WIDTH]){
    for (int row = 0; row < BOARD_HEIGHT; row++){
        for (int col = BOARD_WIDTH - 1; col > 0; col--){
            if (board[row][col - 1] == EMPTY and board[row][col] != EMPTY){
                //set value to the left equal to current value and
                //set current value to empty
                board[row][col - 1] = board[row][col];
                board[row][col] = EMPTY;
                col = BOARD_WIDTH;
            }
        }
    }
}

//void add_left
//Purpose: helper function. Adds all possible values in the left direction
//Paramaters: board[]
//Returns: nothing
int add_left(string board[][BOARD_WIDTH]){
    int score = 0;

    for (int row = 0; row < BOARD_HEIGHT; row++){
        for (int col = 0; col < BOARD_WIDTH - 1; col++){
            if(board[row][col]==board[row][col + 1] and board[row][col]!=EMPTY){
                board[row][col] = int2string(string2int(board[row][col]) * 2);
                score += string2int(board[row][col]);
                board[row][col + 1] = EMPTY;
            }
        }
    }

    return score;
}

//void slide_left
//Purpose: helper function which slides all values as far left as possible
//Paramaters: board[]
//Returns: nothing
void slide_up(string board[][BOARD_WIDTH]){
    for (int col = 0; col < BOARD_WIDTH; col++){    
        for (int row = BOARD_HEIGHT - 1; row > 0; row--){
            if (board[row - 1][col] == EMPTY and board[row][col] != EMPTY){
                //set above value equal to current value and
                //set current value to empty
                board[row - 1][col] = board[row][col];
                board[row][col] = EMPTY;
                row = BOARD_HEIGHT;
            }
        }
    }
}

//void add_left
//Purpose: helper function. Adds all possible values in the left direction
//Paramaters: board[]
//Returns: nothing
int add_up(string board[][BOARD_WIDTH]){
    int score = 0;

    for (int col = 0; col < BOARD_WIDTH; col++){
        for (int row = 0; row < BOARD_HEIGHT - 1; row++){
            if(board[row][col] == board[row+1][col] and board[row][col]!=EMPTY){
                board[row][col] = int2string(string2int(board[row][col]) * 2);
                score += string2int(board[row][col]);
                board[row + 1][col] = EMPTY;
            }
        }
    }

    return score;
}

//void slide_left
//Purpose: helper function which slides all values as far left as possible
//Paramaters: board[]
//Returns: nothing
void slide_down(string board[][BOARD_WIDTH]){
    for (int col = 0; col < BOARD_WIDTH; col ++){    
        for (int row = 0; row < BOARD_HEIGHT; row++){
            if (board[row + 1][col] == EMPTY and board[row][col] != EMPTY){
                //set value below equal to current value and
                //set current value to empty
                board[row + 1][col] = board[row][col];
                board[row][col] = EMPTY;
                row = -1;
            }
        }
    }
}

//void add_left
//Purpose: helper function. Adds all possible values in the left direction
//Paramaters: board[]
//Returns: nothing
int add_down(string board[][BOARD_WIDTH]){
    int score = 0;

    for (int col = 0; col < BOARD_WIDTH; col++){
        for (int row = BOARD_HEIGHT - 1; row >= 0; row--){
            if(board[row-1][col] == board[row][col] and board[row][col]!=EMPTY){
                board[row][col] = int2string(string2int(board[row][col]) * 2);
                score += string2int(board[row][col]);
                board[row - 1][col] = EMPTY;
            }
        }
    }

    return score;
}

//bool empty_spott
//Purpose: checks the entire board to see if there is at least one empty spot
//Paramaters: board[]
//Returns: true if there is an empty spot. false if not
bool empty_spot(string board[][BOARD_WIDTH]){
    for (int row = 0; row < BOARD_HEIGHT; row++){    
        for (int col = 0; col < BOARD_WIDTH; col++){
            if (board[row][col] == EMPTY)
                return true;
        }
    }
    return false;
}

//void two_or_four
//Purpose: Adds either a 2 or a 4 to an empty spot on the board
//Paramaters: board[]
//Returns: nothing
void two_or_four(string board[][BOARD_WIDTH]){
    srand(time(NULL));

    if (rand() % 10 == 0) //10% likelihood of adding a 4
        add_value("4", board);
    else
        add_value("2", board); //90% likelihood of adding a 2

}

//void add_value
//Purpose: If there is an empty spot on the board, adds a given value to an
//         empty spot on the board
//Paramaters: board[]
//Returns: nothing
void add_value(string value, string board[][BOARD_WIDTH]){
    if (!empty_spot(board)) //check to seee if there are any spots where
                            //a new value can be added to the board
        return; //if there are no empty spots, leave function

    srand(time(NULL));
    int row;
    int col;

    do{
        //set row and column variables equal to a random value between 0 and 3
        row = rand() % 4;
        col = rand() % 4;
    }while(board[row][col] != EMPTY); //if the random spot is full,
                                      //get a new spot

    board[row][col] = value; //when an empty spot is found, put value in it
}

/* string2int
 * Convert a string to an int. Returns the int form of the given string.
 * Throw logic error if the string is not numerical. 
 */
int string2int(string s) {
    stringstream ss(s);
    int result;
    ss >> result;
    if (ss.fail())
        throw logic_error("ERROR: " + s + " is not a numerical value");
    return result;
}

/* Converts an int to string.
 * Returns the string form of the given int
 */
string int2string(int num) {
    string result;
    ostringstream oss;
    oss << num;
    result = oss.str();
    return result;
}
/* Print a string (persumably an int in the form of a string) with 
 * right paddings of up to 5 spaces
 */
void print_padded_string(string s) {
    printf("%-6s", s.c_str());
}

