#include <iostream>
#include "Board.cpp"

int main(){
    char board[6][7] = {' '};
    char Tops[7] = {-1,-1,-1,-1,-1,-1,-1};
    int Turn = 2;
    std::cout<<"It is WHITE'S turn, enter a number between 1 and 7 to drop your piece. enter q to quit"<<std::endl;
    Board::drawBoard(board,std::cout);
    std::cin.clear();
    char input = std::cin.get();
    std::cin.clear();
    std::cin.ignore(INT_MAX,'\n');
    while(input != 'Q' && input != 'q') {
        if(Turn % 2 == 0) {
            std::cout<<"It is BLACK'S turn, enter a number between 1 and 7 to drop your piece. enter q to quit"<<std::endl;
            if(((input - 48) > 0) && ((input - 48) <= 7)) {
                int Column = input-49;
                int Row = Tops[Column] + 1;
                if(Row < 6) {
                    board[Row][Column] = 'B';
                    Tops[Column] += 1;
                    Turn++;
                }
            }
        }
        else {
            std::cout<<"It is WHITE'S turn, enter a number between 1 and 7 to drop your piece. enter q to quit"<<std::endl;
            if(((input - 48) > 0) && ((input - 48) <= 7)) {
                int Column = input-49;
                int Row = Tops[Column] + 1;
                if(Row < 6) {
                    board[Row][Column] = 'W';
                    Tops[Column] += 1;
                    Turn++;
                }
            }
        }
        Board::drawBoard(board,std::cout);
        input = std::cin.get();
        std::cin.clear();
        std::cin.ignore(INT_MAX,'\n');
    }
}