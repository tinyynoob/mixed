

int coinChange(int* coins, int coinsSize, int amount)
{
    int table[amount + 1];
    table[0] = 0;
    for (int curr = 1; curr < amount + 1; curr++) {
        table[curr] = amount + 1;   // means impossible
        for (int i = 0; i < coinsSize; i++) {
            if (curr - coins[i] < 0)
                continue;
            else if (table[curr - coins[i]] + 1 < table[curr])
                table[curr] = table[curr - coins[i]] + 1;
        }
    }
    return (table[amount] == amount + 1) ? -1 : table[amount];
}