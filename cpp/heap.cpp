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
    heap(const int data[], const int dataSize);
    ~heap();
    int get_root();
    int getHeight();    //notice that single-node tree has height 0
    void insert(const int);
    int delete_at_root();  //if no root to delete, return 1; Otherwise, return 0;
    void printOut();
    void printOutDOT(fstream&);    //print out a DOT file
    void sort();    //after sort(), the data would be arranged as a sorted vector no longer a heap
private:
    vector <int> nodes;
    void heapifyDown(const int, const int);
};


int main()
{
    heap *myHeap;
    fstream file;
    file.open("int_input.txt", ios::in);
    myHeap = new heap(file);
    file.close();

    file.open("outGraph.dot", ios::out | ios::trunc);
    myHeap->printOutDOT(file);
    file.close();

    myHeap->sort();
    myHeap->printOut();
    delete myHeap;
    system("pause");
    return 0;
}

heap::heap(fstream& inFile) //call by reference
{
    int n;
    while(!inFile.eof()){
        inFile>>n;
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
    /*-------start heapifyUp-------*/
    index = nodes.size()-1;
    parent = (index-1)/2;
    while(index && nodes.at(index)<nodes.at(parent)){
        swap(nodes.at(index), nodes.at(parent));
        index = parent;
        parent = (index-1)/2;
    }
}

int heap::delete_at_root()
{
    if(nodes.empty()) //heap is empty, no loop to delete
        return 1;
    swap(nodes.at(0), nodes.back());
    nodes.pop_back();
    heapifyDown(0, nodes.size());
    return 0;
}

void heap::heapifyDown(const int root, const int length)
//root = root index of the subtree
//length is the logical end of the heap. in usual case, it is nodes.size(); in sort(), it works
{
    int left, right, key;
    if(root >= length)
        return;
    key = -1;
    left = 2*root+1;
    right = 2*root+2;
    if(left < length){    //if left subtree exists
        if(right < length){    //if right subtree exists
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
        heapifyDown(key, length);
        return;
    }
}

void heap::printOut(){
    vector <int>::iterator it;
    for(it=nodes.begin(); it!=nodes.end(); it++)
        cout<<*it<<' ';
    cout<<endl;
}

void heap::printOutDOT(fstream& outFile){
    int index, temp;
    outFile<<"digraph heap {\n";
    for(index=0,temp=0; temp<nodes.size(); index++){
        outFile<<'\t'<<nodes.at(index)<<" -> {";
        temp = 2*index+1;
        if(temp < nodes.size()){
            outFile<<nodes.at(temp);
            if(++temp < nodes.size())
                outFile<<' '<<nodes.at(temp);
        }
        outFile<<"};\n";
    }
    outFile<<"}";
}

void heap::sort(){
    int i;
    for(i=nodes.size(); i; i--){
        //cout<<get_root()<<' ';    //this line will print data from lowest to highest
        swap(nodes.at(0), nodes.at(i-1));
        heapifyDown(0, i-1);
    }
}