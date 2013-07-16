//用bit表示集合

//http://www.cnblogs.com/kelamayi/archive/2010/07/19/1780808.html
//http://www.cnblogs.com/atyuwen/archive/2010/08/05/bit_comb_2.html


/////所有子集////////////
///////逆向遍历
for (unsigned long i = s; i ; i = (i - 1) & s)//神奇的(i-1)&s
{
    visit(i);
}


///////正向遍历
for (unsigned long i = 0; ; i = (i - s) & s)
{
    visit(i);
    if (i == s) break;
}
//////////////////于输入有相同元素个数的集合/////////////////
bool next(unsigned long &x) const
{
    if (x == last_) return false;
    unsigned long r, s;
    s = x & (-(long)x);
    r = s + x;
    x = r | (((x ^ r) >> 2) / s);
    return true;
}
