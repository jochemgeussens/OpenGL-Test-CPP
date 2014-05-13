
#include <exception>
using namespace std; 
class Exception : public exception
{
public:
	Exception(string m = "exception!") : msg(m) {}
	~Exception() throw() {}
	const char* what() const throw() { return msg.c_str(); }

private:
	string msg;
};
