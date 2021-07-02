#include<iostream>
#include<cstdio>

using namespace std;

int target[10] = {0, 1, 2, 3, 8, 0, 4, 7, 6, 5};
int m1[8] = {1, 4, 7, 8, 9, 6, 3, 2};
int m2[4] = {5, 6, 3, 2};
int ma[8] = {1, 4, 7, 8, 9, 6, 5, 2};
int mb[8] = {3, 2, 5, 4, 7, 8, 9, 6};
int mc[6] = {7, 8, 9, 6, 5, 4};
int md[9] = {4, 1, 2, 5, 6, 3, 2, 1, 4};
int mf[4] = {7, 8, 5, 4};
int mg[13] = {4, 1, 2, 3, 6, 5, 8, 9, 6, 3, 2, 1, 4};

bool check(int arr[])
{
    for (int i = 1; i <= 9; i++)
        if(arr[i] != target[i])
            return false;
    return true;
}

void swap(int *arr, int i, int j)
{
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

void print(int arr[])
{
    for (int i = 1; i <= 9; i++)
    {
        cout << arr[i] << ' ';
        if(i%3 == 0)
            cout << endl;
    }
}

int main()
{
    int arr[10], i, j;
    int target[10] = {0, 1, 2, 3, 8, 0, 4, 7, 6, 5};
    cout << "输入初始状态：" << endl;
    for (int i = 1; i <= 9; i++)
        cin >> arr[i];
    cout << "目标状态为：" << endl;
    print(target);
    //第一步
    if(arr[3] == 1 && arr[5] != 0)
    {
        for (i = 1;; i++)
            if(arr[i] == 0)
                break;
        for (j = 0;;j++)
            if(m1[j] == i)
                break;
        while(arr[3] == 1 || arr[3] == 0)
        {
            swap(arr, m1[j], m1[(j + 1) % 8]);
            j = (j + 1) % 8;
        }
    }
    else if(arr[3] == 1 && arr[5] == 0)
    {
        i = 5;
        for (;;j++)
            if(m2[j] == i)
                break;
        while(arr[3] == 1 || arr[3] == 0)
        {
            swap(arr, m2[j], m2[(j + 1) % 4]);
            j = (j + 1) % 4;
        }
    }
    else if(arr[3] == 0)
    {
        i = 3;
        for (j = 0;;j++)
            if(m2[j] == i)
                break;
        while(arr[3] == 1 || arr[3] == 0)
        {
            swap(arr, m2[j], m2[(j + 1) % 4]);
            j = (j + 1) % 4;
        }
    }
    cout << "第一步的结果为：" << endl;
    print(arr);
    //第二步
    for (i = 1;; i++)
        if(arr[i] == 0)
            break;
    for (j = 0;; j++)
        if(ma[j] == i)
            break;
    while(arr[1] != 1)
    {
        swap(arr, ma[j], ma[(j + 1) % 8]);
        j = (j + 1) % 8;
    }
    cout << "第二步的结果为：" << endl;
    print(arr);
    //第三步
    for (i = 1;; i++)
        if(arr[i] == 0)
            break;
    for (j = 0;; j++)
        if(mb[j] == i)
            break;
    while(arr[2] != 2)
    {
        swap(arr, mb[j], mb[(j + 1) % 8]);
        j = (j + 1) % 8;
    }
    cout << "第三步的结果为：" << endl;
    print(arr);
    if(arr[3] == 3)
        cout << "跳到第六步" << endl;
    else
    {
        //第四步
        for (i = 1;; i++)
            if(arr[i] == 0)
                break;
        for (j = 0;; j++)
            if(mc[j] == i)
                break;
        while(arr[5] != 3)
        {
            swap(arr, mc[j], mc[(j + 1) % 6]);
            j = (j + 1) % 6;
        }
        cout << "第四步的结果为：" << endl;
        print(arr);
        //第五步
        i = 4;
        for (j = 0;; j++)
            if(md[j] == i)
                break;
        do{
            swap(arr, md[j], md[(j + 1) % 9]);
            j = (j + 1) % 9;
        } while (arr[4] != 0);
        cout << "第五步的结果为：" << endl;
        print(arr);
    }
    //第六步
    for (j = 0;; j++)
        if(mc[j] == i)
            break;
    while(arr[6] != 4)
    {
        swap(arr, mc[j], mc[(j + 1) % 6]);
        j = (j + 1) % 6;
    }
    cout << "第六步的结果为：" << endl;
    print(arr);
    if(arr[9] == 5)
        cout << "跳到第九步" << endl;
    else
    {
        //第七步
        for (i = 1;; i++)
            if(arr[i] == 0)
                break;
        for (j = 0;; j++)
            if(mf[j] == i)
                break;
        while(arr[5] == 5)
        {
            swap(arr, mf[j], mf[(j + 1) % 4]);
            j = (j + 1) % 4;
        }
        cout << "第七步的结果为：" << endl;
        print(arr);
        //第八步
        i = 4;
        for (j = 0;; j++)
            if(mg[j] == i)
                break;
        do{
            swap(arr, mg[j], mg[(j + 1) % 13]);
            j = (j + 1) % 13;
        } while (arr[4] != 0);
        cout << "第八步的结果为：" << endl;
        print(arr);
    }
    //第九步
    for (j = 0;; j++)
        if(mf[j] == i)
            break;
    while(arr[8] != 6)
    {
        swap(arr, mf[j], mf[(j + 1) % 4]);
        j = (j + 1) % 4;
    }
    if(arr[4] == 8 && arr[7] == 7)
    {
        cout << "达到目标" << endl;
        print(arr);
    }
    else
        cout << "无解" << endl;
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