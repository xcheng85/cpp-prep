
#include <gtest/gtest.h>
#include <unordered_map>
#include <finegrainedhashmapthreadsafe.h>

using namespace core::container;

// Test Fixtures: Using the Same Data Configuration for Multiple Tests
class FineGrainedHashMapThreadSafeTest : public testing::Test
{
protected:
    FineGrainedHashMapThreadSafeTest()
    {
        _m0.setVal(1, 1);
    }

    // ~FineGrainedHashMapThreadSafeTest() override = default;

    FineGrainedHashMapThreadSafe<int, int> _m0;
};

// ASSERT VS EXPECT
// ASSERT: ABORT
// EXPECT: CONTINUE 

TEST_F(FineGrainedHashMapThreadSafeTest, TestFixtureInit)
{
    constexpr int k = 1;
    EXPECT_TRUE(_m0.value(k).has_value());
    _m0.del(k);
    ASSERT_FALSE(_m0.value(k).has_value());
}

// // ./hashmap_test --gtest_brief=1
// TEST(HashmapTest, Ctor)
// {
//     FineGrainedHashMapThreadSafe<int, int> hm;
//     auto p{hm.peek()};
//     EXPECT_EQ(1, p.size()) << "Vectors x and y are of unequal length";
// }
