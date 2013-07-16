//子集的遍历，用bit表示
//http://www.cnblogs.com/kelamayi/archive/2010/07/19/1780808.html
//http://www.cnblogs.com/atyuwen/archive/2010/08/05/bit_comb_2.html

for (unsigned long i = s; i ; i = (i - 1) & s)//神奇的(i-1)&s,倒着便利
{
    visit(i);
}


///////正向遍历
for (unsigned long i = 0; ; i = (i - s) & s)
{
    visit(i);
    if (i == s) break;
}
