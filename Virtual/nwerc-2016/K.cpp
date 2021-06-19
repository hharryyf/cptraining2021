/*
    This is not my code, Dallas implemented it 10 minutes after the contest,
    I added some comments to support understanding
*/
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define Point point

const ll MAXN = 2001;
const ld INF = 1e9;
struct point {
    ld x;
    ld y;
    point() {
        x = y = 0;
    }
    point(ld a, ld b) {
        x = a;
        y = b;
    }
};
point verts[MAXN];
point newVerts[MAXN];
/*
    this is equivalent to a - b in my template
*/
point sub(point a, point b) {
    return point(a.x-b.x,a.y-b.y);
}

/*
    this is equivalent to a + b in my template
*/

point add(point a, point b) {
    return point(a.x+b.x,a.y+b.y);
}

/*
    calculate the 2-norm of a vector
*/
ld nDist(point a) {
    return sqrt(a.x*a.x+a.y*a.y);
}

/*
    normalize the vector to a unit vector
*/
point norm(point a) {
    ld dist = nDist(a);
    return point(a.x/dist,a.y/dist);
}

/*
    scale the vector to length d, I can put it into my template
*/

point normD(point a, ld d) {
    point tem = norm(a);
    tem.x *= d;
    tem.y *= d;
    return tem;
}

/*
    get the normal of a vector
*/
point perp(point a) {
    return point(a.y,-a.x);
}

/*
    euclidian distance between 2 points
*/

ld pDist(point a, point b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

struct line {
    point a;
    point b;
    ld A,B,C;
    line() {
        
    }
    /*
        Line in Ax + By + C format, I prefer to use point vector though
    */
    line(point _a, point _b) {
        a = _a;
        b = _b;
        A = b.y-a.y;
        B = b.x-a.x;
        C = a.x*b.y-b.x*a.y;
    }
};
line oldLines[MAXN];
line lines[MAXN];
/*
    If two line intersect, if so we get the intersection point
*/
point intersect(line a, line b) {
    ld D = (a.a.x-a.b.x)*(b.a.y-b.b.y) - (a.a.y-a.b.y)*(b.a.x-b.b.x);
    ld x = (
        (a.a.x*a.b.y - a.a.y*a.b.x)*(b.a.x-b.b.x) - (a.a.x-a.b.x)*(b.a.x*b.b.y - b.a.y*b.b.x)
        )/D;
    ld y = (
        (a.a.x*a.b.y - a.a.y*a.b.x)*(b.a.y-b.b.y) - (a.a.y-a.b.y)*(b.a.x*b.b.y - b.a.y*b.b.x)
        )/D;
    return point(x,y);
}

/*
    dot product, similar to Dot in my template
*/

ld dp(point a, point b) {
    return a.x*b.x+a.y*b.y;
}

/*
    get the distance from point to a line
*/

ld perpD(point a, line b) {
    return abs(b.A*a.x+b.B*a.y+b.C)/sqrt(b.A*b.A+b.B*b.B);
}

int orientation(point p, point q, point r)
{
    ld val = (q.y - p.y) * (r.x - q.x) -
            (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0; // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

/*
    point q on segment (p,r)
*/

bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

/*
    segment/segment intersection
*/

bool doIntersect(point p1, point q1, point p2, point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
 
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
 
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
 
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
 
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
 
    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
 
    return false; // Doesn't fall in any of the above cases
}

/*
    if p is in polygon
*/

bool isInside(point polygon[], int n, point p)
{
    // There must be at least 3 vertices in polygon[]
    if (n < 3) return false;
 
    // Create a point for line segment from p to infinite
    point extreme = {INF, p.y};
 
    // Count intersections of the above line with sides of polygon
    int count = 0, i = 0;
    do
    {
        int next = (i+1)%n;
 
        // Check if the line segment from 'p' to 'extreme' intersects
        // with the line segment from 'polygon[i]' to 'polygon[next]'
        if (doIntersect(polygon[i], polygon[next], p, extreme))
        {
            // If the point 'p' is colinear with line segment 'i-next',
            // then check if it lies on segment. If it lies, return true,
            // otherwise false
            if (orientation(polygon[i], p, polygon[next]) == 0)
            return onSegment(polygon[i], p, polygon[next]);
 
            count++;
        }
        i = next;
    } while (i != 0);
 
    // Return true if count is odd, false otherwise
    return count&1; // Same as (count%2 == 1)
}

ll n;
ld angles[MAXN];
bool invalids[MAXN];

int main() {
    scanf("%lld",&n);
    for (ll i=0;i<n;i++) {
        scanf("%Lf %Lf",&verts[i].x,&verts[i].y);
    }
    for (ll i=0;i<n;i++) {
        ll prev = (i+n-1)%n;
        // consider the line formed by 2 adjacent vertices
        oldLines[i] = line(verts[i],verts[prev]);
        // the vector formed by push the old line 4 meters into the polygon
        point perp4 = perp(normD(sub(verts[i],verts[prev]),(ld)4*1000));
        // get the equation of the new line
        lines[i] = line(add(verts[i],perp4),add(verts[prev],perp4));
    }

    for (ll i=0;i<n;i++) {
        ll prev = (i+n-1)%n;
        // get the new vertices formed by the new lines, these new vertices would form a new polygon
        // but note that some vertices might be outside the polygon
        newVerts[prev] = intersect(lines[i],lines[prev]);
    }
    for (ll i=0;i<n;i++) {
        if (!isInside(verts,n,newVerts[i])) {
            // if the ith point is not in the polygon, it is invalid
            // otherwise, any of these points can be the candidate
            // the reason is these points have a valid distances away from the side of the polygon
            invalids[i] = true;
        }
    }
    for (ll i=0;i<n;i++) {
        if (invalids[i]) {continue;}
        for (ll j=0;j<n;j++) {
            if (invalids[j]) {continue;}
            // manipulate any 2 valid points, if they have a good margin, then output
            if (pDist(newVerts[i],newVerts[j]) >= (ld)8*1000) {
                printf("%Lf %Lf\n%Lf %Lf\n",newVerts[i].x,newVerts[i].y,newVerts[j].x,newVerts[j].y);
                return 0;
            }
        }
    }
    printf("impossible\n");
    return 0;
}