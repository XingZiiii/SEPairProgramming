#include<vector>

#define p1_score  6
#define p2_score 13

using namespace std;

extern "C" {
    int isOver(vector<int> board) {
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
}
