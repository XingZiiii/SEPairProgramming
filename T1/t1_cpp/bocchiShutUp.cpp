extern "C" {
    int bocchiShutUp(int flag, int* seq, int size){
        int num, max = 1, maxNum = 0, maxCount = 0;
        int freq[7] = {0, 0, 0, 0, 0, 0, 0};
        for (int i=0; i<size; i++) {
            if (seq[i] / 10 == flag){
                num = seq[i]%10;
                freq[num] ++;
                if (freq[num] > max){
                    max = freq[num];
                    maxNum = num;
                }
            }
        }
        for (int i=1; i<7; i++){
            if (freq[i] == max){
                maxCount ++;
            }
        }
        if (maxCount > 1) return 10;
        else return flag*10 + maxNum;
    };
}
