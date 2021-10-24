#include<iostream>
#include<fstream>
#include<list>
#include<iterator>
using namespace std;



int main()
{
    list <int> myList;
    list <int>::iterator it;
    ifstream file;
    int i,index,n,data,branch;
    file.open("init.txt");
    if(file.is_open()){
        file>>n;
        for(i=0;i<n;i++){
            file>>data;
            myList.push_back(data);
        }
    }
    file.close();

    do
    {
        cout<<"choose function: (1)insert_at (0)exit"<<endl<<":";
        cin>>branch;
        switch(branch){
            case 1:
                cout<<"insert at:";
                cin>>index;
                cout<<"insert data:";
                cin>>data;
                it = myList.begin();
                for(i=0;i<index;i++)
                    it++;
                myList.insert(it,data);
                break;
            case 0:
                break;
            default:
                cout<<"not matched option\n";
                break;
        }
    }while(branch);

    cout<<"myList:\n";
    for(it=myList.begin(); it!=myList.end(); ++it)
        cout<<*it<<"\t";
    cout<<endl;
    system("pause");
    return 0;
}