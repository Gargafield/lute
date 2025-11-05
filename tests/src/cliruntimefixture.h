#pragma once
#include "doctest.h"

#include "lute/climain.h"
#include "lute/runtime.h"

#include "testreporter.h"

#include "lua.h"

#include <memory>
#include <string>

class CliRuntimeFixture
{
public:
    CliRuntimeFixture();

    bool runCode(const std::string& source);

    lua_State* L;

    TestReporter& getReporter();

private:
    std::unique_ptr<Runtime> runtime;
    std::unique_ptr<TestReporter> reporter;
};
