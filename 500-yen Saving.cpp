/* http://icpc.iisf.or.jp/past-icpc/domestic2015/contest/all_en.html#section_D */

#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

struct store
{
    int price, rest;
};

int after_last;
int c[1000];
store s[100];

int knapsack(int n, int w, int last)
{
    memset(c, 0, sizeof(c));
    for(int i = 0; i < n; ++i)
    {
        int weight = s[i].rest;
        int cost = s[i].price;
        for(int j = w; (j - weight) >= 0; --j)
        {
            if(c[j - weight] + cost >= c[j])
            {
                if(i >= last) after_last++;
                c[j] = c[j - weight] + cost;
            }
        }
    }
    return c[w];
}

int main()
{
    cin.sync_with_stdio(false);
    cin.tie(NULL);
    while(1)
    {
        int n;
        int gohyaku, change;
        int last, min_last;
        int skip;
        int ans;
        cin >> n;
        if(n == 0) break;
        else
        {
            ans = 0;
            gohyaku = change = 0;
            last = -1;
            after_last = 0;
            min_last = 1e9;
            for(int i = 0; i < n; ++i)
            {
                store now;
                cin >> now.price;
                now.rest = (now.price * (-1)) % 1000;
                if(now.rest != 0) now.rest += 1000;
                s[i] = now;
            }
        }
        for(int i = 0; i < n; ++i)
        {
            if(change >= 500)
            {
                gohyaku += (change / 500);
                change %= 500;
            }
            if(i == 0)
            {
                gohyaku = s[i].rest / 500;
                change = s[i].rest % 500;
            }
            else
            {
                if(s[i].rest == 0) ;
                else if(s[i].rest >= 500)
                {
                    gohyaku++;
                    change += (s[i].rest - 500);
                }
                else
                {
                    if((500 - s[i].rest) <= change)
                    {
                        gohyaku++;
                        change -= (500 - s[i].rest);
                    }
                    else change += s[i].rest;
                }
            }
            if(change >= 500) last = i + 1;
        }
        skip = knapsack(n, change, last);
        for(int i = 0; i < n; ++i) ans += s[i].price;
        ans -= skip;
        if((last != -1) && (last != n) && (after_last == n - last))
        {
            for(int i = last; i < n; ++i) min_last = min(min_last, s[i].price);
            ans += min_last;
        }
        cout << gohyaku << " " << ans << endl;
    }
    return 0;
}
