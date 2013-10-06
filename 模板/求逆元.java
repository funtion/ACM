int[] inv = new int[MAXN];
inv[1] = 1;
for (int i = 2; i<MAXN; i++)
    inv[i] = inv[MOD%i]*(MOD-MOD/i)%MOD;
///////MOD must be prime
