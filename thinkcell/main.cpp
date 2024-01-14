#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"

#include "interval.hpp"

TEST_CASE("Test0") {
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(5), TestKeyType(15), TestValueType('B'));
    m.assign2(TestKeyType(20), TestKeyType(25), TestValueType('C'));
    m.assign2(TestKeyType(12), TestKeyType(22), TestValueType('D'));
    m.assign2(TestKeyType(14), TestKeyType(16), TestValueType('A'));
    m.assign2(TestKeyType(16), TestKeyType(22), TestValueType('A'));
    m.assign2(TestKeyType(22), TestKeyType(25), TestValueType('A'));
    m.assign2(TestKeyType(30), TestKeyType(35), TestValueType('A'));

    m.print();
    // for (int i = 0; i < 10; i++)
    // {
    //     REQUIRE(m[i] == 'B');
    // }
}

TEST_CASE("Test1") {
    interval_map<TestKeyType, TestValueType> m(TestValueType('B'));
    m.assign2(TestKeyType(1), TestKeyType(5), TestValueType('B'));
    m.print();
    for (int i = 0; i < 10; i++)
    {
        REQUIRE(m[i] == 'B');
    }
}

TEST_CASE("Test2") {
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(1), TestKeyType(5), TestValueType('B'));
    m.print();
    REQUIRE(m[0] == 'A');
    REQUIRE(m[5] == 'A');
    REQUIRE(m[6] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
}

TEST_CASE("Test3") {
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(5), TestKeyType(10), TestValueType('B'));
    m.assign2(TestKeyType(20), TestKeyType(30), TestValueType('C'));
    m.assign2(TestKeyType(0), TestKeyType(5), TestValueType('B'));
    m.print();
    for(int i = 0; i < 10; i++) {
        REQUIRE(m[i] == 'B');
    }
    for(int i = 10; i < 20; i++) {
        REQUIRE(m[i] == 'A');
    }
    for(int i = 20; i < 30; i++) {
        REQUIRE(m[i] == 'C');
    }
    for(int i = 30; i < 35; i++) {
        REQUIRE(m[i] == 'A');
    }
}

// may be buggy test case
TEST_CASE("Test4") {
    interval_map<TestKeyType, TestValueType> m(TestValueType('B'));
    m.assign2(TestKeyType(5), TestKeyType(10), TestValueType('B'));
    m.print();
    m.assign2(TestKeyType(20), TestKeyType(30), TestValueType('C'));
    m.print();
    m.assign2(0, 5, TestValueType('B'));
    m.print();
    for(int i = -10; i < 40; i++) {
        if(i >= 20 && i < 30) {
            REQUIRE(m[i] == 'C');
        } else {
            REQUIRE(m[i] == 'B');
        }
    }
}

TEST_CASE("Test4_1") {
    interval_map<TestKeyType, TestValueType> m(TestValueType('B'));
    m.assign2(TestKeyType(5), TestKeyType(10), TestValueType('B'));
    m.print();
    m.assign2(TestKeyType(20), TestKeyType(30), TestValueType('C'));
    m.print();
    m.assign2(TestKeyType(22), TestKeyType(27), TestValueType('B'));
    m.print();
    for(int i = -10; i < 40; i++) {
        if(i < 20 || (i >= 22 && i < 27) || i > 30) {
            REQUIRE(m[i] == 'B');
        } else if((i >= 20 && i < 22) || (i >= 27 && i < 30)) {
            REQUIRE(m[i] == 'C');
        }
    }
}


TEST_CASE("Test5") {
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(5), TestKeyType(10), TestValueType('B'));
    m.assign2(TestKeyType(20), TestKeyType(30), TestValueType('C'));
    m.assign2(TestKeyType(0), TestKeyType(15), TestValueType('A'));
    m.print();
    for(int i = 0; i < 40; i++) {
        if(i >= 20 && i < 30) {
            REQUIRE(m[i] == 'C');
        }else {
            REQUIRE(m[i] == 'A');
        }
    }
}

TEST_CASE("Test6") {
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(5), TestKeyType(10), TestValueType('B'));
    m.assign2(TestKeyType(20), TestKeyType(30), TestValueType('C'));
    m.assign2(TestKeyType(0), TestKeyType(5), TestValueType('B'));
    m.print();
    for(int i = -10; i < 50; i++) {
        if(i < 0 || i >= 30) {
            REQUIRE(m[i] == 'A');
        } else if(i < 10) {
            REQUIRE(m[i] == 'B');
        } else if(i < 20) {
            REQUIRE(m[i] == 'A');
        } else if(i < 30) {
            REQUIRE(m[i] == 'C');
        }
    }
}

TEST_CASE("Test7") {
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(5), TestKeyType(10), TestValueType('B'));
    m.assign2(TestKeyType(20), TestKeyType(30), TestValueType('C'));
    m.assign2(TestKeyType(12), TestKeyType(18), TestValueType('A'));
    m.print();
}
TEST_CASE("EmptyRange")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(3), TestKeyType(3), TestValueType('B'));
    REQUIRE(m.m_map.count(3) == 0);

    m.assign2(TestKeyType(3), TestKeyType(2), TestValueType('B'));
    REQUIRE(m.m_map.count(2) == 0);
    REQUIRE(m.m_map.count(3) == 0);
}

TEST_CASE("TrivialRange")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(1), TestKeyType(10), TestValueType('B'));
    m.print();
    REQUIRE(m[0] == TestValueType('A'));
    for (int i = 1; i < 10; i++)
    {
        REQUIRE(m[i] == 'B');
    }
    REQUIRE(m[10] == 'A');
}

TEST_CASE("TrivialTwoRange")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(1), TestKeyType(3), TestValueType('B'));
    m.assign2(TestKeyType(6), TestKeyType(8), TestValueType('C'));
    m.print();
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'A');
    REQUIRE(m[4] == 'A');
    REQUIRE(m[5] == 'A');
    REQUIRE(m[6] == 'C');
    REQUIRE(m[7] == 'C');
    REQUIRE(m[8] == 'A');
}

TEST_CASE("OverwriteLowest")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(std::numeric_limits<TestKeyType>::lowest(), TestKeyType(10000), TestValueType('B'));
    m.print();
    REQUIRE(m[0] == 'B');
    REQUIRE(m[9999] == 'B');
    REQUIRE(m[10000] == 'A');
}

TEST_CASE("Merge")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(-10), TestKeyType(10), TestValueType('B'));
    m.print();
    m.assign2(TestKeyType(10), TestKeyType(20), TestValueType('B'));
    m.print();
    REQUIRE(m[0] == 'B');
    REQUIRE(m[10] == 'B');
    REQUIRE(m[19] == 'B');
    REQUIRE(m[20] == 'A');
}

TEST_CASE("FloatKey")
{
    interval_map<TestFloatKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestFloatKeyType(1.f), TestFloatKeyType(5.f), TestValueType('B'));
    m.print();
    REQUIRE(m[0.f] == 'A');
    REQUIRE(m[.999999999f] == 'B');
    REQUIRE(m[1.f] == 'B');
    REQUIRE(m[4.999f] == 'B');
    REQUIRE(m[5.f] == 'A');

}

TEST_CASE("OverlappingRangeComplete")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(3), TestKeyType(5), TestValueType('B'));
    m.assign2(TestKeyType(1), TestKeyType(6), TestValueType('C'));
    m.print();
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'C');
    REQUIRE(m[2] == 'C');
    REQUIRE(m[3] == 'C');
    REQUIRE(m[4] == 'C');
    REQUIRE(m[5] == 'C');
    REQUIRE(m[6] == 'A');
}

TEST_CASE("OverlappingRangeInner")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(1), TestKeyType(6), TestValueType('C'));
    m.assign2(TestKeyType(3), TestKeyType(5), TestValueType('B'));
    m.print();
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'C');
    REQUIRE(m[2] == 'C');
    REQUIRE(m[3] == 'B');
    REQUIRE(m[4] == 'B');
    REQUIRE(m[5] == 'C');
    REQUIRE(m[6] == 'A');
}

TEST_CASE("OverlappingRangeSmallToLarge")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(1), TestKeyType(5), TestValueType('B'));
    m.assign2(TestKeyType(3), TestKeyType(6), TestValueType('C'));
    m.print();
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'C');
    REQUIRE(m[4] == 'C');
    REQUIRE(m[5] == 'C');
    REQUIRE(m[6] == 'A');
}

TEST_CASE("OverlappingRangeLargeToSmall")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(3), TestKeyType(6), TestValueType('C'));
    m.assign2(TestKeyType(1), TestKeyType(5), TestValueType('B'));
    m.print();
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'B');
    REQUIRE(m[4] == 'B');
    REQUIRE(m[5] == 'C');
    REQUIRE(m[6] == 'A');
}

TEST_CASE("ExtendingRangeBegin")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(3), TestKeyType(5), TestValueType('B'));
    m.assign2(TestKeyType(1), TestKeyType(4), TestValueType('B'));
    m.print();
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'B');
    REQUIRE(m[4] == 'B');
    REQUIRE(m[5] == 'A');
}

TEST_CASE("ExtendingRangeEnd")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(1), TestKeyType(5), TestValueType('B'));
    m.assign2(TestKeyType(3), TestKeyType(6), TestValueType('B'));
    m.print();
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'B');
    REQUIRE(m[4] == 'B');
    REQUIRE(m[5] == 'B');
    REQUIRE(m[6] == 'A');
}

TEST_CASE("ExtendingRangeBothBeginEnd")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(2), TestKeyType(3), TestValueType('B'));
    m.assign2(TestKeyType(1), TestKeyType(5), TestValueType('B'));
    m.print();
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'B');
    REQUIRE(m[4] == 'B');
    REQUIRE(m[5] == 'A');
}

TEST_CASE("OverwriteEndValueSafety")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(2), TestKeyType(5), TestValueType('B'));
    m.assign2(TestKeyType(5), TestKeyType(8), TestValueType('C'));
    m.assign2(TestKeyType(4), TestKeyType(5), TestValueType('A'));
    for(int i = 0; i < 10; i++) {
        if(i < 2) {
            REQUIRE(m[i] == 'A');
        } else if(i < 4) {
            REQUIRE(m[i] == 'B');
        } else if (i < 5) {
            REQUIRE(m[i] == 'A');
        } else if( i < 8) {
            REQUIRE(m[i] == 'C');
        } else {
            REQUIRE(m[i] == 'A');
        }
    }
    m.print();
}

TEST_CASE("ReusingExistingRangeBothBeginEnd")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(1), TestKeyType(5), TestValueType('B'));
    m.assign2(TestKeyType(2), TestKeyType(3), TestValueType('B'));
    m.print();
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'B');
    REQUIRE(m[4] == 'B');
    REQUIRE(m[5] == 'A');
}

TEST_CASE("ReusingEnd")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(1), TestKeyType(5), TestValueType('B'));
    m.assign2(TestKeyType(4), TestKeyType(6), TestValueType('A'));
    m.print();
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'B');
    REQUIRE(m[2] == 'B');
    REQUIRE(m[3] == 'B');
    REQUIRE(m[4] == 'A');
    REQUIRE(m[5] == 'A');
}

TEST_CASE("RestoringInitial")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(1), TestKeyType(5), TestValueType('B'));
    m.assign2(TestKeyType(1), TestKeyType(5), TestValueType('A'));
    m.print();
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'A');
    REQUIRE(m[2] == 'A');
    REQUIRE(m[3] == 'A');
    REQUIRE(m[4] == 'A');
    REQUIRE(m[5] == 'A');
}

TEST_CASE("RestoringInitial2")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(1), TestKeyType(5), TestValueType('B'));
    m.assign2(TestKeyType(0), TestKeyType(7), TestValueType('A'));
    m.print();
    REQUIRE(m[0] == 'A');
    REQUIRE(m[1] == 'A');
    REQUIRE(m[2] == 'A');
    REQUIRE(m[3] == 'A');
    REQUIRE(m[4] == 'A');
    REQUIRE(m[5] == 'A');
}

TEST_CASE("VeryComplex")
{
    interval_map<TestKeyType, TestValueType> m(TestValueType('A'));
    m.assign2(TestKeyType(3), TestKeyType(6), TestValueType('B'));
    m.assign2(TestKeyType(2), TestKeyType(5), TestValueType('C'));
    m.assign2(TestKeyType(4), TestKeyType(7), TestValueType('A'));
    m.print();
    REQUIRE(m[1] == 'A');
    REQUIRE(m[2] == 'C');
    REQUIRE(m[3] == 'C');
    REQUIRE(m[4] == 'A');
    REQUIRE(m[5] == 'A');
    REQUIRE(m[6] == 'A');
    REQUIRE(m[7] == 'A');
}
