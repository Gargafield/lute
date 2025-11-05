#include "cliruntimefixture.h"

#include "lua.h"
#include "lualib.h"

#include "Luau/Compiler.h"

static int report(lua_State* L)
{
    const char* str = luaL_tolstring(L, 1, nullptr);
    lua_getglobal(L, "reporter");
    if (lua_islightuserdata(L, -1))
    {
        // It's a light userdata, proceed to retrieve
        void* rep = lua_touserdata(L, -1); // Get it from the top of the stack
        TestReporter* reporter = static_cast<TestReporter*>(rep);
        reporter->reportOutput(str);
    }
    else
    {
        throw std::runtime_error("Expected reporter to be a light userdata");
    }
    return 0;
}

CliRuntimeFixture::CliRuntimeFixture()
    : runtime(std::make_unique<Runtime>())
    , reporter(std::make_unique<TestReporter>())
{
    L = setupCliState(
        *runtime,
        [rep = reporter.get()](lua_State* L)
        {
            lua_pushlightuserdata(L, (void*)rep);
            lua_setglobal(L, "reporter");
            lua_pushcfunction(L, report, "");
            lua_setglobal(L, "report");
        }
    );
}

TestReporter& CliRuntimeFixture::getReporter()
{
    return *reporter;
}

bool CliRuntimeFixture::runCode(const std::string& source)
{
    std::string bytecode = Luau::compile(source, Luau::CompileOptions());
    return runBytecode(*runtime, bytecode, "=stdin", L, 0, nullptr, getReporter());
}
