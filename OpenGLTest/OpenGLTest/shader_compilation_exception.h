#pragma once
#include <exception>
using namespace std;
class shader_compilation_exception : public exception
{
public:
	shader_compilation_exception();
	~shader_compilation_exception();
	const char* what() const throw();
};

