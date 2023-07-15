
#include<iostream>
using namespace std;

// prototypes
typedef struct Player;
void initialise_board(char board[3][3]);
void print_board(char board[][3]);
bool is_tie(char board[3][3]);
char player_win(char board[3][3]);

//player struct
typedef struct Player
{
    string name;
    char symbol;
    int win = 0, lose = 0, tie = 0; // this is used for showing stat
} player;

int main()
{
    int choice, row, col;
    char board[3][3];
    char symbol;
    string name;
    
    //player
    player player1, player2;
    // A welcome message
    cout << "Welcome to Tick-Tack-Toe \n";
    
    // label
player1_symbol:
    
    // asking for the players names and symbol
    cout << "\nPlayer 1 name: ";
    getline(cin, name);
    cout<< "Player 1 symbol: ";
    cin >> symbol;
    //fflush(stdin); // flush stdin to remove garbage character

    
    // is user enters *, then ask again
    if( symbol == '*')
    {
        cout << "Not this symbol, please try again" << endl;
        cin >> symbol;
       goto player1_symbol;
    }
    // this helps the game keep track on player2 name and symbol they chose
    player1.name = name;
    player1.symbol = symbol;
    
    // label
player2_symbol:
    
    // Asking for player 2 for his/her information
    cout << "\nPlayer 2 name: ";
    cin >> name;
    cout<< "Player 2 symbol: ";
    cin >> symbol;
    //fflush(stdin); // flush stdin to remove garbage character

    if( symbol == '*')
    {
        cout << "Not this symbol, please try again" << endl;
        cin >> symbol;
        goto player2_symbol;
    }

    // if player2 accidently chooses the same symbol as player 1, this will have them re-enter
    if(symbol == player1.symbol)
    {
        cout << "This symbol is taken please try again \n ";
        //cin >> symbol;
        goto player2_symbol;
    }
    
    // this helps the game keep track on player2 name and symbol they chose
    player2.name = name;
    player2.symbol = symbol;
    
    // label
replay:
    
    // fill board with *
    initialise_board(board);

    // print board
    print_board(board);
    
    // start from player 1
    player player_turn = player1;
    
    // the start of the game
    while(true)
    {
        // label
    choose_location:
        
        // ask for the user name and the locations
        cout << player_turn.name << " choose rows from 0-2 only: ";
        cin >> row;
        cout << player_turn.name << " choose column  from 0-2 only: ";
        cin >> col;
        cin.ignore();
        
        // if the user inputs a location that is occupied already
        if( board[row][col] != '*')
        {
            cout << "This location is already occupied \n";
            goto choose_location;
        }
        else
            board[row][col] = player_turn.symbol;
        
        // print board
        print_board(board);
        cout << endl;
        
        // check for win,
        char win_symbol = player_win(board);
        
        // if a player has won
        if( win_symbol != '*')
        {
            if( win_symbol == player1.symbol)
            {
                cout << player1.name << " has won\n";

                // update win and loss
                player1.win = player1.win + 1;
                player2.lose = player2.lose + 1;
                break;

            }
            else
            {
                cout << player2.name << " has won\n";

                // update win and loss
                player2.win = player2.win + 1;
                player1.lose = player1.lose + 1;
                break;

            }
        }
        
        // if no one won, check if game is tie
        else if( is_tie(board))
        {
            cout << "It's a tie\n";

            //update ties
            player1.tie = player1.tie + 1;
            player2.tie = player2.tie + 1;
            break;
        }
        // else change player's turn
        else
        {
            if( player_turn.name == player1.name)
                player_turn = player2;

            else
                player_turn = player1;
        }
    }

    // after they finish the game they are given to options to show stats or replay the game or end the program
    cout << "1. Show Stats\n";
    cout << "2. Replay\n";
    cout << "3. Quit:\n ";
    cin >> choice;

    //if the user chooses to show stats, win loss tie
    if(choice == 1)
    {
        cout << endl << player1.name << "\t" << player1.symbol << "\twins: " << player1.win;
        cout << "\tlosses: " << player1.lose << "\tties: " << player1.tie << endl;

        cout << endl << player2.name << "\t" << player2.symbol << "\twins: " << player2.win;
        cout << "\tlosses: " << player2.lose << "\tties: " << player2.tie << endl;
    }

    // if the user chooses option 2 then clear screen and restart game
    else if(choice == 2)
    {
        system("CLS");
        goto replay;
    }
    // if they choose 3 they will then exit the game
    else
        exit(0);

}

// to fill board with *
void initialise_board(char board[3][3])
{
    for(int row=0; row< 3; row++)
    {
        for(int col=0; col< 3; col++)
        {
            board[row][col]= '*';
        }
    }
}

//Display board
void print_board(char board[][3])
{
    // this is to label the top row from 0-2
    cout << "   1   2   3 ";
    cout << endl;
    
      for(int row=0; row< 3; row++)
      {
          // this is for the side of the chart
          cout << row << "  ";
          for(int col=0; col< 3; col++)
          {
             // cout.width(3);
              cout << board[row][col] << "\t";
          }
          cout << endl;
      }
    
}


// to check if game is tie
bool is_tie(char board[3][3])
{
    //its a tie if all positions are filled

    for(int row=0; row< 3; row++)
        for(int col=0; col< 3; col++)
            if(board[row][col] == '*')
                return false;

    return true;
}


// to check if player has won, this returns char of winning player, if no one wins then it return *
char player_win(char board[3][3])
{
    // check rows if all three are same and not empty (*)// 0, 1, 2
    for (int i=0; i<3; i++)
        if( board[i][0] == board[i][1] && board[i][1] == board[i][2] &&  board[i][0] != '*') // if row 1 equal row 2 and row equal 2 and row 3
            return board[i][0];

    // check columns if all three are same and not empty (*)
    for( int i=0; i< 3; i++)
        if( board[0][i] == board[1][i] && board[1][i] == board[2][i] &&  board[0][i] != '*')
            return board[0][i];

    // check left diagonal
    if( board[0][0] == board[1][1] && board[1][1] == board[2][2] &&  board[0][0] != '*')
            return board[0][0];

    // check left diagonal
    if( board[0][2] == board[1][1] && board[1][1] == board[2][0] &&  board[0][2] != '*')
            return board[0][2];
    
    //else return *, no one wins
    return '*';
}

