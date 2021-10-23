#include <iostream>
#include<list>
using namespace std;



int main()
{
    list <int> myList;
    int i,n,data;
    cout<<"number of elements:";
    cin>>n;
    for(i=0;i<n;i++){
        cout<<i<<"-th data"<<endl;
        cin>>data;
        myList.push_back(data);
    }
    return 0;
}