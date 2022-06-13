#include <iostream>
#include "ANNN.h"
#include "TicTacToe.h"

using namespace std;

int main()
{

    Tictactoe ttt;
    ANN AI;
    //Training the data through file
    AI.training();

    while(ttt.gameover()){
        ttt.player_turn();
        // ttt.AI_move();
        ttt.check();
    }
    return 0;

}