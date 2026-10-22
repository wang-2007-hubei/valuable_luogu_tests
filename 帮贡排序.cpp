// luogu_tests.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <vector>
#include<string>
#include<algorithm>


using namespace std;


struct Person {
	string name;
	string pos;
	int contribute;
	int level;
	int id; // 原始输入顺序
}people[115];

int rankPos(const string& p) {
	if (p == "BangZhu") return 7;
	if (p == "FuBangZhu") return 6;
	if (p == "HuFa") return 5;
	if (p == "ZhangLao") return 4;
	if (p == "TangZhu") return 3;
	if (p == "JingYing") return 2;
	return 1; // BangZhong
}

bool cmp1(const Person& p,const Person& q) {
	if (p.contribute == q.contribute) return p.id < q.id;
	return p.contribute > q.contribute;
}

bool cmp2(const Person& p, const Person& q) {
	if (rankPos(p.pos) == rankPos(q.pos)) {
		if (p.level == q.level)return p.id < q.id;
		return p.level > q.level;
	}
	return rankPos(p.pos) > rankPos(q.pos);
}

int main()
{
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++) {
		cin >> people[i].name >> people[i].pos >> people[i].contribute >> people[i].level;
		people[i].id = i;
	}
	sort(people + 4, people + n+1, cmp1);
	for (int i = 1;i <= n;i++) {
		if (i == 1) {
			people[i].pos = "BangZhu";
		}
		else if (i >= 2 && i <= 3)people[i].pos = "FuBangZhu";
		else if (i >= 4 && i <= 5)people[i].pos = "HuFa";
		else if (i >= 6 && i <= 9)people[i].pos = "ZhangLao";
		else if (i >= 10 && i <= 16)people[i].pos = "TangZhu";
		else if (i >= 17 && i <= 41)people[i].pos = "JingYing";
		else {
			people[i].pos = "BangZhong";
		}
	}
	sort(people + 4, people + 1 + n, cmp2);
	for (int i = 1;i <= n;i++) {
		cout << people[i].name << " " << people[i].pos << " " << people[i].level << "\n";
	}
    return 0;
}

