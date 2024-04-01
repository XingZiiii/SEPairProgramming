#include<assert.h>
#include<fstream>
#include<iostream>
#include<string.h>
#include<ctype.h>
#include "mancalaResult.h"

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