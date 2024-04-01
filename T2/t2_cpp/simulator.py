import random

p1_score = 6
p2_score = 13
# 选择 Debug 模式，输出模拟每局的具体棋盘状况
debug = False

# 生成播棋比赛
def generate_game():
    record = [[] for i in range(3)]
    # 初始化棋盘
    board = [4 for i in range(14)]
    board[p1_score] = 0
    board[p2_score] = 0
    
    # 随机选择先手玩家
    flag = random.randint(1, 2)
    pre = flag
    
    # 模拟游戏过程
    while True:
        if debug:
            print("当前先手: " + str(pre))
        # 轮到玩家1
        if pre == 1:
            # 随机选择一个非空的棋格
            move = random.choice([i for i in range(6) if board[i] != 0])
            record[0].append(10+move+1)
            # 更新棋盘
            n = board[move]
            board[move] = 0
            while n > 0:
                move = (move + 1) % 14
                if move == p2_score:
                    continue
                board[move] += 1
                n -= 1
            
            # 检查下次先手
            if move == p1_score:
                pre = 1
            else:
                pre = 2
            
            # 检查是否得子
            if board[move] == 1 and (move >= 0 and move <= 5):
                board[p1_score] += 1 + board[12-move]
                board[12-move] = 0
                board[move] = 0
        
        # 轮到玩家2
                
        else:  
            # 随机选择一个非空的棋格
            move = random.choice([i for i in range(7, 13) if board[i] != 0])
            record[0].append(20+move-6)
            # 更新棋盘
            n = board[move]
            board[move] = 0
            while n > 0:
                move = (move + 1) % 14
                if move == p1_score:
                    continue
                board[move] += 1
                n -= 1
            
            # 检查下次先手
            if move == p2_score:
                pre = 2
            else:
                pre = 1
            
            # 检查是否得子
            if board[move] == 1 and (move >= 7 and move <= 12):
                board[p2_score] += 1 + board[12-move]
                board[12-move] = 0
                board[move] = 0
        
        
        record[1].append(board[p1_score])
        record[2].append(board[p2_score])

        if debug:
            print("选择播撒位置: " + str(record[0][-1]))
            print("棋盘状态: ")
            print(" ".join(str(x) for x in reversed(board[7:14])))
            if (board[13] / 10 != 0):
                s = "   "
            else:
                s = "  "
            print(s + " ".join(str(x) for x in board[0:7]))
        # 检查游戏是否结束
                
        # 检查游戏是否结束
        if all(board[i] == 0 for i in range(6)) or all(board[i] == 0 for i in range(7, 13)):
            board[p1_score] += sum(board[i] for i in range(6))   
            board[p2_score] += sum(board[i] for i in range(7, 13))
            record[1][-1] = board[p1_score]
            record[2][-1] = board[p2_score]
            if debug:
                print("最后得分:", str(record[1][-1]) ,  str(record[2][-1]))
            return flag, record


def main():
    # 输入生成局数
    num = input()
    with open('data.txt', 'w') as f:
        for i in range(int(num)):
            isComplete = random.randint(0,1)
            pre, record = generate_game()
            
            if isComplete == 1:
                s = ", ".join(str(x) for x in record[0])
                s = "{" + s + "}"
                if pre == 1:
                    res = record[1][-1] - record[2][-1] + 15000
                else:
                    res = record[2][-1] - record[1][-1] + 15000
                f.write(str(pre) + ", " + str(len(record[0])) + ", " + s + ", " + str(res) + "\n")
            else:
                l = random.randint(1, len(record[0])-1)
                s = ", ".join(str(x) for x in record[0][:l])
                s = "{" + s + "}"
                if pre == 1:
                    res = record[1][l-1] + 20000
                else:
                    res = record[2][l-1] + 20000
                f.write(str(pre) + ", "  + str(l) + ", " + s + ", " + str(res) + "\n")
        
main()