/* KMP algorithm with the fail function of S printed (takes more space in order to keep record) */
#include <iostream>
#include <vector>

using namespace std;

string s, j;
vector<int> match_point;
vector<int> s_fail, j_fail;

void half_KMP(string& s, string& j, vector<int>& s_fail, vector<int>& j_fail)
{
    bool build = ((&s) == (&j));
    if(build) j_fail.push_back(-1);
    for(int i = 0, fail_bit = -1; i < (int)s.size(); ++i)
    {
        if(i == 0 && build) continue;
        while(s[i] != j[fail_bit + 1] && (fail_bit >= 0)) fail_bit = j_fail[fail_bit];
        if(s[i] == j[fail_bit + 1]) fail_bit++;
        s_fail.push_back(fail_bit);
        if(!build && fail_bit == (int)(j.size() - 1))
        {
            match_point.push_back(i - j.size() + 1);
            fail_bit = j_fail[fail_bit];
        }
    }
}

int main()
{
    cout << "Please input S: ";
    cin >> s;
    cout << "Please input J: ";
    cin >> j;
    half_KMP(j, j, j_fail, j_fail);
    half_KMP(s, j, s_fail, j_fail);
    cout << "Fail function of S: ";
    for(int i = 0; i < (int)s.size(); ++i) cout << s_fail[i] << ' ';
    cout << endl;
    cout << "Fail function of J: ";
    for(int i = 0; i < (int)j.size(); ++i) cout << j_fail[i] << ' ';
    cout << endl;
    cout << "Match point(s): ";
    for(auto i: match_point) cout << i << ' ';
    cout << endl;
    return 0;
}

