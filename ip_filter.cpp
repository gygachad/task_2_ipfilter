#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
vector<std::string> split(const string &str, char d)
{
    vector<std::string> r;

    string::size_type start = 0;
    string::size_type stop = str.find_first_of(d);
    while(stop != string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

bool comp(vector<string> a, vector<string> b)
{        
    if (a[0] == b[0])
    {
        if (a[1] == b[1])
        {
            if (a[2] == b[2])
                return stoul(a[3]) > stoul(b[3]);
            else
                return stoul(a[2]) > stoul(b[2]);
        }
        else
        {
            return stoul(a[1]) > stoul(b[1]);
        }
    }
    else
    {
        return stoul(a[0]) > stoul(b[0]);
    }
}

void print_ip_pool(vector<vector<string>> ip_pool)
{
    for (vector<vector<string>>::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        for (vector<string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                cout << ".";

            }
            cout << *ip_part;
        }
        cout << endl;
    }
}

vector<vector<string>>* filter(vector<vector<string>> ip_pool, string first)
{
    vector<vector<string>>* filtered = new vector<vector<string>>();

    for each (vector<string> ip in ip_pool)
    {
        if (ip[0] == first)
            filtered->push_back(ip);
    }

    return filtered;
}

vector<vector<string>>* filter(vector<vector<string>> ip_pool, string first, string second)
{
    vector<vector<string>>* filtered = new vector<vector<string>>();

    for each (vector<string> ip in ip_pool)
    {
        if (ip[0] == first && ip[1] == second)
            filtered->push_back(ip);
    }

    return filtered;
}

vector<vector<string>>* filter_any(vector<vector<string>> ip_pool, string val)
{
    vector<vector<string>>* filtered = new vector<vector<string>>();

    for each (vector<string> ip in ip_pool)
    {
        if (ip[0] == val || 
            ip[1] == val || 
            ip[2] == val || 
            ip[3] == val
            )
            filtered->push_back(ip);
    }

    return filtered;
}

int ip_filter_main(int argc, char const *argv[])
{
    try
    {
        vector<vector<string>> ip_pool;

        for(string line; getline(std::cin, line);)
        {
            vector<string> v = split(line, '\t');
            vector<string> splitted_ip = split(v.at(0), '.');

            ip_pool.push_back(splitted_ip);
        }

        // TODO reverse lexicographically sort
        sort(ip_pool.begin(), ip_pool.end(), comp);

        cout << "reverse lexicographically sort" << endl;
        print_ip_pool(ip_pool);
        cout << endl;

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        //ip = filter(1);

        vector<vector<string>>* filtered_by_first= filter(ip_pool, "1");

        cout << "filtered by first 1" << endl;
        print_ip_pool(*filtered_by_first);
        cout << endl;

        delete filtered_by_first;

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        vector<vector<string>>* filtered_by_first_and_second = filter(ip_pool, "46", "70");

        cout << "filtered by first 46 and second 70" << endl;
        print_ip_pool(*filtered_by_first_and_second);
        cout << endl;

        delete filtered_by_first_and_second;

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        vector<vector<string>>* filtered_by_any = filter_any(ip_pool, "46");

        cout << "filtered by any 46" << endl;
        print_ip_pool(*filtered_by_any);
        cout << endl;

        delete filtered_by_any;

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const exception &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
