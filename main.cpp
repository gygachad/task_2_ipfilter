#include "ip_filter.h"
#include "version.h"

#include <iostream>

int main(int argc, char const *argv[]) {

	std::cout << "ip_filter version: " << version() << std::endl;

	return ip_filter_main(argc, argv);
}
