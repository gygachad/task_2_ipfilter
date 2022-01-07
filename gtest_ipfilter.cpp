#include <string>

#include <gtest/gtest.h>

#include "version.h"
#include "gtest_ipfilter.h"
#include "ip_pool.h"

using namespace std;

class TestSerialization : public ::testing::Test {
public:
    TestSerialization() { /* init protected members here */ }
    ~TestSerialization() { /* free protected members here */ }
    void SetUp() { /* called before every test */ }
    void TearDown() { /* called after every test */ }

protected:
    /* none yet */
};

TEST_F(TestSerialization, DateJson)
{
    EXPECT_TRUE(version() > 0);

    string test_mask = "1.*.*.4";

    ip_addr addr;

    addr.parse("1.2.3.4");
    EXPECT_TRUE(addr.match(test_mask));

    addr.parse("2.2.3.4");
    EXPECT_FALSE(addr.match(test_mask));

    ip_pool filter = ip_pool();

    vector<string> not_filtered = ip_pool::split(string(NOT_FILTERED), '\n');

    for(auto line = not_filtered.begin(); line != not_filtered.end(); line++)
    {
        vector<string> v = ip_pool::split(*line, '\t');

        ip_addr ip = ip_addr();

        if (ip.parse(v.at(0)))
            filter.push_back(ip);
    }

    filter.reverse_sort();

    ip_pool filtered_by_first;
    filtered_by_first.push_back(filter.filter("1.*.*.*"));

    ip_pool filtered_by_first_and_second;
    filtered_by_first_and_second.push_back(filter.filter("46.70.*.*"));

    ip_pool filtered_by_any;
    filtered_by_any.push_back(filter.filter_any("46"));

    string filtered = "";

    filtered += filter.to_string();
    filtered += filtered_by_first.to_string();
    filtered += filtered_by_first_and_second.to_string();
    filtered += filtered_by_any.to_string();

    filtered.erase(remove(filtered.begin(), filtered.end(), '\r'), filtered.end());
    filtered.erase(remove(filtered.begin(), filtered.end(), '\n'), filtered.end());

    string filtered_check(FILTERED);

    EXPECT_TRUE(filtered_check == filtered);
}

int main(int argc, char** argv) 
{    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}