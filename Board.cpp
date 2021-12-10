//Board class
#include <iostream> // cout
#include <cmath> // abs
#include <assert.h> //for debuging
class Board {
    private:
        char pieces[6][7];
        char tops[7]; //contains the index of the top most filled spot in each colomn
        Board *children[7];
        Board *parent;

        bool hasChildren;
        bool isEvaluated;
    public:
        int turn;
        int valueForRed;
        int valueForYel;

        Board(){
            for(int i = 0; i < 7; i++) {
                tops[i] = -1;
                children[i] = nullptr;
                for(int j = 0; j < 6; j++) {
                    pieces[j][i] = ' ';
                }
            }
            parent = nullptr;
            valueForRed = valueForYel = 0;
            hasChildren = false;
            isEvaluated = false;
        }

        Board(Board& p, Board* Parent){
            isEvaluated = false;
            hasChildren = false;
            parent = Parent;
            turn = p.turn;

            for(int i = 0; i < 7; i++) {
                tops[i] = p.tops[i];
                children[i] = nullptr;
                for(int j = 0; j < 6; j++) {
                    pieces[j][i] = p.pieces[j][i];
                }
            }
        }

        ~Board() {
            for(int i = 0; i < 7; i++) {
                delete children[i];
            }
        }

        void generateChildren() {
            if(hasChildren) {
                for(int i = 0; i < 7; i++) {
                    delete children[i];
                }
            };
            hasChildren = true;
            for(int i = 0; i < 7; i++)
            {
                if(tops[i] < 6) {
                    Board *Temp = new Board(*this, this);
                    Temp->turn++;
                    Temp->makeMove(i,this->turn);
                    children[i] = Temp;
                    //drawBoard( *Temp,std::cout); // debug
                    //std::cout<<"Board Valued at: "<<Temp->evaluateBoard();
                }
                else {
                    children[i] = nullptr;
                    //std::cout<<"No child at column " << i <<std::endl;
                }
            }
        }
        int evaluateBoard(){
            if(this->isEvaluated) return this->valueForRed - this->valueForYel;
            this->isEvaluated = true;

            int TotalForRed = 0, TotalForYel = 0;
            for(int i = 0; i < 7; i++) {
                char Owner = ' ';
                if(tops[i] >= 0) {
                    assert(tops[i] < 6);
                    for(int j = 0; j < tops[i] + 1; j++) {
                        Owner = this->pieces[j][i];
                        unsigned char isAlive = 15;
                        int R = 1, U = 1, UR = 1, UL = 1;
                        for(int k = 1; k < 4; k++) {
                            int dX = i + k;
                            int dY = j + k;
                            if ((dX < 7) && ((isAlive & 1) != 0)) { //right
                                if(Owner == pieces[j][dX]) {
                                    R++;
                                }
                                else if(pieces[j][dX] != ' ') { //must Be the opposing player
                                    isAlive = isAlive & ~1;
                                }
                            }
                            if ((dY < 6) && ((isAlive & 2) != 0)) { //up
                                if(Owner == pieces[dY][i]) {
                                    U++;
                                }
                                else if(pieces[dY][i] != ' ') { //must Be the opposing player
                                    isAlive = isAlive & ~2;
                                }
                            }
                            if ((dY < 6) && (dX < 7) && ((isAlive & 4) != 0)) { //diagnal up and right
                                if(Owner == pieces[dY][dX]) {
                                    UR++;
                                }
                                else if(pieces[dY][dX] != ' ') { //must Be the opposing player
                                    isAlive = isAlive & ~4;
                                }
                            }
                            dX = i - k;
                            dY = j + k;
                            if ((dY < 6) && (dX >= 0) && ((isAlive & 8) != 0)) { //diagnal up and left
                                if(Owner == pieces[dY][dX]) {
                                    UL++;
                                }
                                else if(pieces[dY][dX] != ' ') { //must Be the opposing player
                                    isAlive = isAlive & ~8;
                                }
                            }
                        }
                        if(Owner == 'B') {
                            if ((isAlive & 1) != 0) { //right
                                TotalForRed += (R - 1);
                            }
                            if ((isAlive & 2) != 0) { //up
                                TotalForRed += (U - 1);
                            }
                            if ((isAlive & 4) != 0) { //diagnal up and right
                                TotalForRed += (UR - 1);
                            }
                            if ((isAlive & 8) != 0) { //diagnal up and left
                                TotalForRed += (UL - 1);
                            }
                            if(R == 4 || U == 4 || UR == 4 || UL == 4) {
                                TotalForRed = INT_MAX;
                            }
                        } else {
                            if ((isAlive & 1) != 0) { //right
                                TotalForYel += (R - 1);
                            }
                            if ((isAlive & 2) != 0) { //up
                                TotalForYel += (U - 1);
                            }
                            if ((isAlive & 4) != 0) { //diagnal up and right
                                TotalForYel += (UR - 1);
                            }
                            if ((isAlive & 8) != 0) { //diagnal up and left
                                TotalForYel += (UL - 1);
                            }
                            if(R == 4 || U == 4 || UR == 4 || UL == 4) {
                                TotalForYel = INT_MAX;
                            }
                        }
                    }
                }
            }

            this->valueForYel = TotalForYel;
            this->valueForRed = TotalForRed;

            return TotalForRed - TotalForYel ;
        }

        bool makeMove(int i, int t) {
            if(i >= 0 && i < 7) {
                if(this->tops[i] < 5) {
                    this->isEvaluated = false;
                    tops[i]++;
                    if((t % 2) == 0) {
                        this->pieces[tops[i]][i] = 'W';
                        return true;
                    }
                    this->pieces[tops[i]][i] = 'B';
                    return true;
                }
                else {return false;}
            }
            return false;
        }

        static void drawBoard(char B[6][7], std::ostream& outS){
            /* char cross = '#';//215;
            char thin = '#'; //196;
            char thick = '#'; //186; */
            char cross = 215;
            char thin = 196;
            char thick = 186;
            outS<<std::endl;
            for(int i = 0; i < 6; i++) {
                outS<<(char)199<<thin<<cross<<thin<<cross<<thin<<cross<<thin<<cross<<thin<<cross<<thin<<cross<<thin<<(char)182<<std::endl;
                //outS<<"#"<<thin<<cross<<thin<<cross<<thin<<cross<<thin<<cross<<thin<<cross<<thin<<cross<<thin<<"#"<<std::endl;
                for(int j = 0; j < 7; j++) {
                    outS<<thick;
                    outS<<B[5-i][j];
                }
                outS<<thick<<std::endl;;
            }
            outS<<(char)200<<(char)205<<(char)202<<(char)205<<(char)202<<(char)205<<(char)202<<(char)205<<(char)202<<(char)205<<(char)202<<(char)205<<(char)202<<(char)205<<(char)188<<std::endl;
            outS<<" 1 2 3 4 5 6 7 "<<std::endl;
        }
        static void drawBoard(Board& B, std::ostream& outS){
            drawBoard(B.pieces,outS);
        }

        /**
         * @brief Red attempts to minimize, Yellow to maximize
         * 
         * @param board is the board being evaluated
         * @param depth is the Maximun depth to Travel from this board
         * @param turn is the current turn at this board
         */
        static int miniMax(Board *board, int depth, int turn){
            if (depth == 0) {
                return board->evaluateBoard();
            }
            if(std::abs(board->evaluateBoard()) > 1000) {
                return board->evaluateBoard();
            }
            if(!board->hasChildren) {board->generateChildren();}
            int Max = -INT_MAX, Min = INT_MAX, A;
            for(int i = 0; i < 7; i++) {
                if(board->children[i] != nullptr) {
                    A = miniMax(board->children[i], depth - 1, turn + 1);
                    Min = (A < Min) ? A : Min;
                    Max = (A > Max) ? A : Max;
                }
            }
            if((turn % 2) == 0) {
                return Min;
            }
            return Max;
        }

        static int miniMaxAlphaBeta(Board *board, int depth, int turn, int Alpha, int Beta){
            if (depth == 0) {
                return board->evaluateBoard();
            }
            if(std::abs(board->evaluateBoard()) > 1000) {
                return board->evaluateBoard();
            }
            if(!board->hasChildren) {board->generateChildren();}
            int Max = -INT_MAX, Min = INT_MAX, A;
            for(int i = 0; i < 7; i++) {
                if(board->children[i] != nullptr) {
                    A = miniMax(board->children[i], depth - 1, turn + 1);
                    Min = (A < Min) ? A : Min;
                    Max = (A > Max) ? A : Max;
                    if((turn % 2) == 0) {
                        if(A > Beta) {return A;}
                        if(A > Alpha) {Alpha = A;}
                    } else {
                        if(A < Alpha) {return A;}
                        if(A < Beta) {Beta = A;}
                    }
                }
            }
            if((turn % 2) == 0) {
                return Min;
            }
            return Max;
        }

        static int pickMove(Board& board,int turn) {
            board.generateChildren();
            int Max = -INT_MAX, Min = INT_MAX, A;
            int minDex, maxDex;
            for(int i = 0; i < 7; i++) {
                if(board.children[i] != nullptr) {
                    A = board.miniMax(board.children[i], 4, turn+1);
                    if(A < Min) {
                        Min = A;
                        minDex = i;
                    }
                    if(A > Max) {
                        Max = A;
                        maxDex = i;
                    }
                }
            }
            //std::cout<<"Max evaluation: "<<Max<<"\tMin evaluation: "<<Min<<std::endl; //for debuging
            if((turn % 2) == 0) {
                return minDex;
            }
            return maxDex;
        }

        static int pickMoveAB(Board& board,int turn) {
            board.generateChildren();
            int Max = -INT_MAX, Min = INT_MAX, A;
            int minDex, maxDex;
            for(int i = 0; i < 7; i++) {
                if(board.children[i] != nullptr) {
                    A = board.miniMaxAlphaBeta(board.children[i], 4, turn+1,-INT_MAX,INT_MAX);
                    if(A < Min) {
                        Min = A;
                        minDex = i;
                    }
                    if(A > Max) {
                        Max = A;
                        maxDex = i;
                    }
                }
            }
            //std::cout<<"Max evaluation: "<<Max<<"\tMin evaluation: "<<Min<<std::endl; //for debuging
            if((turn % 2) == 0) {
                return minDex;
            }
            return maxDex;
        }
};