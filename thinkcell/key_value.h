#include <numeric>
#include <limits>
#include <iostream>

// #define NO_USE_PRINT

#ifdef NO_USE_PRINT

struct TestValueType {
    char ch;
    TestValueType() = delete;
    TestValueType(char ch) : ch(ch) {}
    constexpr bool operator==(TestValueType const& other) const {
        return other.ch == ch;
    }
    friend std::ostream& operator<< (std::ostream& stream, const TestValueType& val) {
        stream << val;
        return stream;
    }
};

struct TestKeyType
{
    int val;
    TestKeyType() = delete;
    TestKeyType(int val) : val(val) {}
    constexpr bool operator<(const TestKeyType& other) const { return val < other.val; }
    friend std::ostream& operator<< (std::ostream& stream, const TestKeyType& key) {
        stream << key;
        return stream;
    }
};

struct TestFloatKeyType
{
    float val;

    // explicit TestFloatKeyType() = default;
    TestFloatKeyType() = delete;
    TestFloatKeyType(float val) : val(val) {}
    bool operator< (TestFloatKeyType other) const
    {
        return other.val - val > 1.e-4f;
    }
    friend std::ostream& operator<< (std::ostream& stream, const TestFloatKeyType& key) {
        stream << key; 
        return stream;
    }
};

namespace std {
    template<> class numeric_limits<TestKeyType> {
    public:
        // static constexpr TestKeyType lowest() { return TestKeyType(numeric_limits<int>::lowest()); }
        static TestKeyType lowest() { return TestKeyType(-250); }
    };
}

namespace std {
    template<> class numeric_limits<TestFloatKeyType> {
    public:
        static TestFloatKeyType lowest() { return TestFloatKeyType(numeric_limits<float>::lowest()); }
    };
}

#else
using TestKeyType = int;
using TestFloatKeyType = float;
using TestValueType = char;
#endif
