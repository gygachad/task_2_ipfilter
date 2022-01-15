#include "ip_pool.h"

using namespace std;

void ip_pool::push_back(ip_addr ip)
{
    this->ip_addr_pool.push_back(ip);
}

void ip_pool::push_back(vector<ip_addr> ip_pool)
{
    for (auto ip = ip_pool.begin(); ip != ip_pool.end(); ip++)
        this->push_back(*ip);
}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
vector<std::string> ip_pool::split(const string& str, char d)
{
    vector<std::string> r;

    string::size_type start = 0;
    string::size_type stop = str.find_first_of(d);
    while (stop != string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void ip_pool::reverse_sort()
{
    sort(this->ip_addr_pool.begin(), this->ip_addr_pool.end(), [](ip_addr a, ip_addr b) {return a > b; });
}

vector<ip_addr> ip_pool::filter(const string& mask)
{
    vector<ip_addr> filtered;

    for (auto ip = this->ip_addr_pool.begin(); ip != this->ip_addr_pool.end(); ip++)
    {
        if(ip->match(mask))
            filtered.push_back(*ip);
    }

    return filtered;
}

vector<ip_addr> ip_pool::filter_any(const string& octet)
{
    vector<ip_addr> filtered;

    for (auto ip = this->ip_addr_pool.begin(); ip != this->ip_addr_pool.end(); ip++)
    {
        for(auto ip_octet = ip->str_octets.begin(); ip_octet != ip->str_octets.end(); ip_octet++)
        {
            if (*ip_octet == octet)
            {
                filtered.push_back(*ip);
                break;
            }
        }
    }

    return filtered;
}

string ip_pool::to_string()
{
    string out = "";

    for (auto ip = this->ip_addr_pool.begin(); ip != this->ip_addr_pool.end(); ip++)
    {
        out += ip->str_addr;
        out += "\n";
    }

    return out;
}