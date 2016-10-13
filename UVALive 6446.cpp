#include<iostream>

#define plane vect

using namespace std;

struct vect
{
    int x, y, z;
    vect operator-(vect& next)
    {
        vect ans;
        ans.x = x - next.x;
        ans.y = y - next.y;
        ans.z = z - next.z;
        return ans;
    }
    bool operator==(vect& comp)
    {
        if(x == comp.x && y == comp.y && z == comp.z) return true;
        else return false;
    }
};

vect cross(vect a, vect b)
{
    vect next;
    next.x = a.y * b.z - a.z * b.y;
    next.y = a.z * b.x - a.x * b.z;
    next.z = a.x * b.y - b.x * a.y;
    return next;
}

int dot(vect a, vect b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

int main()
{
    int test_case;
    cin >> test_case;
    while(test_case--)
    {
        int n;
        int usable;
        int same[50];
        vect university[50];
        bool a_line = true;
        bool ans[50];
        cin >> n;
        usable = n;
        for(int i = 0; i < n; ++i) cin >> university[i].x >> university[i].y >> university[i].z;
        for(int i = 0; i < n; ++i)
        {
            same[i] = -1;
            ans[i] = false;
        }
        for(int i = 0; i < n; ++i)
        {
            for(int j = i + 1; j < n; ++j)
            {
                if(same[j] == -1 && university[j] == university[i])
                {
                    same[j] = i;
                    usable--;
                }
            }
        }
        for(int i = 0; i < n; ++i)
        {
            if(same[i] != -1) continue;
            for(int j = i + 1; j < n; ++j)
            {
                if(same[j] != -1) continue;
                for(int k = j + 1; k < n; ++k)
                {
                    if(same[k] != -1) continue;
                    int standard;
                    bool same_side = true;
                    bool positive = true;
                    bool first_l = true;
                    plane ijk = cross(university[j] - university[i], university[k] - university[i]);
                    if(ijk.x == 0 && ijk.y == 0 && ijk.z == 0) continue;
                    else a_line = false;
                    standard = dot(ijk, university[k]);
                    for(int l = 0; l < n; ++l)
                    {
                        if(l != i && l != j && l != k && same[l] == -1)
                        {
                            int product = dot(ijk, university[l]);
                            if(first_l)
                            {
                                if(product == standard) continue;
                                else if(product > standard) positive = true;
                                else positive = false;
                                first_l = false;
                            }
                            else
                            {
                                if(positive && product < standard) same_side = false;
                                else if(!positive && product > standard) same_side = false;
                            }
                        }
                    }
                    if(same_side) ans[i] = ans[j] = ans[k] = true;
                }
            }
        }
        if(usable <= 3 || a_line) for(int i = 0; i < n; ++i) cout << 'T';
        else
        {
            for(int i = 0; i < n; ++i)
            {
                if(same[i] == -1) cout << (ans[i] ? 'T' : 'F');
                else cout << (ans[same[i]] ? 'T' : 'F');
            }
        }
        cout << endl;
    }
    return 0;
}