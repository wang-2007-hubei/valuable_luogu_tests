// luogu_tests.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int m, n;
    int seq[400];//给定的安排顺序
    int mach_n[20][20];//机器号
    int prc_t[20][20];//加工时间

    for (int i = 0;i < 20;i++) {
        for (int j = 0;j < 20;j++) {
            mach_n[i][j] = 0;
            prc_t[i][j] = 0;
        }
    }

    cin >> m;
    cin >> n;
    for (int i = 0;i < m * n;i++) {
        cin >> seq[i];
    }
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> mach_n[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> prc_t[i][j];

    vector<vector<int>> machine(m + 1); // 每台机器的时间轴，0 表示空闲
    vector<int> done(n + 1, 0);         // 每个工件已安排了几道工序
    vector<int> finish(n + 1, 0);       // 每个工件上一道工序完成时间
 
    int func(int m, int n, int mach_n[20][20], int prc_t[20][20], int i, int seq[], vector<vector<int>>&machine, vector<int>&done, vector<int>&finish);
    
    int maxn = 0;
    for (int i = 0;i < m * n;i++) {
        maxn = max(maxn, func(m, n, mach_n, prc_t, i, seq,machine,done,finish));
    }
    cout << maxn << "\n";
    return 0;
}


int func(int m, int n, int mach_n[20][20], int prc_t[20][20],int i, int seq[], vector<vector<int>>& machine, vector<int>& done, vector<int>& finish) {
    int job = seq[i];//取出工件号

    int ans = 0;
    
    int op = done[job];done[job]++;//当前工序号
    int mac = mach_n[job - 1][op];//得到机器号
    int need = prc_t[job - 1][op];//得到加工时间
    
    //从 finish[job] 开始，在 machine[mac] 上找第一个长度为 need 的连续空闲区间
    int start = finish[job];  // 不能早于该工件上一道工序完成时间

    while (true) {
        bool ok = true;

        for (int u = start; u < start + need; u++) {
            if (u < (int)machine[mac].size() && machine[mac][u] != 0) {
                ok = false;
                break;
            }
        }

        if (ok) break;  // 找到最前面的可行空档
        start++;
    }

    if ((int)machine[mac].size() < start + need)
        machine[mac].resize(start + need, 0);

    for (int t = start; t < start + need; t++)
        machine[mac][t] = job;

    finish[job] = start + need;
    ans = max(ans, finish[job]);
    return ans;
}