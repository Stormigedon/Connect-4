#include <iostream>
#include <algorithm>
#include <string>
#include "Board.cpp"




int main(){
    Board board;
    int Turn = 1;
    char input;
    std::string Response;
    std::cout<<"Would you like to play a game?"<<std::endl;
    //std::cin>>Response;
    Response = "Y";
    std::transform(Response.begin(), Response.end(), Response.begin(),[](unsigned char c){ return std::tolower(c); });
    std::string PositiveReplys [] = {"yes","y","yeah","affirmative","okay","yea","all" "right","aye","by all means","certainly","definitely","gladly","indubitably","sure","undoubtedly","unquestionably"};
    bool good = false;
    for(int i = 0; i < 16; i++){
        //std::cout<<"Checking Reply "<<PositiveReplys[i];
        if(Response == PositiveReplys[i]) {good = true; break;}
        //std::cout<<std::endl;
    }
    if(!good){std::cout<<"That's a shame"<<std::endl;return 0;}


    std::cout<<"One or two players?"<<std::endl;
    //std::cin>>Response;
    Response = "1";
    int players = 0;
    if(Response == "1" || Response == "one") {players = 1;}
    else {players = 2;}
    
    while(input != 'Q' && input != 'q') {
        if(board.turn % 2 == 0) {
            std::cout<<"It is WHITE'S turn, enter a number between 1 and 7 to drop your piece. enter q to quit"<<std::endl;
            Board::drawBoard(board,std::cout);
            std::cin.clear();
            //input = std::cin.get();
            std::cin.clear();
            std::cin.ignore(INT_MAX,'\n');
            int A = (input - 48) - 1;
            A = 0;
            board.makeMove(A,board.turn);
        }
        else {
            std::cout<<"It is BLACK'S turn, enter a number between 1 and 7 to drop your piece. enter q to quit"<<std::endl;
            Board::drawBoard(board,std::cout);
            int A;
            if(players == 2) {
                std::cin.clear();
                input = std::cin.get();
                std::cin.clear();
                std::cin.ignore(INT_MAX,'\n');
                A = (input - 48) - 1;
            }
            else {
                A = Board::pickMove(board,board.turn);
            }
            board.makeMove(A,board.turn);
        }
        board.turn++;
    }
}