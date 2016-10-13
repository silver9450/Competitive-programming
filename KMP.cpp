#include <iostream>
#include <vector>

using namespace std;

string s, j;
vector<int> match_point;
vector<int> fail;

void half_KMP(string& s, string& j, vector<int>& fail)
{
    bool build = ((&s) == (&j));
    if(build) fail.push_back(-1);
    for(int i = 0, fail_bit = -1; i < (int)s.size(); ++i)
    {
        if(i == 0 && build) continue;
        while(s[i] != j[fail_bit + 1] && (fail_bit >= 0)) fail_bit = fail[fail_bit];
        if(s[i] == j[fail_bit + 1]) fail_bit++;
        if(build) fail.push_back(fail_bit);
        if(!build && fail_bit == (int)(j.size() - 1))
        {
            match_point.push_back(i - j.size() + 1);
            fail_bit = fail[fail_bit];
        }
    }
}

int main()
{
    cout << "Please input S: ";
    cin >> s;
    cout << "Please input J: ";
    cin >> j;
    half_KMP(j, j, fail);
    half_KMP(s, j, fail);
    cout << "Fail function of J: ";
    for(int i = 0; i < (int)j.size(); ++i) cout << fail[i] << ' ';
    cout << endl;
    cout << "Match point(s): ";
    for(auto i: match_point) cout << i << ' ';
    cout << endl;
    return 0;
}
