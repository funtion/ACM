std::ios::sync_with_stdio(false); 
//cin 瞬间拥有scanf的速度
//faster
namespace IO
{
template<class T> inline T RD(T &x)
{
    char c;
    for (c = getchar(); c < '-'; c = getchar());
    if (c == '-')
    {
        x = '0' - getchar();
        for (c = getchar(); '0' <= c && c <= '9'; c = getchar()) x = x * 10 + '0' - c;
    }
    else
    {
        x = c - '0';
        for (c = getchar(); '0' <= c && c <= '9'; c = getchar()) x = x * 10 + c - '0';
    }
    return x;
} inline int RD()
{
    int x;
    return RD(x);
}
} using namespace IO;
//
