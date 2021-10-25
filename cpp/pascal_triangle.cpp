#include<iostream>
#include<queue>
using namespace std;

int main()
{
    int n, i, j;
    queue <int> que, nextQue;
    cout<<"the height of the Pascal triangle:";
    cin>>n;
    if(n<=0)
        cout<<"error input";
    else if(n==1)
        cout<<1; 
    else{    
        cout<<1<<endl; 
        que.push(1);
        que.push(1);
        for(i=1; i<n-1; i++, que=nextQue){     //floor
            while(!nextQue.empty())     //clear the old queue
                nextQue.pop();
            nextQue.push(que.front());
            cout<<que.front()<<" ";
            for(j=0;j<i;j++){       //room
                nextQue.push(que.front());  //up left number
                que.pop();  //throw up left
                nextQue.back()+= que.front();   //up right number
                cout<<que.front()<<" "; //print up right
            }
            nextQue.push(que.front());
            que.pop();
            cout<<endl;
        }
        while(!que.empty()){    //the last floor
            cout<<que.front()<<" ";
            que.pop();
        }
    }
    cout<<endl;

    system("pause");
    return 0;
}