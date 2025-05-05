// Author = William Marklynn

// Desc: Connect 4 game between human players: player 1 and player 2
//       marked with X and O symbols respectively. Either player wins
//       if their respective symbols occupy 4 consecutive spaces
//       either horizontally or vertically. If all 48 spaces are occupied
//       game ends in a draw.
//       Program asks winning player if they would like to play again.

// How?: int main contains boolean value running which is true while gameplay
//       is ongoing. Conventional connect 4 boards are 6 by 8.
//       To create a connect 4 board in the program,
//       a 2D array spaces of size 6 by 8 is declared and initialized.
//       a drawboardfunction is responsible for drawing the
//       connect 4 board in the output by placing each index value
//       of spaces in between '|' symbols representing borders between columns
//       while running is true, it will prompt player 1 to drop their marker
//       on their desired column. To achieve this, function player1move places
//       player 1's marker in the lowest empty row in that column.
//       Following this, boolean functions
//       check_winner_horizontal and check_winner_vertical
//       checks if there are 4 consecutive X markers in their respective
//       directions. If there are, the game ends and
//       a prompt if they user would like to play
//       is outputted. The same prompt will be
//       displayed if all 48 spaces are occupied (tie).
//       If there are not, player 2 will get their turn to drop their marker.
//       Player 2 has the same mechanic with player2move function and the
//       check_winner_horizontal, check_winner_vertical,
//       and check tie functions.
//       when gameplay is over, user is prompted
//       whether they would like to play again
//       if user inputs 'y' or 'Y', board is cleared
//       with the clear_board function
//       which goes through every out and inner
//       indexes of spaces and place an empty
//       ' ' value and the clear board is once
//       displayed in output to facilitate a new
//        round of gameplay. If user inputs 'n', running is set to false,
//        thus exiting the loop and ending the program.


#include <iostream>

void draw_board(char spaces[6][8], int rows, int columns);

void player1_move(char spaces[6][8], int rows, int columns, char player1);

void player2_move(char spaces[6][8], int rows, int columns, char player2);

bool check_winner_horizontal(char spaces[6][8], int rows, int columns,
    char player1, char player2);

bool check_winner_vertical(char spaces[6][8], int rows, int columns,
    char player1, char player2);

bool check_tie(char spaces[6][8], int rows, int columns);

void clear_board(char spaces[6][8], int rows, int columns);

int main() {
    bool running = true;
    char spaces[6][8];
    for (int i = 0; i < 6; i++){
        for(int j = 0; j < 8; j++){
            spaces[i][j] = ' ';
        }
    }
    char player1 = 'X';
    char player2 = 'O';

    draw_board(spaces, 6, 8);

    do {
        char play_again;
        // to be initialized later when player is asked if they would 
        //like to replay
        player1_move(spaces, 6, 8, player1);
        draw_board(spaces, 6, 8);
        if (check_winner_vertical(spaces, 6, 8, player1, player2) ||
            check_winner_horizontal(spaces, 6, 8, player1, player2) ||
            check_tie(spaces, 6, 8)){  // all three 
                //conditions end current round
            do {
                std::cout << "Would you like to play again? (y/n)" << ' ';
                std::cin >> play_again;
                std::cin.clear();
                std::cin.ignore(40, '\n');
            } while (play_again != 'n' && play_again != 'y');
            if (play_again == 'n') {
                std::cout<<"Thanks for playing!" << std::endl;
                running = false;
            } else if (play_again == 'y'){
                clear_board(spaces, 6, 8);
                draw_board(spaces, 6, 8);
                player1_move(spaces, 6, 8, player1);  
                // ensures Player X starts first in rematch
                draw_board(spaces, 6, 8);
            } 
        }

        if (running != false) {
            player2_move(spaces, 6, 8, player2);
            draw_board(spaces, 6, 8);
            if (check_winner_vertical(spaces, 6, 8, player1, player2) ||
                check_winner_horizontal(spaces, 6, 8, player1, player2) ||
                check_tie(spaces, 6, 8)){
                // std::cout << "Would you like to play again? (y/n)" << ' ';
                do {
                    std::cout << "Would you like to play again? (y/n)" << ' ';
                    std::cin >> play_again;
                    std::cin.clear();
                    std::cin.ignore(40, '\n');
                } while (play_again != 'n' && play_again != 'y');
                if (play_again == 'n') {
                    std::cout<<"Thanks for playing!" << std::endl;
                    running = false;
                } else if (play_again == 'y') {
                    clear_board(spaces, 6, 8);
                    draw_board(spaces, 6, 8);
                }
            }

        }
    } while (running); // while game is running, keep prompting user
                        // for inputs for markers/play again
    return 0;
}

// desc: draws board of 48 spaces, with each value of spaces between the 
//       borders marked by '|', as well as borders on the top and 
//       bottom of the board. column numbers added above the top border 
//       to improve user-friendliness
// pre: array passed must be 6 by 8; 6 inner arrays of 8 char values.
// post: connect 4 board, with values of spaces in between the borders are
//       displayed.
void draw_board(char spaces[6][8], int rows, int columns){
    std::cout << "  0   1   2   3   4   5   6   7  " 
    ""
                 "" << std::endl;
    
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            //if (j == columns-1) {
              //  std::cout << "| " << spaces[i][j] << " |";
            //}
            std::cout << "| " << spaces[i][j] << ' ';
        }
        std::cout << "|  " << std::endl;
    }    
    std::cout << std::endl;


}

// desc: places player X's marker on the lowest empty row
//       of the chosen column number on the board
// pre: column_number has to be an integer between and including 1 and 8
// post: player X's marker is placed on the lowest empty row
//       of the chosen column number on the board. Array
//       value at column_number's index is replaced with
//       player X's marker.
void player1_move(char spaces[6][8], int rows, int columns, char player1) {
    int column_number;
    int row_number = 0;
    do {
        std::cout << "X: Enter a column number (0-7): ";
        while (!(std::cin >> column_number)) {
            std::cout << "X: Enter a column number (0-7): ";
            std::cin.clear();
            std::cin.ignore(40, '\n');
        }
        while (spaces[row_number][column_number] == ' ' && row_number < 5)
        {
            row_number++;
        }
        while (spaces[row_number][column_number] != ' ' && row_number > 0)
        {
            row_number--;
        }
    } while (column_number < 0 || column_number > 7);

    spaces[row_number][column_number] = player1;
}

// desc: places player O's marker on the lowest empty row
//       of the chosen column number on the board
// pre: column_number has to be an integer between and including 1 and 8
// post: player O's marker is placed on the lowest empty row
//       of the chosen column number on the board. Array
//       value at column_number's index is replaced with
//       player O's marker.
void player2_move(char spaces[6][8], int rows, int columns, char player2) {
    int column_number;
    int row_number = 0;
    do {
        std::cout << "O: Enter a column number (0-7): ";
        while (!(std::cin >> column_number)) {
            std::cout << "O: Enter a column number (0-7): ";
            std::cin.clear();
            std::cin.ignore(40, '\n');
        }
        while (spaces[row_number][column_number] == ' ' && row_number < 5)
        {
            row_number++;
        }
        while (spaces[row_number][column_number] != ' ' && row_number > 0)
        {
            row_number--;
        }
    } while (column_number < 0 || column_number > 7);
    spaces[row_number][column_number] = player2;
}

// desc: checks if there is a winner; if there are 4 of the same
//       consecutive markers in the columns
// pre:  board must have a 3x3 grid with characters 'X', 'O', or empty spaces.
// post: function does not modify array, only analyzes current state
//       of game and returns true if there are 4 consecutive markers in
//       a particular row.
bool check_winner_horizontal(char spaces[6][8], int rows, int columns
    , char player1, char player2){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j <= columns/2; j++) {
            if (spaces[i][j] != ' ' && spaces[i][j] == spaces[i][j+1] &&
                spaces[i][j+1] == spaces[i][j+2]
                && spaces[i][j+2] == spaces[i][j+3]) {
                spaces[i][j] == player1? std::cout << "Player X Wins!" 
                << std::endl : std::cout << "Player O Wins!" << std::endl;
                return true;
            }
        }
    }
    return false;
}

// desc: checks if there is a winner; if there are 4 of the same
//       consecutive markers in the columns
// pre:  board must have a 3x3 grid with characters 'X', 'O', or empty spaces.
// post: function does not modify array, only analyzes current state
//       of game and returns true if there are 4 consecutive markers in
//       a particular column.
bool check_winner_vertical(char spaces[6][8], int rows, int columns, 
    char player1, char player2) {
    for(int i = 0; i < rows/2; i++){
        for(int j = 0; j < columns; j++) {
            if (spaces[i][j] != ' ' && spaces[i][j] == spaces[i+1][j] &&
                spaces[i+1][j] == spaces[i+2][j] &&
                spaces[i+2][j] == spaces[i+3][j]) {
                spaces[i][j] == player1? std::cout << "Player X Wins!" 
                << std::endl : std::cout << "Player O Wins!" << std::endl;

                return true;
            }
        }
    }

    return false;
}

// desc: checks if all indexes of 2D array spaces are empty spaces
//       checks if game ended in a draw
//       if any empty spaces, no draw yet
//       if no spaces, game ends in draw
// pre:  board must have a 3x3 grid with characters 'X', 'O', or empty spaces.
// post: function does not modify array, only analyzes current state
//       of game and returns true if there are no empty spaces in
//       array spaces.
bool check_tie(char spaces[6][8], int rows, int columns){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (spaces[i][j] == ' ') {
            return false;
          }
        }
    }
    std::cout << "The game has ended in a draw\n";
    return true;
}

// desc: clears 2D array spaces, thereby clearing the connect 4 board
//       to facilitate a replay of the game
// pre: 2D array spaces must have 6 rows and 8 columns
// post: All of 2D array spaces' index values are replaced with empty spaces
void clear_board(char spaces[6][8], int rows, int columns) {
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++) {
            spaces[i][j] = ' ';
        }
    }
}
