// luogu_tests.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <vector>
#include <set>
#include <tuple>
using namespace std;

struct Cnode {
    int pos;
    int direc;
    Cnode* front;
};
vector<Cnode> cow;
vector<Cnode> farmer;

int main()
{
    char a[10][10];
    for (int i = 0;i < 10;i++) {
        for (int j = 0;j < 10;j++) {
            cin >> a[i][j];
        }
    }

    int find(char a[10][10], char word);
    bool compare(const vector<Cnode>&cow, const vector<Cnode>&farmer);
    void sbs(char a[10][10], vector<Cnode>&cow);//step by step
    int basicfunc(char a[10][10], vector<Cnode>&cow, vector<Cnode>&farmer);

    Cnode c_head;
    Cnode f_head;

    c_head.pos = find(a, 'C');
    c_head.direc = -10;

    f_head.pos = find(a, 'F');
    f_head.direc = -10;

    cow.push_back(c_head);
    farmer.push_back(f_head);
    cout << basicfunc(a, cow, farmer) << endl;

    return 0;
}


int find(char a[10][10], char word) {
    for (int i = 0;i < 10;i++) {
        for (int j = 0;j < 10;j++) {
            if (a[i][j] == word) {
                return 10 * i + j + 1;
                break;
            }
        }
    }
}

bool compare(const vector<Cnode>& cow,const vector<Cnode>& farmer) {
    if (cow.back().pos == farmer.back().pos) {
        return true;
    }
    else return false;
}

void sbs(char a[10][10], vector<Cnode>& cow) {
    int pos = cow.back().pos;
    int row = (pos - 1) / 10;
    int col = (pos - 1) % 10;
    int d = cow.back().direc;

    int nr = row, nc = col;
    if (d == -10) nr = row - 1;      // 北
    else if (d == 1) nc = col + 1;   // 东
    else if (d == 10) nr = row + 1;  // 南
    else if (d == -1) nc = col - 1;  // 西

    Cnode temp = cow.back();

    if (nr < 0 || nr >= 10 || nc < 0 || nc >= 10 || a[nr][nc] == '*') {
        // 前方不可走，顺时针转 90 度
        if (d == -10) temp.direc = 1;
        else if (d == 1) temp.direc = 10;
        else if (d == 10) temp.direc = -1;
        else if (d == -1) temp.direc = -10;

        temp.pos = pos;  // 原地不动
    }
    else {
        // 前方可走，前进一步
        temp.direc = d;
        temp.pos = nr * 10 + nc + 1;
    }

    cow.push_back(temp);
}



int basicfunc(char a[10][10], vector<Cnode>& cow, vector<Cnode>& farmer) {
    set<tuple<int, int, int, int>> seen;

    seen.insert(make_tuple(cow.back().pos, cow.back().direc,
        farmer.back().pos, farmer.back().direc));

    for (int minute = 1; ; minute++) {
        sbs(a, cow);
        sbs(a, farmer);

        if (cow.back().pos == farmer.back().pos) {
            return minute;
        }

        auto state = make_tuple(cow.back().pos, cow.back().direc,
            farmer.back().pos, farmer.back().direc);

        if (seen.count(state)) {
            return 0;  // 状态重复，永远不会相遇
        }

        seen.insert(state);
    }
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
