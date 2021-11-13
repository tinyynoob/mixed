#include<iostream>
#include<string>
using namespace std;

int main()
{
    int counter;
    char current;
    string input, output;
    string::iterator it_in;
    input = "0001110000110";

    it_in = input.begin();
    while(it_in!=input.end()){
        current = *it_in;
        counter = 1;
        it_in++;
        while(it_in!=input.end() && *it_in==current){   //process repeated data
            counter++;
            it_in++;
        }
        output+= to_string(counter);
        output.push_back(current);
    }
    cout<<output<<endl;
    system("pause");
    return 0;
}