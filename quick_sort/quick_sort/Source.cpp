#include<iostream>
#include<fstream>
using namespace std;

class quickSort
{
private:
    int length;
    int *list;
    void list_swap(int, int);
public:
    quickSort(int _len, int _data[]) {
        int i;
        length = _len;
        list = new int[length];
        for (i = 0; i < length; i++)
            list[i] = _data[i];
    }
    void quick_sort(int, int);
    void out_and_delData();
};


int main()
{
    int i, n, data;
    int* list;
    quickSort* A;
    fstream f;
    f.open("data.txt", ios::in);
    for (n = 0; !f.eof();) {
        f >> data;
        if (!f) {
            cout << "ERROR read file" << endl;
            return 0;
        }
        n++;
    }
    f.close();
    if (!n)
        return 0;
    list = new int[n];
    f.open("data.txt", ios::in);
    for (i = 0; i < n; i++)
        f >> list[i];
    f.close();
    A = new quickSort(n, list); delete[]list;
    A->quick_sort(0, n - 1);
    A->out_and_delData();
    delete A;
	return 0;
}

// in-place version
void quickSort::quick_sort(int left, int right) {
    int i, pivot, index;
    if (right - left <= 1)
        return;
    index = (left + right) / 2; //index is pivotIndex
    pivot = list[index];
    list_swap(index, right);
    for (i = left, index = left; i < right ; i++) {     //index is used to mark bigger element
        if (list[i] < pivot) {
            list_swap(i, index);    //sometimes swap small and small
            index++;  //i will go further than index if a bigger element is found, and index will keep until another smaller element is found
        }
    }
    list_swap(index, right); //index is where pivot should put
    quick_sort(left, index - 1);
    quick_sort(index + 1, right);
    return;
}

void quickSort::list_swap(int m, int n) {
    int temp;
    temp = list[m];
    list[m] = list[n];
    list[n] = temp;
}

void quickSort::out_and_delData() {
    int i;
    for (i = 0; i < length; i++)     //print result
        cout << list[i] << ' ';
    delete []list;
}