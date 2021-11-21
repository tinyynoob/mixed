#include<iostream>
#include<fstream>
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
    void update_balance_factor();
    bool isLeaf();
    int getHeight();
};

template <class T>
class AVL_tree
{
public:
    AVL_tree<T>();
    AVL_tree<int>(fstream&);
    ~AVL_tree<T>(); //developing
    bool insertNode(const T);
    bool deleteNode(const T); //developing
    bool search(const T);
private:
    AVL_node<T> *root;
    AVL_node<T>* findNode(const T);
    void rotateRight(AVL_node<T>*&);
    void rotateLeft(AVL_node<T>*&);
    void rotateLeftRight(AVL_node<T>*&);
    void rotateRightLeft(AVL_node<T>*&);
    void insertBalance(AVL_node<T>*, const T);
    void deleteBalance(AVL_node<T>*, const T);  //developing
    void _BSTdelete(AVL_node<T>*&);
};


int main()
{
    AVL_tree <int> *myAVL;
    fstream FILE;
    FILE.open("int_input.txt", ios::in);
    myAVL = new AVL_tree<int>(FILE);
    FILE.close();
    
    delete myAVL;
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
void AVL_node<T>::update_balance_factor(){
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

AVL_tree<int>::AVL_tree(fstream& inFILE){
    int n;
    while(!inFILE.eof()){
        inFILE>>n;
        insertNode(n);
    }
}

template <class T>
AVL_tree<T>::~AVL_tree(){
    AVL_node<T> *it, *temp;
    // while(1){
        
    // }
}

template <class T>
bool AVL_tree<T>::insertNode(const T input){
    AVL_node<T> *newNode, *it;
    newNode = new AVL_node<T>(input);
    if(!root) //empty tree
        root = newNode;
    
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

template <class T>
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

template <class T>
bool AVL_tree<T>::search(const T toFind){
    if(findNode(toFind))
        return true;
    return false;
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

    subtree->update_balance_factor();  //update
    oldLeftNode->left->update_balance_factor();
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

    subtree->update_balance_factor();  //update
    oldRightNode->right->update_balance_factor();
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
    subtree->right->update_balance_factor();
}

template <class T>
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

template <class T>
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

template <class T>
void AVL_tree<T>::deleteBalance(AVL_node<T>* grievingParent, const T deadData){
    AVL_node<T> *it;
    for(it=grievingParent; it; it=it->parent)
    {
        
    }
}

template <class T>
void AVL_tree<T>::_BSTdelete(AVL_node<T>*& target){     //for recursive call
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
