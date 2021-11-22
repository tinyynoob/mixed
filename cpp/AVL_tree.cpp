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
private:
    /* all functions starting with '_' is for recursive call */
    AVL_node<T> *root;
    AVL_node<T>* findNode(const T);
    void rotateRight(AVL_node<T>*&);
    void rotateLeft(AVL_node<T>*&);
    void rotateLeftRight(AVL_node<T>*&);
    void rotateRightLeft(AVL_node<T>*&);
    void insertBalance(AVL_node<T>*, const T);
    void deleteBalance(AVL_node<T>*, const T);  //developing
    void _BSTdelete(AVL_node<T>*&);
    void _clear(AVL_node<T>*);  //this function will recursively destruct the whole tree
    void _printOutDOT(fstream&, AVL_node<T>*);
};


int main()
{
    AVL_tree <int> *myAVL;
    fstream file;
    // file.open("int_input.txt", ios::in);
    // myAVL = new AVL_tree<int>(file);
    // file.close();
    myAVL = new AVL_tree<int>();
    myAVL->insertNode(3);
    myAVL->insertNode(4);

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
    balance_factor = left->getHeight() - right->getHeight();
}

template <typename T>
bool AVL_node<T>::isLeaf(){
    if(left || right)
        return false;
    return true;
}

template <typename T>
int AVL_node<T>::getHeight(){
    if(this->left && this->right){
        int a, b;
        a = this->left->getHeight();
        b = this->right->getHeight();
        return max(a,b)+1;
    }
    else if(this->left)
        return this->left->getHeight()+1;
    else if(this->right)
        return this->right->getHeight()+1;
    else
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
        cout<<typeid(T).name()<<endl;
        if(!insertNode(n))
            cerr<<"insert error"<<endl;
    }
}

template <typename T>
AVL_tree<T>::~AVL_tree(){
    _clear(root);
}

template <typename T>
bool AVL_tree<T>::insertNode(const T input){
    AVL_node<T> *newNode, *it;
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
                insertBalance(it, input);
                break;
            }
            it = it->left;
        }
        else if(input > it->data){
            if(!it->right){     //the position is found
                it->right = newNode;
                newNode->parent = it;
                insertBalance(it, input);
                break;
            }
            it = it->right;
        }
        else{      //duplicate node
            delete newNode;
            return false;
        }
    }
    return true;
}

template <typename T>
bool AVL_tree<T>::deleteNode(const T toDelete){
    AVL_node<T> *target, *temp;
    target = findNode(toDelete);
    if(!target) //there is no the node
        return false;
    temp = target->parent;
    if(!temp)  //if delete at root
        _BSTdelete(root);
    else if(toDelete < temp->data)
        _BSTdelete(temp->left);
    else if(toDelete > temp->data)
        _BSTdelete(temp->right);

    //developing    //???
    if(temp)
        deleteBalance(temp, toDelete);
    else
        deleteBalance(root, toDelete);
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
void AVL_tree<T>::rotateRight(AVL_node<T>*& subtree){
    AVL_node<T> *superior, *oldLeftNode;
    superior = subtree->parent;
    oldLeftNode = subtree->left;
    
    subtree->left = oldLeftNode->right;
    if(oldLeftNode->right)
        oldLeftNode->right->parent = subtree;

    oldLeftNode->right = subtree;
    subtree->parent = oldLeftNode;

    subtree->update_balance_factor();  //update
    oldLeftNode->left->update_balance_factor();
    oldLeftNode->parent = superior; //upward connection
    subtree = oldLeftNode;
}

template <typename T>
void AVL_tree<T>::rotateLeft(AVL_node<T>*& subtree){
    AVL_node<T> *superior, *oldRightNode;
    superior = subtree->parent;
    oldRightNode = subtree->right;

    subtree->right = oldRightNode->left;
    if(oldRightNode->left)
        oldRightNode->left->parent = subtree;
    
    oldRightNode->left = subtree;
    subtree->parent = oldRightNode;

    subtree->update_balance_factor();  //update
    oldRightNode->right->update_balance_factor();
    oldRightNode->parent = superior;    //upward connection
    subtree = oldRightNode;
}

template <typename T>
void AVL_tree<T>::rotateLeftRight(AVL_node<T>*& subtree){
    AVL_node<T> *oldLeftNode;
    subtree->left = oldLeftNode->right;
    oldLeftNode->right->parent = subtree;

    oldLeftNode->right = subtree->left->left;
    oldLeftNode->right->parent = oldLeftNode;

    subtree->left->left = oldLeftNode;
    oldLeftNode->parent = subtree->left;

    rotateRight(subtree);
    subtree->right->update_balance_factor();
}

template <typename T>
void AVL_tree<T>::rotateRightLeft(AVL_node<T>*& subtree){
    AVL_node<T> *oldRightNode;
    subtree->right = oldRightNode->left;
    oldRightNode->left->parent = subtree;

    oldRightNode->left = subtree->right->right;
    oldRightNode->left->parent = oldRightNode;

    subtree->right->right = oldRightNode;
    oldRightNode->parent = subtree->right;

    rotateLeft(subtree);
    subtree->left->update_balance_factor();
}

template <typename T>
void AVL_tree<T>::insertBalance(AVL_node<T>* noviceParent, const T newData){
    AVL_node<T> *it;
    for(it=noviceParent; it; it=it->parent)
    {
        if(newData < it->data){  //if add happened at left
            it->balance_factor++;
            if(it->balance_factor == 2){
                if(it->left->balance_factor == 1){
                    if(!it->parent)
                        rotateRight(root);
                    else if(it->data < it->parent->data)
                        rotateRight(it->parent->left);
                    else if(it->data > it->parent->data)
                        rotateRight(it->parent->right);
                }
                else if(it->left->balance_factor == -1){
                    if(!it->parent)
                        rotateLeftRight(root);
                    else if(it->data < it->parent->data)
                        rotateLeftRight(it->parent->left);
                    else if(it->data > it->parent->data)
                        rotateLeftRight(it->parent->right);
                }
                break;
            }
        }
        else{        //if add happened at right
            it->balance_factor--;
            if(it->balance_factor == -2){
                if(it->right->balance_factor == -1){
                    if(!it->parent)
                        rotateLeft(root);
                    else if(it->data < it->parent->data)
                        rotateLeft(it->parent->left);
                    else if(it->data > it->parent->data)
                        rotateLeft(it->parent->right);
                }
                else if(it->right->balance_factor == 1){
                    if(!it->parent)
                        rotateRightLeft(root);
                    else if(it->data < it->parent->data)
                        rotateRightLeft(it->parent->left);
                    else if(it->data > it->parent->data)
                        rotateRightLeft(it->parent->right);
                }
                break;
            }
        }
    }
}

template <typename T>
void AVL_tree<T>::deleteBalance(AVL_node<T>* grievingParent, const T deadData){
    AVL_node<T> *it;
    for(it=grievingParent; it; it=it->parent)
    {
        
    }
}

template <typename T>
void AVL_tree<T>::_BSTdelete(AVL_node<T>*& target){
/*------- kill the node target points to --------*/
    AVL_node<T> *it;
    if(target->left && target->right){  //if have two childs
        if(!target->right->left){   //if the right subtree has no left child
            target->data = target->right->data;
            _BSTdelete(target->right);
        }
        else{
            for(it=target->right; it->left; it=it->left)   //find leftmost node at right subtree
                ;
            target->data = it->left->data;
            _BSTdelete(it->left);
        }
    }
    else if(target->left){  //there is only left subtree
        it = target;
        target->left->parent = target->parent;
        target = target->left;
        delete it;
    }
    else if(target->right){ //there is only right subtree
        it = target;
        target->right->parent = target->parent;
        target = target->right;
        delete it;
    }
    else{   //no subtree
        delete target;
        target = NULL;
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
