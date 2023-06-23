#include <bits/stdc++.h>
using namespace std;

#define FOR(i,m,n) for(int i = m; i < n; i++)
#define MAXN 100001

int T, n, m, q;
char format;
int h1, h2;
long a[MAXN], t[4*MAXN];

void build(long a[], int v, int tl, int tr) {
    if (tl == tr) 
        t[v] = a[tl];
    else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}

void update(long v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) t[v] = new_val;
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}

int query(long v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (l == tl && r == tr) return t[v];

    int tm = (tl + tr) / 2;
    return max(query(v*2, tl, tm, l, min(r, tm)),
           query(v*2+1, tm+1, tr, max(l, tm+1), r));
}

int main(){
    scanf("%d ", &T);
    FOR(c,0,T){
        scanf("%d %d ", &n, &m);
        FOR(i,0,n) scanf("%d ", &a[i]);
        build(a, 1, 0, n-1);
        
        printf("Testcase %d:\n", c);
        scanf("%d ", &q);
        FOR(i,0,q){
            scanf("%c ", &format);
            if(format == 'A'){
                scanf("%d ", &h1);
                m += h1;
            } 
            else if(format == 'B'){
                scanf("%d %d ", &h1, &h2);
                update(1,0,n-1, h1, h2);
            }
            else{
                scanf("%d %d ", &h1, &h2);
                printf("%d\n", abs(m - query(1,0,n-1,h1,h2)));
            }
        }
        printf("\n");
    }
    return 0;
}
