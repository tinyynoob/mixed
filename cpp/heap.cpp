#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
using namespace std;

#define swap(a,b) {int t; t=a; a=b; b=t;}

class heap  //assume binary min heap
{
public:
    heap(fstream&);
    heap(const int[], const int);
    ~heap();
    int get_root();
    int getHeight();    //notice that single-node tree has height 0
    void insert(const int);
    int delete_root();  //if no root to delete, return 1; Otherwise, return 0;
    void printOut();
private:
    vector <int> nodes;
    void HeapifyDown(const int);
};

int main()
{
    heap *myHeap;
    fstream FILE;
    FILE.open("heap_input.txt", ios::in);
    myHeap = new heap(FILE);
    FILE.close();

    myHeap->printOut();
    delete myHeap;
    system("pause");
    return 0;
}

heap::heap(fstream& inFILE) //call by reference
{
    int n;
    while(!inFILE.eof()){
        inFILE>>n;
        insert(n);
    }
}

heap::heap(const int data[], const int dataSize){
    int i;
    for(i=0; i<dataSize; i++)
        insert(data[i]);
}

heap::~heap(){
    nodes.clear();
}

int heap::get_root()
{
    return nodes.at(0); //.at() includes bounds checking
}

int heap::getHeight()
{
    if(nodes.size()==0)
        return -1;
    else
        return (int)log2(nodes.size());
}

void heap::insert(const int input){
    int parent, index;
    nodes.push_back(input);
    index = nodes.size()-1;
    parent = (index-1)/2;
    while(index && nodes.at(index)<nodes.at(parent)){
        swap(nodes.at(index), nodes.at(parent));
        index = parent;
        parent = (index-1)/2;
    }
}

int heap::delete_root()
{
    if(getHeight()==-1) //heap is empty, no loop to delete
        return 1;
    swap(nodes.at(0), nodes.back());
    nodes.pop_back();
    HeapifyDown(0);
    return 0;
}

void heap::HeapifyDown(const int root)   //root = root index of the subtree
{
    int left, right, key;
    if(root >= nodes.size())
        return;
    key = -1;
    left = 2*root+1;
    right = 2*root+2;
    if(left<=nodes.size()){    //if left subtree exists
        if(right<=nodes.size()){    //if right subtree exists
            if(nodes.at(left)<nodes.at(root) && nodes.at(left)<=nodes.at(right))    //if left is least
                key = left;
            else if(nodes.at(right)<nodes.at(root) && nodes.at(right)<=nodes.at(left))  //if right is least
                key = right;
        }
        else    //if right subtree does not exist
            if(nodes.at(left) < nodes.at(root))
                key = left;
    }
    if(key==-1) //if key unchanged
        return;
    else{
        swap(nodes.at(root), nodes.at(key));
        HeapifyDown(key);
        return;
    }
}

void heap::printOut(){
    vector <int>::iterator it;
    for(it=nodes.begin(); it!=nodes.end(); it++)
        cout<<*it<<' ';
    cout<<endl;
}