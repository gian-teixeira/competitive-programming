#include <bits/stdc++.h>
using namespace std;

#define FOR(i,m,n) for(int i = m; i < n; i++)
#define MAXN 20001

unsigned long c, n, k;
unsigned a[MAXN], t[4*MAXN];

void build(unsigned a[], int v, int tl, int tr) {
    if (tl == tr) t[v] = a[tl];
    else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = t[v*2] & t[v*2+1];
    }
}

int query(int v, int tl, int tr, int l, int r) {
    if (l > r) return -1;
    if (l == tl && r == tr) return t[v];

    int tm = (tl + tr) / 2;
    return query(v*2, tl, tm, l, min(r, tm))
           & query(v*2+1, tm+1, tr, max(l, tm+1), r);
}

int main()
{   
    scanf("%d ", &c);
    while(c--){
        scanf("%d %d ", &n, &k);
        FOR(i,0,n) scanf("%d ", &a[i]);
    
        build(a,1,0,n-1);
        FOR(i,0,n){
            int l = i - k;
            int r = i + k;
            int AND;
            
            #define squery(l, r) query(1,0,n-1,l,r)
            if(k >= n/2) AND = squery(0,n-1);
            else if(r > n-1) AND = squery(l,n-1) & squery(0,r-n);
            else if(l < 0) AND = squery(n+l,n-1) & squery(0, r);
            else AND = squery(l,r);
    
            printf("%d ", AND);
        }
        printf("\n");
    }

    return 0;
}
