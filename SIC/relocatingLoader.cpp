#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<charconv>
using namespace std;

/*
status code descriptions:
    0: all is well
    1: could not open input file
    2: some input failed
*/
class relocatingLoader
{
public:
    relocatingLoader(string);   //input file name
    bool load();
    bool generate_devf2();
    int getStatus(){ return status;};
private:
    string memory;  //pseudo SIC memory
    int status;
    vector<int> starting_address_of_memory_blocks;  //the interval: [)
    vector<int> ending_address_of_memory_blocks;
    int starting_address;   //should be 0
    int inputLength;
    string name;
    string inFileName;
    void processTextRecord(string);   //process a line
    void processModificationRecord(string);   //process a line
};

int main()
{
    relocatingLoader *RL;
    RL = new relocatingLoader("objectCode.OBJ");
    RL->load();
    delete RL;
    system("pause");
    return 0;
}

relocatingLoader::relocatingLoader(string inFileName){
    status = 0;
    this->inFileName = inFileName;
}

relocatingLoader::~relocatingLoader(){
    starting_address_of_memory_blocks.clear();
    ending_address_of_memory_blocks.clear();
}

bool relocatingLoader::load(){
    fstream inFile;
    string record;
    char recordType;
    int i;
    
    inFile.open(inFileName, ios::in);
    if(!inFile.is_open()){
        status = 1;
        return false;
    }

    /*--- process first line ---*/
    if(!getline(inFile, record)){
        status = 2;
        return false;
    }
    name.assign(record, 2, 6);
    from_chars(record.c_str()+7, record.c_str()+13, starting_address, 16);  //the interval: [)
    from_chars(record.c_str()+13, record.c_str()+19, inputLength, 16);  //wrong
    /*--- end process first line ---*/

    memory.resize(32768, '.');  //unsure
    while(getline(inFile, record)){
        recordType = record.at(0);
        if(recordType == 'T')
            processTextRecord(record);
        else if(recordType == 'M')
            processModificationRecord(record);
        else if(recordType == 'E')
            break;
        else
            ;   //what to do?
    }
    
    //last line of memory bytes
    return true;
}

void relocatingLoader::processTextRecord(string record){
    int i, j, flag, start, wordsNum;
    from_chars(record.c_str()+1, record.c_str()+7, start, 16);
    from_chars(record.c_str()+7, record.c_str()+9, wordsNum, 16);

    flag = 0;
    for(i=0; i<starting_address_of_memory_blocks.size(); i++){
        if(start == ending_address_of_memory_blocks[i]){
            flag = 1;
            break;
        }
    }
    if(flag)
        ending_address_of_memory_blocks.at(i)+= wordsNum;
    else{   //this is a new memory block
        starting_address_of_memory_blocks.push_back(start);
        ending_address_of_memory_blocks.push_back(start+wordsNum);
    }
    
    for(i=0; i<wordsNum; i++){
        j = 2*i;
        memory[start+j] = record[9+j];
        memory[start+j+1] = record[9+j+1];
    }
}

