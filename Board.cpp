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
                for(int j = 0; j < 6; j++) {
                    peices[j][i] = ' ';
                }
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
                for(int j = 0; j < 6; j++) {
                    peices[j][i] = p.peices[j][i];
                }
            }
        }

        void generateChildren() {
            hasChildren = true;
            int T = turn + 1;
            for(int i = 0; i < 7; i++)
            {
                if(tops[i] < 6) {
                    Board *Temp = new Board(*this, this);
                }
                else{children[i] = nullptr;}
            }
        }
        void evaluateBoard(){
            //I would love to think of a cleaner way to do this but for the life of me I can't figure one out
            int TotalForRed = 0, TotalForYel = 0;
            for(int i = 0; i < 7; i++) {
                char Owner = ' ';
                if(tops[i] >= 0) {
                    Owner = peices[tops[i]][i];
                    int diagUL = 0, diagDL = 0, diagUR = 0, diagDR = 0, Left = 0, Right = 0, Up = 0, Down = 0;
                    if(Owner != ' ') {
                        for(int j = 1; j < 3; j++) {
                            if((i + j) < 7) { //right
                                if(peices[tops[i]][i + j] == Owner) {Right++;}
                                else if(peices[tops[i]][i + j] != ' ') {Right = -4;}
                            }
                            if((i - j) >= 0) { //left
                                if(peices[tops[i]][i - j] == Owner) {Left++;}
                                else if(peices[tops[i]][i - j] != ' ') {Left = -4;}
                            }
                            if((tops[i] + j) < 6) { //Up
                                if(peices[tops[i] + j][i] == Owner) {Up++;}
                                else if(peices[tops[i] + j][i] != ' ') {Up = -4;}
                            }
                            if((tops[i] + j) >= 0) { //down
                                if(peices[tops[i] - j][i] == Owner) {Down++;}
                                else if(peices[tops[i] - j][i] != ' ') {Down = -4;}
                            }
                            if(((i + j) < 7) && ((tops[i] + j) < 6)) { //diag Up and Right
                                if(peices[tops[i] + j][i + j] == Owner) {diagUR++;}
                                else if(peices[tops[i] + j][i + j] != ' ') {diagUR = -4;}
                            }
                            if(((i + j) < 7) && ((tops[i] - j) >= 0))  { //Down and Right
                                if(peices[tops[i] - j][i + j] == Owner) {diagDR++;}
                                else if(peices[tops[i] - j][i + j] != ' ') {diagDR = -4;}
                            }
                            if(((i - j) >= 0) && ((tops[i] + j) < 6)) { //Up and Left
                                if(peices[tops[i] + j][i - j] == Owner) {diagUL++;}
                                else if(peices[tops[i] + j][i - j] != ' ') {diagUL = -4;}
                            }
                            if(((i - j) >= 0) && ((tops[i] - j) >= 0))  { //down and left
                                if(peices[tops[i] - j][i - j] == Owner) {diagDL++;}
                                else if(peices[tops[i] - j][i - j] != ' ') {diagDL = -4;}
                            }
                        }
                        if(diagUL == 3 || diagDL == 3 || diagUR == 3 || diagDR == 3 || Left == 3 || Right == 3 || Up == 3 || Down == 3) { // if any of these are 3 then it's a connect 4, winning moves have maximum value
                            if(Owner == 'W') {
                                valueForYel = INT_MAX;
                                valueForRed = 0;
                            }
                            if(Owner == 'B') {
                                valueForYel = 0;
                                valueForRed = INT_MAX;
                            }
                            return;
                        }
                        if(Owner == 'W') {
                            TotalForYel += diagUL + diagDL + diagUR + diagDR + Left + Right + Up + Down;
                        }
                        if(Owner == 'B') {
                            TotalForRed += diagUL + diagDL + diagUR + diagDR + Left + Right + Up + Down;
                        }
                    }
                }
            }
            
            valueForYel = TotalForYel;
            valueForRed = TotalForRed;
            return;
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