#include<vector>
#include<math.h>
#include<iostream>

#define p1_score  6
#define p2_score 13
#define INF INT_MAX
#define DEPTH 10


using namespace std;

extern "C" {
    int isOver(vector<int>& board) {
        int flag = 1;
        for (int i = 0; i < 6; i++) {
            if (board[i] != 0) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            return 1;
        }
        flag = 1;
        for (int i = 7; i < 13; i++) {
            if (board[i] != 0) {
                flag = 0;
                break;
            }
        }
        return flag;
    }   

    int* mancalaBoard(int flag, int *seq, int size) {
        int pre = seq[0] / 10;
        vector<int> board(14, 4);
        board[p1_score] = 0;
        board[p2_score] = 0;
        bool violate = 0;
        for (int i = 0; i < size; i++) {
            int cur = seq[i];
            // 判断先手是否正确
            if (pre != cur / 10) {
                violate = cur / 10;
                break;
            }
            int pos = cur % 10 - 1;
            if (cur / 10 == 2) {
                pos += 7;
            }
            // 判断取的位置是否为空
            if (board[pos] == 0) {
                violate = pre;
                break;
            }
            int num = board[pos];
            board[pos] = 0;
            // 进行播散
            while (num > 0) {
                pos = (pos + 1) % 14;
                if (pre == 1 && pos == p2_score) {
                    continue;
                } else if (pre == 2 && pos == p1_score) {
                    continue;
                }
                board[pos]++;
                num--;
            }
            // 判断是否取子
            if ((pre == 1 && (pos >= 0 && pos <= 5) && board[pos] == 1 && board[12-pos] != 0) || (pre == 2 && (pos >= 7 && pos <= 12) && board[pos] == 1 && board[12-pos] != 0)) {
                board[pos] = 0;
                int take = 12 - pos;
                int n = board[take];
                board[take] = 0;
                if (pre == 1) {
                    board[p1_score] += n + 1;
                } else {
                    board[p2_score] += n + 1;
                }
            }
            
            // 确定下一步先手
            if ((pre == 1 && pos == p1_score) || (pre == 2 && pos != p2_score)) {
                pre = 1;
            } else {
                pre = 2;
            }

            // 判断是否结束
            if (isOver(board) && i != size - 1) {
                violate = seq[i+1] / 10;
                break;
            }
        }

        
        int data;
        // 判断是否违规
        if (violate){
            data = 200;
            if (violate == 1) {
                data += 2*board[p1_score] - 48;
            } else {
                data -= 2*board[p2_score] - 48;
            };
        }

        // 判断是否结束
        else if (isOver(board)) {
            for (int i = 0; i < 6; i++) {
                board[p1_score] += board[i];
                board[i] = 0;
            }
            for (int i = 7; i < 13; i++) {
                board[p2_score] += board[i];
                board[i] = 0;
            }
            data = 200 + board[p1_score] - board[p2_score];
        } else {
           data = pre;
        }

        int *res = new int[15];
        for (int i = 0; i < 14; i++) {
            res[i] = board[i];
        }
        res[14] = data;
        return res;
    }

    int evaluate(int flag, std::vector<int>& board) {
        int sum1 = 0;
        for (int i=0; i<7; i++){
            sum1 += board[i];
        }
        int sum2 = 48-sum1;
        int score1 = board[p1_score];
        int score2 = board[p2_score];

        int grid_empty = 0;
        for (int i=0; i<14; i++){
            if (board[i] == 0) grid_empty++;
        }

        int polar = sum1<sum2 ? -1 : 1;

        if (score1+score2 < 30){
            if (flag == 1){
                return score1-score2;
            } else {
                return score2-score1;
            }
        } else {
            if (sum1 == sum2) {
                return 0;
            } else if (flag == 1) {

                return (sum1 - sum2 + grid_empty);
            } else {
                return (sum2 - sum1 + grid_empty);
            }
        }
    };

    vector<int> mancalaMove(const vector<int>& oldBoard, int move){
        vector<int> board = oldBoard;
        int pre = board[14];
        int pos = move;
        if (pre == 2) {
            pos += 7;
        }
                
        int num = board[pos];
        board[pos] = 0;
        // 进行播散
        while (num > 0) {
            pos = (pos + 1) % 14;
            if (pre == 1 && pos == p2_score) {
                continue;
            } else if (pre == 2 && pos == p1_score) {
                continue;
            }
            board[pos]++;
            num--;
        }
        // 判断是否取子
        if ((pre == 1 && (pos >= 0 && pos <= 5) && board[pos] == 1 && board[12-pos] != 0) || (pre == 2 && (pos >= 7 && pos <= 12) && board[pos] == 1 && board[12-pos] != 0)) {
            board[pos] = 0;
            int take = 12 - pos;
            int n = board[take];
            board[take] = 0;
            if (pre == 1) {
                board[p1_score] += n + 1;
            } else {
                board[p2_score] += n + 1;
            }
        }
            
        // 确定下一步先手
        if (isOver(board)){
            pre = 3;
        } else if ((pre == 1 && pos == p1_score) || (pre == 2 && pos != p2_score)) {
            pre = 1;
        } else {
            pre = 2;
        }
        board[14] = pre;
        return board;
    }

    int minMax(int flag, std::vector<int>& board, int depth, int alpha, int beta) {
        int begin = board[14]==1 ? 0:7;
        if (depth == 0 || board[14]==3) {
            return evaluate(flag, board);
        }
        if (flag == board[14]) {
            // 最大策略
            int maxEval = -INF;
            for (int i = begin; i < begin+6; i++) {
                if (board[i] == 0) continue;
                std::vector<int> newboard = mancalaMove(board, i-begin);
                int eval = minMax(flag, newboard, depth-1, alpha, beta);
                // cout << "maxeval: " << eval << endl;
                maxEval = max(maxEval, eval);
                alpha = max(alpha, eval);
                if (beta <= alpha) {
                    break;
                }
            }
            return maxEval;
        } else {
            // 最小策略
            int minEval = INF;
            for (int i = begin; i < begin + 6; i++) {
                if (board[i] == 0) continue;
                std::vector<int> newboard = mancalaMove(board, i-begin);
                int eval = minMax(flag, newboard, depth-1, alpha, beta);
                // cout << "mineval: " << eval << endl;
                minEval = min(minEval, eval);
                beta = min(beta, eval);
                if (beta <= alpha) {
                    break;
                }
            }
            return minEval;
        }
    }

    int findBestMove(int flag, int *status) {
        int begin = flag==1 ? 0:7;
        int maxEval = -INF;
        int maxMove = -1;
        vector<int> board(status, status + 14);
        board.push_back(flag);

        for (int i = begin; i < begin + 6; i++) {
            if (status[i] == 0) continue;

            //走一步
            std::vector<int> newboard = mancalaMove(board, i-begin);
            int eval = minMax(flag, newboard, DEPTH, -INF, INF);
            // cout << "TEST: " << eval << endl;
            if (eval > maxEval) {
                maxEval = eval;
                maxMove = i;
            }
        }
        return maxMove - begin;
    }

    int mancalaOperator(int flag, int* status) {
        int move = findBestMove(flag, status);
        return flag * 10 + move + 1;
    }
    
}
// test
// int main() {
//     int seq[100];
//     int op = 1, size = 0;
//     int *board;
//     board = new int[14]{4,4,4,4,4,4,0,4,4,4,4,4,4,0};
//     while (op < 3){
//         int move;
//         if (op == 1) {
//             cin >> move;
//         } else {
//             move = mancalaOperator(op, board);
//         }

//         // int move = mancalaOperator(op, board);
//         seq[size++] = move;
//         board = mancalaBoard(op, seq, size);
//         op = board[14];
        
//         cout << move << endl;
//         for (int i = 0; i < 15; i++){
//             cout << board[i] << " ";
//         }
//         cout << endl;
//     }
//     cout << "score:" << op-200 << endl;
// }