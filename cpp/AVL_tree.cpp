#include<iostream>
#include<fstream>
#include<typeinfo>
using namespace std;

#define max(a,b) (a>b?a:b)

template <typename T>
class AVL_node
{
public:
    AVL_node<T>(T);
    T data;
    int balance_factor;     //defined by height of left subtree subtracting height of right subtree
    AVL_node<T> *parent;
    AVL_node<T> *left;
    AVL_node<T> *right;
    void update_balance_factor();
    bool isLeaf();
    int getHeight();
};

template <typename T>
class AVL_tree
{
public:
    AVL_tree<T>();
    AVL_tree(fstream&); //currently only supports int type
    ~AVL_tree<T>();
    bool insertNode(const T);
    bool deleteNode(const T); //developing
    bool search(const T);
    void printOutDOT(fstream&);
private:    /* all functions starting with '_' are for recursive call */
    AVL_node<T> *root;
    AVL_node<T>* findNode(const T);
    AVL_node<T>* rotateRight(AVL_node<T>*);
    AVL_node<T>* rotateLeft(AVL_node<T>*);
    AVL_node<T>* rotateLeftRight(AVL_node<T>*);
    AVL_node<T>* rotateRightLeft(AVL_node<T>*);
    void insertBalance(AVL_node<T>*);   //including update balance factor
    void deleteBalance(AVL_node<T>*);  //developing
    AVL_node<T>* _BSTdelete(AVL_node<T>*, AVL_node<T>*&);  //developing
    void _clear(AVL_node<T>*);  //this function will recursively destruct the whole tree
    void _printOutDOT(fstream&, AVL_node<T>*);
};


int main()
{
    AVL_tree <int> *myAVL;
    fstream file;
    file.open("int_input.txt", ios::in);
    myAVL = new AVL_tree<int>(file);
    file.close();

    file.open("outGraph.dot", ios::out | ios::trunc);
    myAVL->printOutDOT(file);
    file.close();
    delete myAVL;
    system("pause");
    return 0;
}


template <typename T>
AVL_node<T>::AVL_node(T input){
    this->data = input;
    this->balance_factor = 0;
    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
}

template <typename T>
void AVL_node<T>::update_balance_factor(){
    //cout<<"entering update_balance_factor() , I am "<<this->data<<endl;    //for debug
    //cout<<"my left is "<<this->left->data<<", my right is "<<this->right->data<<endl;   //for debug
    if(this->left && this->right)
        this->balance_factor = this->left->getHeight() - this->right->getHeight();
    else if(this->left)
        this->balance_factor = this->left->getHeight() - (-1);  //note that empty tree has length -1
    else if(this->right)
        this->balance_factor = (-1) - this->right->getHeight();
    else
        this->balance_factor = 0;
}

template <typename T>
bool AVL_node<T>::isLeaf(){
    if(left || right)
        return false;
    return true;
}

template <typename T>
int AVL_node<T>::getHeight(){
    //cout<<"entering getHeight() , I am "<<this->data<<endl;    //for debug
    if(this->left && this->right){
        int a, b;
        a = this->left->getHeight();
        b = this->right->getHeight();
        return max(a,b)+1;
    }
    else if(this->left)     //there is only left subtree
        return this->left->getHeight()+1;
    else if(this->right)    //there is only right subtree
        return this->right->getHeight()+1;
    else    //it is leaf
        return 0;
}


template <typename T>
AVL_tree<T>::AVL_tree(){
    this->root = NULL;
}

template <typename T>
AVL_tree<T>::AVL_tree(fstream& inFile){
    int n;
    this->root = NULL;
    if(typeid(T) != typeid(int)){
        cerr<<"type error"<<endl;
        return;
    }
    while(!inFile.eof()){
        inFile>>n;
        //cout<<typeid(T).name()<<endl; //for debug
        if(!insertNode(n))
            cout<< "insert failed: duplicate data " << n <<endl;
    }
}

template <typename T>
AVL_tree<T>::~AVL_tree(){
    _clear(root);
}

template <typename T>
bool AVL_tree<T>::insertNode(const T input){
    AVL_node<T> *newNode, *it;
    //cout<<"trying to insert: "<<input<<endl;    //for debug
    newNode = new AVL_node<T>(input);
    if(!root){ //empty tree
        root = newNode;
        return true;
    }
    
    it = root;
    while(1)    //find a position to insert
    {
        if(input < it->data){
            if(!it->left){      //the position is found
                it->left = newNode;
                newNode->parent = it;
                insertBalance(it);  //update balance factor step by step to root and check if any rotation needed
                break;
            }
            it = it->left;
        }
        else if(input > it->data){
            if(!it->right){     //the position is found
                it->right = newNode;
                newNode->parent = it;
                insertBalance(it);  //update balance factor step by step to root and check if any rotation needed
                break;
            }
            it = it->right;
        }
        else{      //duplicate node
            delete newNode;
            //cout<<"duplicate data: "<<input<<endl;
            return false;
        }
    }
    return true;
}

template <typename T>
bool AVL_tree<T>::deleteNode(const T toDelete){
    AVL_node<T> *target, *temp, *deepestGrievingParent;
    target = findNode(toDelete);
    if(!target) //there is no the node
        return false;

    deepestGrievingParent = NULL;
    temp = target->parent;
    if(!temp)  //if delete at root
        root = _BSTdelete(target, deepestGrievingParent);
    else if(toDelete < temp->data)  //if delete at left
        temp->left = _BSTdelete(target, deepestGrievingParent);
    else if(toDelete > temp->data)  //if delete at right
        temp->right = _BSTdelete(target, deepestGrievingParent); 
    
    if(deepestGrievingParent)
        deleteBalance(deepestGrievingParent);   //including update balance factor
    //otherwise, the tree is now empty
    return true;
}

template <typename T>
bool AVL_tree<T>::search(const T toFind){
    if(findNode(toFind))
        return true;
    return false;
}

template <typename T>
void AVL_tree<T>::printOutDOT(fstream& outFile){
    outFile<<"digraph AVL_tree {\n";
    _printOutDOT(outFile, root);
    outFile<<"}";
}

template <typename T>
AVL_node<T>* AVL_tree<T>::findNode(const T toFind){
    AVL_node<T> *it;
    it = root;
    while(it){
        if(toFind < it->data)
            it = it->left;
        else if(toFind > it->data)
            it = it->right;
        else
            return it;
    }
    return NULL;    //cant find
}

template <typename T>
AVL_node<T>* AVL_tree<T>::rotateRight(AVL_node<T>* subtree){
    AVL_node<T> *oldLeftNode;
    oldLeftNode = subtree->left;
    
    subtree->left = oldLeftNode->right;
    if(oldLeftNode->right)
        oldLeftNode->right->parent = subtree;

    oldLeftNode->parent = subtree->parent;      //upward connection
    oldLeftNode->right = subtree;
    subtree->parent = oldLeftNode;
    return oldLeftNode;     //return the new root of the subtree
}

template <typename T>
AVL_node<T>* AVL_tree<T>::rotateLeft(AVL_node<T>* subtree){
    AVL_node<T> *oldRightNode;
    oldRightNode = subtree->right;

    subtree->right = oldRightNode->left;
    if(oldRightNode->left)
        oldRightNode->left->parent = subtree;
    
    oldRightNode->parent = subtree->parent;     //upward connection
    oldRightNode->left = subtree;
    subtree->parent = oldRightNode;
    return oldRightNode;    //return the new root of the subtree
}

template <typename T>
AVL_node<T>* AVL_tree<T>::rotateLeftRight(AVL_node<T>* subtree){
    AVL_node<T> *oldLeftNode;
    oldLeftNode = subtree->left;

    subtree->left = oldLeftNode->right;
    oldLeftNode->right->parent = subtree;

    oldLeftNode->right = subtree->left->left;
    if(subtree->left->left)
        subtree->left->left->parent = oldLeftNode;
    subtree->left->left = oldLeftNode;
    oldLeftNode->parent = subtree->left;

    return rotateRight(subtree);
}

template <typename T>
AVL_node<T>* AVL_tree<T>::rotateRightLeft(AVL_node<T>* subtree){
    AVL_node<T> *oldRightNode;
    oldRightNode = subtree->right;

    subtree->right = oldRightNode->left;
    oldRightNode->left->parent = subtree;

    oldRightNode->left = subtree->right->right;
    if(subtree->right->right)
        subtree->right->right->parent = oldRightNode;
    subtree->right->right = oldRightNode;
    oldRightNode->parent = subtree->right;

    return rotateLeft(subtree);
}

template <typename T>
void AVL_tree<T>::insertBalance(AVL_node<T>* noviceParent){
    AVL_node<T> *it, *newRootOfRotatedSubtree, *temp;

    for(it=noviceParent; it; it=it->parent)
    {
        it->update_balance_factor();
        if(it->balance_factor == 2){
            if(it->left->balance_factor == 1){
                //cout<<"trying to rotateRight the tree "<<it->data<<endl; //for debug
                temp = it->parent;
                newRootOfRotatedSubtree = rotateRight(it);
                newRootOfRotatedSubtree->update_balance_factor();
                newRootOfRotatedSubtree->right->update_balance_factor();
            }
            else if(it->left->balance_factor == -1){
                //cout<<"trying to rotateLeftRight the tree "<<it->data<<endl; //for debug
                temp = it->parent;
                newRootOfRotatedSubtree = rotateLeftRight(it);
                newRootOfRotatedSubtree->update_balance_factor();
                newRootOfRotatedSubtree->left->update_balance_factor();
                newRootOfRotatedSubtree->right->update_balance_factor();
            }
            else    //impossible
                ;
        }
        else if(it->balance_factor == -2){
            if(it->right->balance_factor == -1){
                //cout<<"trying to rotateLeft the tree "<<it->data<<endl; //for debug
                temp = it->parent;
                newRootOfRotatedSubtree = rotateLeft(it);
                newRootOfRotatedSubtree->update_balance_factor();
                newRootOfRotatedSubtree->left->update_balance_factor();
            }
            else if(it->right->balance_factor == 1){
                //cout<<"trying to rotateRightLeft the tree "<<it->data<<endl; //for debug
                temp = it->parent;
                newRootOfRotatedSubtree = rotateRightLeft(it);
                newRootOfRotatedSubtree->update_balance_factor();
                newRootOfRotatedSubtree->left->update_balance_factor();
                newRootOfRotatedSubtree->right->update_balance_factor();
            }
            else    //impossible
                ;
        }
        else
            continue;

        //if there is any rotation
        if(!temp)   //if that is root being rotated
            root = newRootOfRotatedSubtree;
        else if(it->data < temp->data)   //rotation happened at left
            temp->left = newRootOfRotatedSubtree;
        else if(it->data > temp->data)   //rotation happened at right
            temp->right = newRootOfRotatedSubtree;
        break;
    }
}

template <typename T>
void AVL_tree<T>::deleteBalance(AVL_node<T>* grievingParent){
    AVL_node<T> *it, *newRootOfRotatedSubtree;

    for(it=grievingParent; it; it=it->parent)   //traverse upward and update each balance factor
    {
        it->update_balance_factor();
        if(it->balance_factor == 2){
            
        }
        else if(it->balance_factor == -2){
            
        }

    }
}

template <typename T>
AVL_node<T>* AVL_tree<T>::_BSTdelete(AVL_node<T>* target, AVL_node<T>*& deepestGrievingParent){
/*------- kill the node pointed by target and return new root of this subtree --------*/
    AVL_node<T> *it;
    if(target->left && target->right){  //if have two childs, replace target->data by the data in specified node, and delete this node
        if(!target->right->left){   //if the right subtree has no left child
            target->data = target->right->data;
            target->right = _BSTdelete(target->right, deepestGrievingParent);
            //forward the return from deeper recursion
            return target;  //unchanged since data replacement does not kill target node
        }
        else{
            for(it=target->right; it->left; it=it->left)   //find leftmost node in right subtree
                ;
            it = it->parent;    //back one step
            target->data = it->left->data;
            it->left = _BSTdelete(it->left, deepestGrievingParent);
            //forward the return from deeper recursion
            return target;  //unchanged since data replacement does not kill target node
        }
    }
    else if(target->left){  //if there is only left subtree, delete and reconnect the nodes (no data replacement)
        it = target->left;  //*it will be the new root of this subtree
        it->parent = target->parent;  //upward connection
        deepestGrievingParent = target->parent;
        delete target;
        return it;
    }
    else if(target->right){ //if there is only right subtree, delete and reconnect the nodes (no data replacement)
        it = target->right; //*it will be the new root of this subtree
        it->parent = target->parent; //upward connection
        deepestGrievingParent = target->parent;
        delete target;
        return it;
    }
    else{   //no subtree
        deepestGrievingParent = target->parent;
        delete target;
        return NULL;
    }
}

template <typename T>
void AVL_tree<T>::_clear(AVL_node<T>* subtree){
    if(subtree->left)
        _clear(subtree->left);
    if(subtree->right)
        _clear(subtree->right);
    delete subtree;
}

template <typename T>
void AVL_tree<T>::_printOutDOT(fstream& outFile, AVL_node<T>* subtree){
    //cout<<"entering _printOutDOT(), I am "<<subtree->data<<endl;    //for debug
    outFile<< '\t' << subtree->data << " -> {";
    if(subtree->left)
        outFile<< subtree->left->data << ' ';
    if(subtree->right)
        outFile<< subtree->right->data;
    outFile<< "};\n";

    if(subtree->left)
        _printOutDOT(outFile, subtree->left);
    if(subtree->right)
        _printOutDOT(outFile, subtree->right);
}
