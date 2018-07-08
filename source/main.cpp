#include <iostream>


#define LOG(message) do { std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " << message << std::endl; } while(0)


int main()
{
	LOG("Hello, World!");

	return EXIT_SUCCESS;
}
