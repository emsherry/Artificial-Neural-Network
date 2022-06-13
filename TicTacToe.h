#include <iostream>
#include <vector>

using namespace std;

class Tictactoe
{
private:
    int row;
    int column;
public:
    friend class ANN;
  
    
    //Declaring a 2-D array for the tic-tac-toe board
    char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    int turn = 1;
    bool draw = false;

    // Show  Board
    void display_board()
    {

        cout << "PLAYER - 1 = 'X'\t PLAYER - 2 = 'O'\n\n";
        cout << "\t\t     |     |     \n";
        cout << "\t\t  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << " \n";
        cout << "\t\t_____|_____|_____\n";
        cout << "\t\t     |     |     \n";
        cout << "\t\t  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << " \n";
        cout << "\t\t_____|_____|_____\n";
        cout << "\t\t     |     |     \n";
        cout << "\t\t  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << " \n";
        cout << "\t\t     |     |     \n";
    }

    // Function to get the player input and update the board

    void player_turn()
    {
        int row,column;
        display_board();
        int choice_1;
        

        if (turn == 1)
        {
            cout << "\n\tPlayer - 1 : ";
        }
        else if (turn == 2)
        {
            cout << "\n\tPlayer - 2 : ";
        }

        // Taking input from user

        if(turn == 1)
        {
            cin >> choice_1;
        }

        // Switch case to mark the specified position

        switch (choice_1)
        {
        case 1:
            row = 0;
            column = 0;
            break;
        case 2:
            row = 0;
            column = 1;
            break;
        case 3:
            row = 0;
            column = 2;
            break;
        case 4:
            row = 1;
            column = 0;
            break;
        case 5:
            row = 1;
            column = 1;
            break;
        case 6:
            row = 1;
            column = 2;
            break;
        case 7:
            row = 2;
            column = 0;
            break;
        case 8:
            row = 2;
            column = 1;
            break;
        case 9:
            row = 2;
            column = 2;
            break;
        default:
            cout << "Invalid Move";
            // player_turn();
        }

        if (turn == 1 && board[row][column] != 'x' && board[row][column] != 'o')
        {
            // updating the position for 'X' symbol if
            // it is not already occupied
            board[row][column] = 'x';
            turn = 2;
        }
        else if (turn == 2)
        {
            AI_move();
            turn =1;   
        }
        else
        {
            // If position occupied already
            cout << "Box already filled!n Please choose another!!\n\n";
            player_turn();
        }
        // display_board();
    }

    bool gameover()
    {
        // Check Rows and Columns
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2] || board[0][i] == board[1][i] && board[0][i] == board[2][i])
                return false;
        }

        // Check Diagonals

        if (board[0][0] == board[1][1] && board[0][0] == board[2][2] || board[0][2] == board[1][1] && board[0][2] == board[2][0])
            return false;

        // Check for any free slot
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] != 'x' && board[i][j] != 'o')
                    return true;
            }
        }
        // Check Draw
        draw = true;
        return false;
    }
    void check()
    {
        while (gameover())
        {
            player_turn();
        }
        
        if (turn == 2 && draw == false)
        {
            cout << "\nCongratulations! You Won!!!";
        }
        else if (turn == 1 && draw == false)
        {
            cout << "\nComputer Won";
        }
        else
            cout << "\nGAME DRAW!!!";
        

    }

    //Function to calculate the index where computer will make its move
    void AI_move()
    {
        ANN ai;
        turn = 2;
        vector<double> probabilities;
        vector<int> empties = getEmptyPositionsIndexes();

        for(auto i: empties)
        {
            double **tempBoard = getBoard();
            tempBoard[i/3][i%3] = -1.0;

            ai.setInputNodes(tempBoard);
            ai.forward_feed();
            probabilities.push_back(ai.getoutput());
        }

        double minimumProb = 0;
        int index;
        for(int i = 0; i < probabilities.size(); i++)
            if(probabilities[i] > minimumProb)
            {
                minimumProb = probabilities[i];
                index = i;
            }
            //Computer makes it move t the desired index of the board
            if(board[row][column] != 'o'  && board[row][column] != 'x')
            {
                board[empties[index]/3][empties[index]%3] = 'o';
            }
            
            
    }

    double** getBoard()
    {
        double **returner;
        returner = new double*[3];
        for(int i = 0; i < 3; i++)
            returner[i] = new double[3];

        for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            switch (board[i][j])
            {
            case 'x':
                returner[i][j] = 1.0;
                break;
            case 'o':
                returner[i][j] = -1.0;
                break;
            default:
                returner[i][j] = 0;
                break;
            }

        return returner;
    }

//Function to get empty positions of the board 
    vector<int> getEmptyPositionsIndexes()
    {
        vector<int> returner;
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(this->board[i][j] != 'x' || this->board[i][j] != 'o')
                {
                    returner.push_back(i*3+j);
                }
            }
           
        }
        
        return returner;
    }

};