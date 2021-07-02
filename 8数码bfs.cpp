#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <stack>

using namespace std;

typedef struct state
{
    int arr[9];
    int hash;
    int pos;
    int step;
    int id;
} node;
node p[1000005];
int pre[1000005], cnt = 0;
int jc[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
int dir[4][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}};

int cantor(int arr[]) //康托展开
{
    int sum = 0;
    for (int i = 0; i < 9; i++)
    {
        int nmin = 0;
        for (int j = i + 1; j < 9; j++)
        {
            if (arr[i] > arr[j])
                nmin++;
        }
        sum += nmin * jc[8 - i];
    }
    return sum;
}

void swap(int *arr, int i, int j)
{
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

void print(int arr[]) //输出数组
{
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            cout << endl;
        cout << arr[i] << ' ';
    }
    cout << endl;
}

void printAns(int cnt) //输出结果
{
    cout << "路径:" << endl;
    int x = cnt;
    stack<node> s;
    while (pre[x] != -1)
    {
        s.push(p[x]);
        x = pre[x];
    }
    s.push(p[x]);
    while (!s.empty())
    {
        node now = s.top();
        s.pop();
        for (int i = 0; i < 9; i++)
        {
            if (i % 3 == 0)
                cout << endl;
            cout << now.arr[i] << ' ';
        }
        cout << endl;
    }
}

void copy(int src[], int target[]) //复制数组
{
    for (int i = 0; i < 9; i++)
        target[i] = src[i];
}

int bfs(int arr[], int sHash, int tHash) //广搜
{
    if (sHash == tHash)
        return 0;
    queue<node> q;
    set<int> Hash;
    node now, next;
    copy(arr, now.arr);
    int pos = 0;
    for (int i = 0; i < 9; i++)
    {
        if (arr[i] == 0)
            break;
        pos++;
    }
    now.hash = sHash;
    now.step = 0;
    now.pos = pos;
    now.id = cnt;
    next.step = 0;
    p[cnt++] = now;
    q.push(now);
    Hash.insert(now.hash);
    while (!q.empty())
    {
        now = q.front();
        q.pop();
        if (now.step == 35)
            continue;
        //print(now.arr);
        for (int i = 0; i < 4; i++)
        {
            int x = now.pos % 3 + dir[i][0];
            int y = now.pos / 3 + dir[i][1];
            if (x < 0 || x > 2 || y < 0 || y > 2)
                continue;
            copy(now.arr, next.arr);
            next.step = now.step + 1;
            next.pos = y * 3 + x;
            swap(next.arr, now.pos, next.pos);
            next.hash = cantor(next.arr);
            next.id = cnt;
            pre[cnt] = now.id;
            p[cnt++] = next;
            int begin = Hash.size();
            Hash.insert(next.hash);
            int end = Hash.size();
            if (next.hash == tHash)
            {
                printAns(cnt - 1);
                return next.step;
            }
            if (end > begin)
                q.push(next);
        }
    }
    return -1;
}

int inversion(int arr[]) //求逆序数
{
    int sum = 0;
    for (int i = 0; i < 9; i++)
        for (int j = i + 1; j < 9; j++)
        {
            if (arr[j] < arr[i] && arr[j] != 0)
                sum++;
        }
    return sum;
}

int main()
{
    for (int i = 0; i < 100005; i++)
        pre[i] = -1;
    string s, t;
    int is[9], it[9];
    cout << "初始状态：" << endl;
    for (int i = 0; i < 9; i++)
        cin >> is[i];
    cout << "目标状态：" << endl;
    for (int i = 0; i < 9; i++)
        cin >> it[i];
    for (int i = 0; i < 9; i++)
    {
        s[i] = '0' + is[i];
        t[i] = '0' + it[i];
    }
    int sHash = cantor(is);
    int tHash = cantor(it);
    int sinv = inversion(is);
    int tinv = inversion(it);
    if ((sinv + tinv) % 2 == 0)
    {
        int step = bfs(is, sHash, tHash);
        cout << "由初始状态经过" << step << "步达到目标状态。" << endl;
    }
    else
        cout << "无法从初始状态到达目标状态" << endl;
    return 0;
}
/*
2 8 3
1 6 4
7 0 5
1 2 3
8 0 4
7 6 5
*/