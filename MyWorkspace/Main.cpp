// MyWorkspace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Algorithms\isPowerOf.hpp"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	STATIC_ASSERT(1);
	STATIC_ASSERT(3);
    for (size_t i =0;i<32;++i)   
    {   
        unsigned int n = 1<<i;   
        if (isPowerOf<32>(n))   
        {   
          cout<<n<<endl; 
        }
    }

	  for (size_t i =0;i<1000000;++i)   
    {   
        if (isPowerOf<32>(i))   
        {   
			cout<<i<<endl; 
        }
    }
	  StaticAssertFailed<(bool)2>::val;
	return 0;
}

