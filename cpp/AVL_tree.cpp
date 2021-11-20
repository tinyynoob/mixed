#include<iostream>
using namespace std;

#define max(a,b) (a>b?a:b)

template <class T>
class AVL_node
{
public:
    AVL_node<T>(T);
    T data;
    int balance_factor;     //defined by height of left subtree subtracting height of right subtree
    AVL_node<T> *parent;
    AVL_node<T> *left;
    AVL_node<T> *right;
    void compute_balance_factor();
    bool isLeaf();
    int getHeight();
};

template <class T>
class AVL_tree
{
public:
    AVL_tree<T>();
    ~AVL_tree<T>(); //developing
    bool insertNode(const T); //developing
    bool deleteNode(const T); //developing
private:
    AVL_node<T> *root;
    AVL_node<T>* findNode(const T);
    void rotateRight(AVL_node<T>*&);
    void rotateLeft(AVL_node<T>*&);
    void rotateLeftRight(AVL_node<T>*&);
    void rotateRightLeft(AVL_node<T>*&);
};


int main()
{
    AVL_tree <int> *myAVL;

    
    system("pause");
    return 0;
}


template <class T>
AVL_node<T>::AVL_node(T input){
    this->data = input;
    this->balance_factor = 0;
    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
}

template <class T>
void AVL_node<T>::compute_balance_factor(){
    balance_factor = left->getHeight() - right->getHeight();
}

template <class T>
bool AVL_node<T>::isLeaf(){
    if(left || right)
        return false;
    return true;
}

template <class T>
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

template <class T>
AVL_tree<T>::AVL_tree(){
    this->root = NULL;
}

template <class T>
AVL_tree<T>::~AVL_tree(){
    
}

template <class T>
bool AVL_tree<T>::insertNode(const T input){
    AVL_node<T> *newNode, *it, *temp;
    newNode = new AVL_node<T>(input);
    if(!root) //empty tree
        root = newNode;
    it = root;
    while(1){   //find a place to insert
        if(input < it->data){
            if(!it->left){
                it->left = newNode;
                it->balance_factor+= 1;
                break;
            }
            it = it->left;
        }
        else if(input > it->data){
            if(!it->right){
                it->right = newNode;
                it->balance_factor+= -1;
                break;
            }
            it = it->right;
        }
        else{      //duplicate node
            delete newNode;
            return false;
        }
    }

    /*--- check if unbalanced ---*/
    it = it->parent;
    it->compute_balance_factor();

    
}

template <class T>
bool AVL_tree<T>::deleteNode(const T input){
    
}

template <class T>
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

template <class T>
void AVL_tree<T>::rotateRight(AVL_node<T>*& subtree){
    AVL_node<T> *superior, *oldLeftNode;
    superior = subtree->parent;
    oldLeftNode = subtree->left;
    
    subtree->left = oldLeftNode->right;
    if(oldLeftNode->right)
        oldLeftNode->right->parent = subtree;

    oldLeftNode->right = subtree;
    subtree->parent = oldLeftNode;

    subtree->compute_balance_factor();  //update
    oldLeftNode->left->compute_balance_factor();
    oldLeftNode->parent = superior; //upward connection
    subtree = oldLeftNode;
}

template <class T>
void AVL_tree<T>::rotateLeft(AVL_node<T>*& subtree){
    AVL_node<T> *superior, *oldRightNode;
    superior = subtree->parent;
    oldRightNode = subtree->right;

    subtree->right = oldRightNode->left;
    if(oldRightNode->left)
        oldRightNode->left->parent = subtree;
    
    oldRightNode->left = subtree;
    subtree->parent = oldRightNode;

    subtree->compute_balance_factor();  //update
    oldRightNode->right->compute_balance_factor();
    oldRightNode->parent = superior;    //upward connection
    subtree = oldRightNode;
}

template <class T>
void AVL_tree<T>::rotateLeftRight(AVL_node<T>*& subtree){
    AVL_node<T> *oldLeftNode;
    subtree->left = oldLeftNode->right;
    oldLeftNode->right->parent = subtree;

    oldLeftNode->right = subtree->left->left;
    oldLeftNode->right->parent = oldLeftNode;

    subtree->left->left = oldLeftNode;
    oldLeftNode->parent = subtree->left;

    rotateRight(subtree);
    subtree->right->compute_balance_factor();
}

template <class T>
void AVL_tree<T>::rotateRightLeft(AVL_node<T>*& subtree){
    AVL_node<T> *oldRightNode;
    subtree->right = oldRightNode->left;
    oldRightNode->left->parent = subtree;

    oldRightNode->left = subtree->right0>right;
    oldRightNode->left->parent = oldRightNode;

    subtree->right->right = oldRightNode;
    oldRightNode->parent = subtree->right;

    rotateLeft(subtree);
    subtree->left->compute_balance_factor();
}
