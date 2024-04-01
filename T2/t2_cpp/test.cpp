#include<assert.h>
#include<fstream>
#include<iostream>
#include<string.h>
#include<ctype.h>

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
    for (int i = 7; i < 13; i++) {
        if (board[i] != 0) {
            flag = 0;
            break;
        }
    }
    return flag;
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
        int pos = cur % 10 - 1;
        if (cur / 10 == 2) {
            pos += 7;
        }
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
        // 判断是否结束
        if (isOver(board) && i != size - 1) {
            return 30000 + i + 1;
        }
        // 确定下一步先手
        if ((pre == 1 && pos == p1_score) || (pre == 2 && pos != p2_score)) {
            pre = 1;
        } else {
            pre = 2;
        }
    }
    // 判断是否结束
    if (isOver(board)) {
        for (int i = 0; i < 6; i++) {
            board[p1_score] += board[i];
        }
        for (int i = 7; i < 13; i++) {
            board[p2_score] += board[i];
        }
        int res = (flag == 1) ? (board[p1_score] - board[p2_score]) : (board[p2_score] - board[p1_score]);
        return 15000 + res;
    } else {
        int res = (flag == 1) ? board[p1_score] : board[p2_score];
        return 20000 + res;
    }
}

//测试异常数据
// 错误操作者
void test_exception_wrong_operator() {
    int array1[] = {12, 11, 21};
    assert(mancalaResult(1, array1, 3) == 30001);

    int array2[] = {11, 21, 22};
    assert(mancalaResult(1, array2, 3) == 30002);
    
    int array3[] = {13, 12, 11, 21};
    assert(mancalaResult(1, array3, 4) == 30002);

    int array4[] = {23, 22, 21, 11};
    assert(mancalaResult(2, array4, 4) == 30002);
};

// 拿无棋子的格子
void test_exception_operate_empty(){
    int array1[] = {12, 21, 12};
    assert(mancalaResult(1, array1, 3) == 30002);

    int array2[] = {21, 12, 21, 12};
    assert(mancalaResult(2, array2, 4) == 30002);
};

// 已经结束，还要操作
void test_exception_operate_after_end(){
    int array1[] = {23, 26, 16, 21, 14, 24, 11, 22, 12, 22, 13, 26, 14, 21, 16, 24, 15, 21, 16, 24, 11};
    assert(mancalaResult(2, array1, 21) == 30019);
};

// 测试正确情况
void test_big_data(){
    std::ifstream in;
    in.open("data.txt", std::ios::in);
    assert(in.is_open());
    std::string s;
    while(getline(in, s)){
        int len = s.size();
        
        int pre = 0, i = 0;
        while(i < len &&  isdigit(s[i])) {
            pre = pre * 10 + s[i] - '0';
            i++;
        }
        while (i < len && (s[i] == ',' || s[i]==' ' || s[i]=='{')) i++;

        int size=0;
        while(i < len &&  isdigit(s[i])) {
            size = size * 10 + s[i] - '0';
            i++;
        }
        int *array = new int[size];
        int index = 0;
        while (i < len && (s[i] == ',' || s[i]==' ' || s[i]=='{')) i++;
        while(i < len && s[i] != '}') {
            int number = 0;
            while(i < len &&  isdigit(s[i])) {
                number = number * 10 + s[i] - '0';
                i++;
            }
            array[index++] = number;

            while (i < len && (s[i] == ',' || s[i]==' ')) i++;
        }

        while (s[i] == ',' || s[i]==' ' || s[i]=='}') i++;
        int result = 0;
        while(i < len &&  isdigit(s[i])) {
            result = result * 10 + s[i] - '0';
            i++;
        }

        int res =  mancalaResult(pre, array, size);
        assert(res == result);

        delete[] array;
    }
}


void test_all(){
    test_exception_wrong_operator();
    test_exception_operate_empty();
    test_exception_operate_after_end();
    test_big_data();
};

int main(){
    test_all();
    return 0;
};