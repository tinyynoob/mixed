#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<random>
#include<chrono>
using namespace std;

#define MEMORYSIZE 10240*2  //10240 bytes, 10240*2 hex digits
#define BOOTSIZE 256*2      //assume that the first 256 bytes will be occupied by boot ROM and BIOS

class relocatingLoader
{
public:
    relocatingLoader(string);   //name of the input object program as parameter
    bool load();
    bool generate_DEVF2();
    int statusLog();
private:
    string memory;  //pseudo SIC memory
    int status;     //status code
    vector<int> starting_address_of_memory_blocks;  //the memory block: [starting, ending)
    vector<int> ending_address_of_memory_blocks;
    int loading_offset;
    int starting_address;
    int transfer_address;
    int objLength;
    string program_name;
    string inFileName;
    void paddingMemory();   //to simulate the memory space
    void random_generate_loading_offset();
    void processTextRecord(string);   //process one line
    void processModificationRecord(string);   //process one line
};

template <typename T>   //this function is imported from https://stackoverflow.com/questions/5100718/integer-to-hex-string-in-c
string int2hexStr(T w, size_t hex_len = sizeof(T)<<1){
    static const char* digits = "0123456789ABCDEF";
    string rc(hex_len,'0');
    for (size_t i=0, j=(hex_len-1)*4 ; i<hex_len; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
}

int main()
{
    relocatingLoader *RL;
    RL = new relocatingLoader("SRCFILE.OBJ");
    if(RL->load()){
        if(RL->generate_DEVF2())
            ;
    }
    RL->statusLog();
    delete RL;
    return 0;
}

relocatingLoader::relocatingLoader(string inFileName){
    status = 0;
    this->inFileName = inFileName;
    memory.resize(MEMORYSIZE);
    paddingMemory();    //memory simulation
}

int relocatingLoader::statusLog(){
    if(status == 0)
        cout<<"Loading successed"<<endl;
    else if(status == 1)
        cout<<"Could not open input object program"<<endl;
    else if(status == 2)
        cout<<"Input failed"<<endl;
    else if(status == 3)
        cout<<"Unknown record type"<<endl;
    else if(status == 4)
        cout<<"Could not open DEVF2"<<endl;
    return status;
}

bool relocatingLoader::load(){
    fstream inFile;
    string record;

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
    program_name = record.substr(1,6);
    starting_address = stoi(record.substr(7,6), nullptr, 16);
    objLength = stoi(record.substr(13,6), nullptr, 16);
    /*--- end process first line ---*/

    if(starting_address)    //check out whether a relocation is needed
        loading_offset = 0;
    else
        random_generate_loading_offset();

    char recordType;
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
    transfer_address = stoi(record.substr(1,6), nullptr, 16);

    inFile.close();
    return true;
}

bool relocatingLoader::generate_DEVF2(){
    fstream outFile;
    outFile.open("DEVF2", ios::out | ios::trunc);
    if(!outFile.is_open()){
        status = 4;
        return false;
    }
    int output_starting_address = (starting_address_of_memory_blocks.at(0)/32)*32; //this is byte
    int size = ending_address_of_memory_blocks.back() - output_starting_address;
    int output_transfer_address = transfer_address + loading_offset;
    outFile<< 'I' << program_name << int2hexStr<int>(output_starting_address, 6)
        << int2hexStr<int>(size, 6) << int2hexStr<int>(output_transfer_address, 6) <<endl;
    
    int counter = 0;
    for(int i=output_starting_address; i<output_starting_address+size; ++i){
        outFile<<memory[i*2];
        outFile<<memory[i*2+1];
        counter++;
        if(counter%32 == 0){
            outFile<<endl;
            counter = 0;
        }
    }
    //output last line
    outFile.close();
    return true;
}

void relocatingLoader::paddingMemory(){
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> UNI(0,15);
    const char* hex = "0123456789ABCDEF";
    for(int i=0; i<MEMORYSIZE; ++i)
        memory[i] = hex[UNI(generator)];
}

void relocatingLoader::random_generate_loading_offset(){
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    //cout<<"value of generator is "<<generator<<endl;    //for test
    uniform_int_distribution<int> UNI(BOOTSIZE/2+1, MEMORYSIZE/2-objLength);
    loading_offset = UNI(generator);
}
 
void relocatingLoader::processTextRecord(string record){
    int i, flag, start, bytesNum;
    start = stoi(record.substr(1,6), nullptr, 16);
    bytesNum = stoi(record.substr(7,2), nullptr, 16);
    //cout<< "start: "<<start<<" bytesNum: "<<bytesNum<<endl;     //for debug

    //if it is a new block, flag=0; else, flag=1;
    flag = 0;
    for(i=0; i<starting_address_of_memory_blocks.size(); i++){
        if(loading_offset+start == ending_address_of_memory_blocks.at(i)){
            flag = 1;
            break;
        }
    }
    if(flag)
        ending_address_of_memory_blocks.at(i)+= bytesNum;
    else{   //this is a new memory block
        starting_address_of_memory_blocks.push_back(loading_offset+start);
        ending_address_of_memory_blocks.push_back(loading_offset+start+bytesNum);
    }
    
    for(i=0; i<bytesNum; i++){
        /*notice that unit of start, bytesNum and addresses is byte, however unit of memory and record is half-byte*/
        memory[2*(loading_offset+start+i)] = record.at(9+i*2);
        memory[2*(loading_offset+start+i)+1] = record.at(10+i*2);
    }
}

void relocatingLoader::processModificationRecord(string record){
    int i, j, location, hexLength, targetValue;
    string str;
    location = stoi(record.substr(1,6), nullptr, 16);   //unit: byte
    hexLength = stoi(record.substr(7,2), nullptr, 16);
    location = 2*(loading_offset+location);   //index of hex digit in memory
    str = memory.substr(location+(hexLength&1), hexLength);
    //cout<<str<<endl;  //for debug
    targetValue = stoi(str, nullptr, 16);
    targetValue+= loading_offset;
    str = int2hexStr<int>(targetValue, hexLength);
    j = 0;
    if(hexLength&1)
        for(i=location+1; i<=location+hexLength; ++i)
            memory[i] = str[j++];
    else
        for(i=location; i<=location+hexLength-1; ++i)
            memory[i] = str[j++];
}
