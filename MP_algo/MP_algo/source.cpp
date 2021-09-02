﻿#include <iostream>
#include <fstream>
using namespace std;

void preMP(const char*, int, int []);
void MP(string, string);


int main()
{
    string p, text;
    fstream f;
    f.open("data.txt", ios::in);
    if (!f) {
        cout << "ERROR" << endl;
        return 0;
    }
    f >> text;
    f >> p;
    //cout << text << endl << p;
    f.close();
    MP(p, t);
    return 0;
}

/*
void preMP(const char* x, int m, int mpNext[])
{
    int i, j;
    i = 0;
    j = mpNext[0] = -1;
    while (i < m) {
        while (j > -1 && x[i] != x[j])
            j = mpNext[j];
        mpNext[++i] = ++j;
    }
}
void MP(string p, string t) {
    int m = p.length();
    int n = t.length();
    const char* pInC = p.c_str();
    const char* tInC = t.c_str();
    int i = 0, j = 0;
    int* mpNext;
    if (m > n) {
        cout << "Unsuccessful match" << endl;
        return;
    }
    mpNext = (int*)malloc(sizeof(int) * (m+1));
    preMP(pInC, m, mpNext);
    while (j < n) {
        while (i > -1 && pInC[i] != tInC[j])
            i = mpNext[i];
        i++; j++;
        if (i >= m) {
            cout << "Matching index found at " << j - i << endl;
            i = mpNext[i];
        }
    }
}
*/

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
