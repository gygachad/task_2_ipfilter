#include <regex>

#include "ip_addr.h"
#include "ip_pool.h"

bool ip_addr::parse(string str_addr)
{
    bool parsed = true;

    this->str_octets.clear();
    this->str_addr = "";

    //Minimal check
    regex ip_re("(\\d{1,3}\\.){3}\\d{1,3}");
    if (!regex_match(str_addr, ip_re))
        return false;

    vector<string> splitted_ip = ip_pool::split(str_addr, '.');

    for (size_t i = 0; i < splitted_ip.size(); i++)
    {
        unsigned long octect = stoul(splitted_ip[i]);
        if (0 <= octect && octect <= 255)
        {
            this->octets[i] = (unsigned char)octect;
        }
        else
        {
            parsed = false;
            break;
        }

        string str_octet = to_string(this->octets[i]);

        this->str_addr += str_octet;
        this->str_octets.push_back(str_octet);

        if (i != 3)//We don't need dot after last octet (a.b.c.d.)
            this->str_addr += ".";
    }

    if (!parsed)
    {
        this->str_octets.clear();
        this->str_addr = "";
    }

    return parsed;
}

bool operator == (const ip_addr& a, const ip_addr& b)
{
    for (size_t i = 0; i < 4; i++)
    {
        if (a.octets[i] != b.octets[i])
            return false;
    }

    return true;
}

bool operator < (const ip_addr& a, const ip_addr& b)
{
    for (size_t i = 0; i < 4; i++)
        if (a.octets[i] != b.octets[i])
            return a.octets[i] < b.octets[i];

    //a == b
    return false;
}

bool ip_addr::match(const string& mask)
{
    bool matched = true;

    //Minimal check
    regex mask_re("((\\d{1,3}|\\*)\\.){3}(\\d{1,3}|\\*)");
    if (!regex_match(mask, mask_re))
        return false;

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