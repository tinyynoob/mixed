

int arrangeCoins(int n){
    int stair;
    for(stair=1; n>=stair; stair++)
        n-= stair;
    return stair-1;
}