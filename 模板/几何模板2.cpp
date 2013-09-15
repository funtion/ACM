//HDU 4741

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const double EPS = 1e-9;
const int MAXN = 40;

struct Point3  //空间点
{
    double x, y, z;
    Point3( double x=0, double y=0, double z=0 ): x(x), y(y), z(z) { }
    Point3( const Point3& a )
    {
        x = a.x;
        y = a.y;
        z = a.z;
        return;
    }
    void showP()
    {
        printf("%f %f %f \n", x, y, z);
    }
    Point3 operator+( Point3& rhs )
    {
        return Point3( x+rhs.x, y+rhs.y, z+rhs.z );
    }
};

struct Line3   //空间直线
{
    Point3 a, b;
};

struct plane3   //空间平面
{
    Point3 a, b, c;
    plane3() {}
    plane3( Point3 a, Point3 b, Point3 c ):
        a(a), b(b), c(c) { }
    void showPlane()
    {
        a.showP();
        b.showP();
        c.showP();
        return;
    }
};

double dcmp( double a )
{
    if ( fabs( a ) < EPS ) return 0;
    return a < 0 ? -1 : 1;
}

//三维叉积
Point3 Cross3( Point3 u, Point3 v )
{
    Point3 ret;
    ret.x = u.y * v.z - v.y * u.z;
    ret.y = u.z * v.x - u.x * v.z;
    ret.z = u.x * v.y - u.y * v.x;
    return ret;
}

//三维点积
double Dot3( Point3 u, Point3 v )
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

//矢量差
Point3 Subt( Point3 u, Point3 v )
{
    Point3 ret;
    ret.x = u.x - v.x;
    ret.y = u.y - v.y;
    ret.z = u.z - v.z;
    return ret;
}

//两点距离
double TwoPointDistance( Point3 p1, Point3 p2 )
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) + (p1.z - p2.z)*(p1.z - p2.z) );
}

//向量的模
double VectorLenth( Point3 p )
{
    return sqrt( p.x*p.x + p.y*p.y + p.z*p.z );
}

//空间直线距离
double LineToLine( Line3 u, Line3 v, Point3& tmp )
{
    tmp = Cross3( Subt( u.a, u.b ), Subt( v.a, v.b ) );
    return fabs( Dot3( Subt(u.a, v.a), tmp ) ) / VectorLenth(tmp);
}

//取平面法向量
Point3 pvec( plane3 s )
{
    return Cross3( Subt( s.a, s.b ), Subt( s.b, s.c ) );
}

//空间平面与直线的交点
Point3 Intersection( Line3 l, plane3 s )
{
    Point3 ret = pvec(s);
    double t = ( ret.x*(s.a.x-l.a.x)+ret.y*(s.a.y-l.a.y)+ret.z*(s.a.z-l.a.z) )/( ret.x*(l.b.x-l.a.x)+ret.y*(l.b.y-l.a.y)+ret.z*(l.b.z-l.a.z) );
    ret.x = l.a.x + ( l.b.x - l.a.x ) * t;
    ret.y = l.a.y + ( l.b.y - l.a.y ) * t;
    ret.z = l.a.z + ( l.b.z - l.a.z ) * t;
    return ret;
}

/************以上模板*************/

void solved( Line3 A, Line3 B )
{
    Point3 normal;
    double dis = LineToLine( A, B, normal );
    printf( "%.6f\n", dis );
    plane3 pla;
    pla = plane3( A.a, A.b, A.a + normal );
    Point3 u = Intersection( B, pla );
    pla = plane3( B.a, B.b, B.a + normal );
    Point3 v = Intersection( A, pla );
    printf("%.6f %.6f %.6f %.6f %.6f %.6f\n", v.x, v.y, v.z, u.x, u.y, u.z );
    return;
}

int main()
{
    int T;
    scanf( "%d", &T );
    while ( T-- )
    {
        Line3 A, B;
        scanf("%lf%lf%lf", &A.a.x, &A.a.y, &A.a.z );
        scanf("%lf%lf%lf", &A.b.x, &A.b.y, &A.b.z );
        scanf("%lf%lf%lf", &B.a.x, &B.a.y, &B.a.z );
        scanf("%lf%lf%lf", &B.b.x, &B.b.y, &B.b.z );
        solved( A, B );
    }
    return 0;
}
