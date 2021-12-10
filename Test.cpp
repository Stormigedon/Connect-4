#include <iostream>
#include <algorithm>
#include <string>
#include "Board.cpp"
#include <chrono>



int main(){
    Board board;
    char input;
    std::string Response;
    std::cout<<"Would you like to play a game?"<<std::endl;
    std::cin>>Response;
    //Response = "Y";
    std::transform(Response.begin(), Response.end(), Response.begin(),[](unsigned char c){ return std::tolower(c); });
    std::string PositiveReplys [] = {"yes","y","yeah","affirmative","okay","yea","all" "right","aye","by all means","certainly","definitely","gladly","indubitably","sure","undoubtedly","unquestionably"};
    bool good = false;
    for(int i = 0; i < 16; i++){
        if(Response == PositiveReplys[i]) {good = true; break;}
    }
    if(!good){std::cout<<"That's a shame"<<std::endl;return 0;}


    std::cout<<"One or two players?"<<std::endl;
    std::cin>>Response;
    //Response = "1";
    int players = 0;
    if(Response == "1" || Response == "one") {players = 1;}
    else {players = 2;}
    std::cout<<"Use alpha-beta pruning?"<<std::endl;
    std::cin>>Response;
    good = false;
    bool useAlphaBeta = false;
    for(int i = 0; i < 16; i++){
        if(Response == PositiveReplys[i]) {useAlphaBeta = true; break;}
    }
    std::cin.clear();
    std::cin.ignore(INT_MAX,'\n');
    int A = 0;
    
    //Board::drawBoard(board,std::cout);
    while(input != 'Q' && input != 'q') {

        if(board.turn % 2 == 0) {
            Board::drawBoard(board,std::cout);
            std::cout<<"It is WHITE'S turn, enter a number between 1 and 7 to drop your piece. enter q to quit"<<std::endl;
            std::cin.clear();
            input = std::cin.get();
            std::cin.clear();
            std::cin.ignore(INT_MAX,'\n');
            A = (input - 48) - 1;
            //A = ((board.turn / 2) % 7) + 1;
            if(A >= 0 && A < 7) {
                std::cout<<"White went with column "<<A+1<<std::endl;
                if(!board.makeMove(A,board.turn)) {std::cout<<"Invalid move try again"<<std::endl;}
                else {board.turn++;}
            } else {std::cout<<"Invalid move try again"<<std::endl;}
        }
        else {
            
            if(players == 2) {
                Board::drawBoard(board,std::cout);
                std::cout<<"It is BLACK'S turn, enter a number between 1 and 7 to drop your piece. enter q to quit"<<std::endl;
                std::cin.clear();
                input = std::cin.get();
                std::cin.clear();
                std::cin.ignore(INT_MAX,'\n');
                A = (input - 48) - 1;
            }
            else {
                if(useAlphaBeta) {
                    //std::cout<<"Used AB"<<std::endl;
                    auto start = std::chrono::steady_clock::now();
                    A = Board::pickMoveAB(board,board.turn);
                    auto end = std::chrono::steady_clock::now();
                    std::cout<<"Picked move in: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()<<"ns"<<std::endl;
                } else {
                    auto start = std::chrono::steady_clock::now();
                    A = Board::pickMove(board,board.turn);
                    auto end = std::chrono::steady_clock::now();
                    std::cout<<"Picked move in: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()<<"ns"<<std::endl;
                }
            }
            std::cout<<"Black went with column "<<A+1<<std::endl;
            board.makeMove(A,board.turn);
            board.turn++;
        }
        if(board.evaluateBoard() > 1000){
            Board::drawBoard(board,std::cout);
            std::cout<<"Black WINS!"<<std::endl;
            return 0;
        }
        else if(board.evaluateBoard() < -1000) {
            Board::drawBoard(board,std::cout);
            std::cout<<"White WINS!"<<std::endl;
            return 1;
        }
        if (board.turn >=  43) {
            std::cout<<"DRAW!!"<<std::endl;
            return 2;
        }
    }
}