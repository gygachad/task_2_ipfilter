#include "ip_addr.h"
#include "ip_pool.h"

bool ip_addr::parse(string str_addr)
{
    vector<string> splitted_ip = ip_pool::split(str_addr, '.');

    if (splitted_ip.size() != 4)
        return false;

    unsigned long octect = 0;

    octect = stoul(splitted_ip[0]);
    if (!(0 <= octect && octect <= 255))
        return false;
    this->octet0 = (unsigned char)octect;
    this->str_octets.push_back(splitted_ip[0]);

    octect = stoul(splitted_ip[1]);
    if (!(0 <= octect && octect <= 255))
        return false;
    this->octet1 = (unsigned char)octect;
    this->str_octets.push_back(splitted_ip[1]);

    octect = stoul(splitted_ip[2]);
    if (!(0 <= octect && octect <= 255))
        return false;
    this->octet2 = (unsigned char)octect;
    this->str_octets.push_back(splitted_ip[2]);

    octect = stoul(splitted_ip[3]);
    if (!(0 <= octect && octect <= 255))
        return false;
    this->octet3 = (unsigned char)octect;
    this->str_octets.push_back(splitted_ip[3]);

    this->str_addr = str_addr;

    return true;
}

bool operator < (const ip_addr& a, const ip_addr& b)
{
    if (a.octet0 == b.octet0)
    {
        if (a.octet1 == b.octet1)
        {
            if (a.octet2 == b.octet2)
                return a.octet3 < b.octet3;
            else
                return a.octet2 < b.octet2;
        }
        else
        {
            return a.octet1 < b.octet1;
        }
    }
    else
    {
        return a.octet0 < b.octet0;
    }
}

bool ip_addr::match(const string& mask)
{
    bool matched = true;

    vector<string> splitted_mask = ip_pool::split(mask, '.');

    if (splitted_mask.size() != 4)
        return false;

    for(int i = 0; i < 4; i++)
    {
        if(splitted_mask[i] != "*")
        {
            if (splitted_mask[i] != this->str_octets[i])
            {
                matched = false;
                break;
            }
        }
    }

    return matched;
}