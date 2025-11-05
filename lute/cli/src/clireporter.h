#pragma once

#include "lute/reporter.h"
#include <cstdio>

// Standard CLI reporter that writes to stderr and stdout
class CLIReporter : public LuteReporter
{
public:
    void reportError(const std::string& message) override
    {
        fprintf(stderr, "%s\n", message.c_str());
    }

    void reportOutput(const std::string& message) override
    {
        fprintf(stdout, "%s\n", message.c_str());
    }
};
