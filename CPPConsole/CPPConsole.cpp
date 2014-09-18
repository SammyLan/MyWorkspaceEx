// CPPConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/smart_ptr/shared_ptr.hpp>
#include <cstdio>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	FILE * f = fopen("text.txt","w");
	if(f == 0)
	{
		return 1;
	}
	boost::shared_ptr<FILE> my_shared_file(f,&fclose);
	boost::shared_ptr<FILE> my_shared_file1(my_shared_file);
	return 0;
}

