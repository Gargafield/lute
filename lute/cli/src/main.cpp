#include "lute/climain.h"
#include "lute/uvstate.h"
#include "clireporter.h"

int main(int argc, char** argv)
{
    UvGlobalState uvState(argc, argv);
    CLIReporter reporter;
    return cliMain(argc, argv, reporter);
}
