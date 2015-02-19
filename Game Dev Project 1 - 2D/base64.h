#pragma once
#include <string>
#include <vector>
class base64
{
	public:
	std::vector<int> getVectors();
	std::string base64_decode(std::string const& encoded_string);

	private:
	std::vector<int> vec;
};


