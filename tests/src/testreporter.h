#pragma once

#include "lute/reporter.h"
#include <string>
#include <vector>

// Test reporter that captures output in vectors for verification
class TestReporter : public LuteReporter
{
public:
    void reportError(const std::string& message) override
    {
        errors.push_back(message);
    }

    void reportOutput(const std::string& message) override
    {
        outputs.push_back(message);
    }

    const std::vector<std::string>& getErrors() const
    {
        return errors;
    }

    const std::vector<std::string>& getOutputs() const
    {
        return outputs;
    }

    void clear()
    {
        errors.clear();
        outputs.clear();
    }

private:
    std::vector<std::string> errors;
    std::vector<std::string> outputs;
};
