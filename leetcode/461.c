

int hammingDistance(int x, int y){
    x = x^y;    //xor
    y = 0;
    for(; x; x>>=1)
        y+= x&1;
    return y;    
}