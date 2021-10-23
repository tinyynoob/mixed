#include <iostream>
#include <list>
#include<iterator>
using namespace std;



int main()
{
    list <int> myList;
    list <int>::iterator it;
    int i,n,data;
    cout<<"number of elements:";
    cin>>n;
    for(i=0;i<n;i++){
        cout<<i<<"-th data"<<endl;
        cin>>data;
        myList.push_back(data);
    }
    cout<<"insert at:";
    cin>>n;
    cout<<"insert data:";
    cin>>data;
    it = myList.begin();
    for(i=0;i<n;i++)
        ++it;
    myList.insert(it,data);
    
    for(it=myList.begin(); it!=myList.end(); ++it)
        cout<<*it;
    cout<<endl;
    system("pause");
    return 0;
}