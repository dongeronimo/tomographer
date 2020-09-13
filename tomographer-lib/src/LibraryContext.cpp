#include "LibraryContext.h"

LibraryContext::LibraryContext():testCounter(0){}

void LibraryContext::TestIncrement()
{
    testCounter++;
}
int LibraryContext::TestCounter()
{
    return testCounter;
}
