/*
https://oj.nctu.me/groups/2/contests/1021/problems/10078/
最後少做一件事情TLE了QQ 不過segment tree是測過沒問題會動的
*/

#include<cstdio>
#include<vector>

using namespace std;

vector<int> segment_tree[25];

int sum;

void add(int L, int R, int now_idx, int level)
{
    if(L==(1<<level)*now_idx && R==((1<<level)*(now_idx + 1) - 1)) sum = sum | segment_tree[level][now_idx];
    else if(R<((1<<level)*now_idx + (1<<(level-1)))) add(L, R, now_idx << 1, level-1);
    else if(L>=(1<<level)*now_idx + (1<<(level-1))) add(L, R, (now_idx << 1)+ 1, level-1);
    else
    {
        add(L, (1<<level)*now_idx + ((1<<(level-1)) - 1), now_idx << 1, level-1);
        add((1<<level)*now_idx + (1<<(level-1)), R, (now_idx << 1) + 1, level-1);
    }
    return;
}

int main()
{
    int n, q, k;
    int level = 0;
    scanf("%d", &n);
    scanf("%d", &q);
    scanf("%d", &k);
    for(int i=0; i<n; ++i)
    {
        int tmp;
        scanf("%d", &tmp);
        segment_tree[0].push_back(tmp);
    }
    if(n&1)
    {
        segment_tree[0].push_back(0);
        ++n;
    }
    n /= 2;
    while(n>0)
    {
        level++;
        for(int i=0; i<n; ++i)
        {
            int tmp = segment_tree[level-1][2*i] | segment_tree[level-1][2*i+1];
            segment_tree[level].push_back(tmp);
        }
        if(n!=1 && n&1)
        {
            segment_tree[level].push_back(0);
            ++n;
        }
        n /= 2;
    }
    for(int i=0; i<q; ++i)
    {
        int l, r;
        int mx = 0;
        scanf("%d", &l);
        scanf("%d", &r);
        for(int j=l; j<=r-k+1; ++j)
        {
            sum = 0;
            add(j, j+k-1, 0, level);
            if(sum>mx) mx = sum;
        }
        printf("%d\n", mx);
    }
    return 0;
}
