#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>

using namespace std;

typedef struct status
{
    int arr[16];
    int pos;
    int fn;
    int dn;
    int hn;
    bool operator<(const status &a) const
    {
        return fn > a.fn;
    }
} node;

int arr[16], target[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
map<string, string> pre;
map<string, int> f;

int dir[4][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}};

void swap(int *arr, int i, int j)
{
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

void print(string s) //输出数组
{
    for (int i = 0; i < 16; i++)
    {
        if (i % 4 == 0)
            cout << endl;
        int t = s[i] - '0';
        cout << t << ' ';
    }
    cout << endl;
}

void printAns(string res) //输出答案
{
    cout << "路径：" << endl;
    string x = res;
    stack<string> s;
    while (pre[x] != x)
    {
        s.push(x);
        x = pre[x];
    }
    s.push(x);
    while (!s.empty())
    {
        string st = s.top();
        s.pop();
        print(st);
    }
}

void copy(int src[], int target[]) //复制数组
{
    for (int i = 0; i < 16; i++)
        target[i] = src[i];
}

string toString(int arr[])
{
    string res = "";
    for (int i = 0; i < 16; i++)
    {
        char c = '0' + arr[i];
        res += c;
    }
    return res;
}

int getDis(int i, int j, int l, int r)
{
    return abs(i - l) + abs(j - r);
}

int getH(int arr[], int target[])
{
    int res = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            int flag = 0;
            for (int l = 0; l < 4; l++)
            {
                for (int r = 0; r < 4; r++)
                    if (arr[4 * i + j] == target[4 * l + r])
                    {
                        res += getDis(i, j, l, r);
                        flag = 1;
                        break;
                    }
                if (flag)
                    break;
            }
        }
    return res;
}

int Astar(int arr[], string Sstr, string Tstr)
{
    if (Sstr == Tstr)
        return 0;
    priority_queue<node> q;
    node now, next;
    copy(arr, now.arr);
    int pos = 0;
    for (int i = 0; i < 16; i++)
    {
        if (arr[i] == 0)
            break;
        pos++;
    }
    string res = Sstr;
    pre[res] = res;
    now.pos = pos;
    now.dn = 0;
    now.hn = getH(now.arr, target);
    now.fn = now.dn + now.hn;
    f[res] = now.fn;
    q.push(now);
    while (!q.empty())
    {
        now = q.top();
        q.pop();
        if (now.dn == 50)
            continue;
        for (int i = 0; i < 4; i++)
        {
            int x = now.pos % 4 + dir[i][0];
            int y = now.pos / 4 + dir[i][1];
            if (x < 0 || x > 3 || y < 0 || y > 3)
                continue;
            copy(now.arr, next.arr);
            next.dn = now.dn + 1;
            next.pos = y * 4 + x;
            swap(next.arr, now.pos, next.pos);
            next.hn = getH(next.arr, target);
            next.fn = next.hn + next.dn;
            res = toString(next.arr);
            //print(res);
            //cout << next.fn << endl;
            if (res == Tstr)
            {
                pre[res] = toString(now.arr);
                printAns(res);
                return next.dn;
            }
            if (pre.count(res) == 0)
            {
                pre[res] = toString(now.arr);
                f[res] = next.fn;
                q.push(next);
            }
            else if (f[res] > next.fn)
            {
                pre[res] = toString(now.arr);
                f[res] = next.fn;
                q.push(next);
            }
        }
    }
    return -1;
}

int main()
{
    string s, t;
    cout << "初始状态：" << endl;
    for (int i = 0; i < 16; i++)
        cin >> arr[i];
    cout << "目标状态：" << endl;
    for (int i = 0; i < 16; i++)
        cin >> target[i];
    s = toString(arr);
    t = toString(target);
    int step = Astar(arr, s, t);
    if (step == -1)
        cout << "无法从初始状态到达目标状态。" << endl;
    else
        cout << "由初始状态经过" << step << "步到达目标状态。" << endl;
    return 0;
}
/*
5 1 2 4
9 6 3 8
13 15 10 11
14 0 7 12
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 0

0 4 7 13
8 11 1 5
2 9 10 12
15 6 14 3
*/