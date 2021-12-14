int maxPower(char * s){
    int i, max, count, length;
    char current;
    length = strlen(s);
    current = s[0];
    max = 0;
    count = 1;
    for(i=1; i<length; i++){
        if(s[i]==current)
            count++;
        else{
            if(count > max)
                max = count;
            count = 1;
            current = s[i];
        }
    }
    if(count > max)
        max = count;
    return max;
}