#include "CppUTest/TestHarness.h"

extern "C"
{
#include "Example.h"
}

TEST_GROUP(Example)
{
    void setup(void)
    {
    }

    void teardown(void)
    {
    }
};

TEST(Example, FailingTest)
{
    CHECK_EQUAL(1, GetValue());
}
