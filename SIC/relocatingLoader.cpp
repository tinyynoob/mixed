#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

#define MEMORYSIZE 32768

/*
status code descriptions:
    0: all is well
    1: could not open input file
    2: some input failed
    3: unknown record type
    4: could not open DEVF2
*/
class relocatingLoader
{
public:
    relocatingLoader(string);   //input file name
    ~relocatingLoader();
    bool load();
    bool generate_DEVF2();
    int getStatus(){ return status;};
private:
    string memory;  //pseudo SIC memory
    int status;
    vector<int> starting_address_of_memory_blocks;  //the memory block: [starting, ending)
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
    cout<<"end load()"<<endl;   //for debug
    RL->generate_DEVF2();
    cout<< "status code: "<<RL->getStatus()<<endl;
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

    inFile.open(inFileName, ios::in);
    if(!inFile.is_open()){
        status = 1;
        return false;
    }
    record.reserve(100);
    /*--- process first line ---*/
    if(!getline(inFile, record)){
        status = 2;
        inFile.close();
        return false;
    }
    name = record.substr(1,6);
    starting_address = stoi(record.substr(7,6), nullptr, 16);
    inputLength = stoi(record.substr(13,6), nullptr, 16);
    /*--- end process first line ---*/

    memory.resize(MEMORYSIZE, '.');  //unsure

    while(getline(inFile, record)){
        recordType = record.at(0);
        if(recordType == 'T')
            processTextRecord(record);
        else if(recordType == 'M')
            processModificationRecord(record);
        else if(recordType == 'E')
            break;
        else{
            status = 3;     //unknown record type
            inFile.close();
            return false;
        }
    }
    
    //last line of memory bytes
    inFile.close();
    return true;
}

bool relocatingLoader::generate_DEVF2(){
    int counter;
    string::iterator it;
    fstream outFile;
    outFile.open("DEVF2", ios::out | ios::trunc);
    if(!outFile.is_open()){
        status = 4;
        return false;
    }
    outFile<< 'I' << name << starting_address <<endl;   //<< size and transfer address //int to hex string
    
    counter = 0;
    for(it=memory.begin(); it!=memory.end(); it++){
        outFile<<*it;
        counter++;
        if(counter%64 == 0){
            outFile<<endl;
            counter = 0;
        }
        else if(counter%8 == 0)
            outFile<<' ';
    }
    //output last line
    outFile.close();
    return true;
}

void relocatingLoader::processTextRecord(string record){
    int i, hexIndex, flag, start, bytesNum;
    start = stoi(record.substr(1,6), nullptr, 16);
    bytesNum = stoi(record.substr(7,2), nullptr, 16);
    cout<< "start: "<<start<<" bytesNum: "<<bytesNum<<endl;     //for debug

    //if it is a new block, flag=0; else, flag=1;
    flag = 0;
    for(i=0; i<starting_address_of_memory_blocks.size(); i++){
        if(start == ending_address_of_memory_blocks.at(i)){
            flag = 1;
            break;
        }
    }
    if(flag)
        ending_address_of_memory_blocks.at(i)+= bytesNum;
    else{   //this is a new memory block
        starting_address_of_memory_blocks.push_back(start);
        ending_address_of_memory_blocks.push_back(start+bytesNum);
    }
    
    for(i=0; i<bytesNum; i++){
        hexIndex = 2*i;
        memory[start+hexIndex] = record.at(9+hexIndex);
        hexIndex++;
        memory[start+hexIndex] = record.at(9+hexIndex);
    }
    cout<<memory.at(30)<<memory.at(31)<<endl;  //for debug
}

void relocatingLoader::processModificationRecord(string record){
    ;
}

// template <typename T >
// string int_to_hex(T inputData)
// {
//     stringstream strstream;
//     stream<< "0x"<< std::setfill ('0') << std::setw(sizeof(T)*2)<< std::hex << inputData;
//     return stream.str();
// }
