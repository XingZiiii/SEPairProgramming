#include<vector>
#define p1_score  6
#define p2_score 13
using namespace std;

extern "C" {
    int isOver(vector<int> board, int pre) {
        if (pre == 1) {
            for (int i = 0; i < 6; i++) {
                if (board[i] != 0) {
                    return 0;
                }
            }
            return 1;
        } else {
            for (int i = 7; i < 13; i++) {
                if (board[i] != 0) {
                    return 0;   
                }    
            }
            return 1;
        }
    }   
    
    int mancalaResult(int flag, int *seq, int size) {
        int pre = flag;
        vector<int> board(14, 4);
        board[p1_score] = 0;
        board[p2_score] = 0;
        for (int i = 0; i < size; i++) {
            int cur = seq[i];
            // 判断先手是否正确
            if (pre != cur / 10) {
                return 30000 + i;
            }
            int pos = cur % 10;
            // 判断取的位置是否为空
            if (board[pos] == 0) {
                return 30000 + i;
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
            if ((pre == 1 && (pos >= 0 && pos <= 5) && board[pos] == 1) || (pre == 2 && (pos >= 7 && pos <= 12) && board[pos] == 1)) {
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
            if (isOver(board, pre) && i != size - 1) {
            return 30000 + i + 1;
            }
        }
        // 判断是否结束
        if (isOver(board, pre)) {
            int res = (flag == 1) ? (board[p1_score] - board[p2_score]) : (board[p2_score] - board[p1_score]);
            return 15000 + res;
        } else {
            int res = (flag == 1) ? board[p1_score] : board[p2_score];
            return 20000 + res;
        }
    }
}