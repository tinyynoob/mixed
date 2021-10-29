

char * intToRoman(int num){
    int length_of_ans, digit, i, index;
    char ans[16];
    char *s;

    index = 0;
    //1000+
    digit = num/1000;
    for(i=0; i<digit; i++)
        ans[index++] = 'M';
    num = num%1000;
    //1~999
    digit = num/100;
    if(digit%5 == 4){
        ans[index++] = 'C';
        if(digit/5)
            ans[index++] = 'M';
        else
            ans[index++] = 'D';
    }
    else{
        if(digit>=5){
            ans[index++] = 'D';
            digit-= 5;
        }
        for(i=0; i<digit; i++)
            ans[index++] = 'C';
    }
    num = num%100;
    //1~99
    digit = num/10;
    if(digit%5 == 4){
        ans[index++] = 'X';
        if(digit/5)
            ans[index++] = 'C';
        else
            ans[index++] = 'L';
    }
    else{
        if(digit>=5){
            ans[index++] = 'L';
            digit-= 5;
        }
        for(i=0; i<digit; i++)
            ans[index++] = 'X';
    }
    num = num%10;
    //1~9
    digit = num;
    if(digit%5 == 4){
        ans[index++] = 'I';
        if(digit/5)
            ans[index++] = 'X';
        else
            ans[index++] = 'V';
    }
    else{
        if(digit>=5){
            ans[index++] = 'V';
            digit-= 5;
        }
        for(i=0; i<digit; i++)
            ans[index++] = 'I';
    }
    ans[index] = '\0';
    length_of_ans = strlen(ans)+1;
    s = (char*)malloc(sizeof(char)*length_of_ans);
    for(i=0; i<length_of_ans; i++)
        s[i] = ans[i];
    return s;
}