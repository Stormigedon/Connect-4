//Board class
#include <iostream>

class Board {
    private:
        char peices[6][7];
        char tops[7]; //contains the index of the top most filled spot in each colomn
        Board *children[7];
        Board *parent;
        int turn;
        bool hasChildren;
    public:
        int valueForRed;
        int valueForYel;

        Board(){
            for(int i = 0; i < 7; i++) {
                tops[i] = -1;
                children[i] = nullptr;
            }
            parent = nullptr;
            valueForRed = valueForYel = 0;
        }
        Board(char iPeices[6][7], int T, char iTops[], Board P){
            
        }
        Board(Board& p, Board* Parent){
            parent = Parent;
            turn = p.turn;

            for(int i = 0; i < 7; i++) {
                tops[i] = p.tops[i];
                children[i] = nullptr;
            }
        }

        void generateChildren() {
            int T = turn + 1;
            for(int i = 0; i < 7; i++)
            {
                Board *Temp = new Board(*this, this);
            }
        }
        int evaluateBoard(int Player){
            //one point for every available line to win, one point for every peice on that like in your color
            int totalForWhite = 0, totalForBlack = 0;
            
            
            for(int i = 0; i < 4; i++) {
            }

            //if 4 in row return int_max
            if(/*4 in a row*/false) {
                return INT_MAX * (((Player % 2) * -2) + 1);
            }

        }
        void scanPos(int X, int Y) {
            int totalForWhite, totalForBlack;
            for(int i = 1; i < 4; i++)
            {
                if(X-i >= 0) {
                    char left = peices[Y][X-i];
                }
            }
        }
        bool makeMove(int i, int t) {
            if(i >= 0 && i < 7) {
                if(this->tops[i] < 6) {
                    if((t % 2) == 0) {
                        this->peices[tops[i] + 1][i] = 'B';
                        return true;
                    }
                    this->peices[tops[i] + 1][i] = 'W';
                    return true;
                }
            }
            return false;
        }

        static void drawBoard(char B[6][7], std::ostream& outS){
            char cross = 215;
            char thin = 196;
            char thick = 186;
            outS<<std::endl;
            for(int i = 0; i < 6; i++) {
                outS<<(char)199<<thin<<cross<<thin<<cross<<thin<<cross<<thin<<cross<<thin<<cross<<thin<<cross<<thin<<(char)182<<std::endl;
                for(int j = 0; j < 7; j++) {
                    outS<<thick;
                    if(B[5-i][j] != ' ')
                        outS<<B[5-i][j];
                    else
                        outS<<i;
                }outS<<thick<<std::endl;;
            }
            outS<<(char)200<<(char)205<<(char)202<<(char)205<<(char)202<<(char)205<<(char)202<<(char)205<<(char)202<<(char)205<<(char)202<<(char)205<<(char)202<<(char)205<<(char)188<<std::endl;
        }

        /**
         * @brief Black attempts to minimize, white to maximize
         * 
         * @param board is the board being evaluated
         * @param depth is the Maximun depth to Travel from this board
         * @param turn is the current turn at this board
         */
        static int miniMax(Board *board, int depth, int turn){
            if (depth == 0) {return board->evaluateBoard(turn);}
            if(!board->hasChildren) {board->generateChildren();}

            int Max, Min, A;
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
};