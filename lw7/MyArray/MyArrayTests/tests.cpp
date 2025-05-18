#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <CArray.h>

TEMPLATE_TEST_CASE("CArray functionality tests", "[CArray][template]", std::string, float) 
{
    SECTION("Push and size operations") 
    {
        CArray<TestType> arr;
        REQUIRE(arr.Size() == 0);

        TestType val1{};
        arr.Push(val1);
        REQUIRE(arr.Size() == 1);

        TestType val2{};
        arr.Push(val2);
        REQUIRE(arr.Size() == 2);

        TestType val3{};
        arr.Push(val3);
        REQUIRE(arr.Size() == 3);
        REQUIRE(arr.Capacity() >= 3); 
    }

    SECTION("Resize operation") 
    {
        CArray<TestType> arr;
        arr.Resize(10);
        REQUIRE(arr.Capacity() >= 10);
    }

    SECTION("Clear operation") 
    {
        CArray<TestType> arr;
        TestType val1{};
        TestType val2{};
        arr.Push(val1);
        arr.Push(val2);
        REQUIRE(arr.Size() == 2);

        arr.Clear();
        REQUIRE(arr.Size() == 0);
    }

    SECTION("Element access") 
    {
        CArray<TestType> arr;
        TestType value{};
        arr.Push(value);

        REQUIRE(arr[0] == value);
        REQUIRE_THROWS_AS(arr[1], std::out_of_range);
    }

    SECTION("Copy constructor") 
    {
        CArray<TestType> arr1;
        TestType val1{};
        TestType val2{};
        arr1.Push(val1);
        arr1.Push(val2);

        CArray<TestType> arr2(arr1);
        REQUIRE(arr2.Size() == arr1.Size());
        // TODO: проверить что массивы одинаковые
        for (size_t i = 0; i < arr1.Size(); ++i)
        {
            CHECK(arr1[i] == arr2[i]);
        }
    }

    SECTION("Move constructor") 
    {
        CArray<TestType> arr1;
        TestType val1{};
        TestType val2{};
        arr1.Push(val1);
        arr1.Push(val2);

        CArray<TestType> arr2(std::move(arr1));
        REQUIRE(arr2.Size() == 2);
        REQUIRE(arr1.Size() == 0);
    }

    SECTION("Copy assignment") 
    {
        CArray<TestType> arr1;
        TestType val1{};
        TestType val2{};
        arr1.Push(val1);
        arr1.Push(val2);

        CArray<TestType> arr2;
        arr2 = arr1;
        REQUIRE(arr2.Size() == arr1.Size());
    }

    SECTION("Move assignment") 
    {
        CArray<TestType> arr1;
        TestType val1{};
        TestType val2{};
        arr1.Push(val1);
        arr1.Push(val2);

        CArray<TestType> arr2;
        arr2 = std::move(arr1);
        REQUIRE(arr2.Size() == 2);
        REQUIRE(arr1.Size() == 0);
    }

    SECTION("Iterator functionality")
    {
        CArray<TestType> arr;
        TestType val1{};
        TestType val2{};
        arr.Push(val1);
        arr.Push(val2);

        // TODO: range based for end++ begin-- *end
        auto it = arr.begin();
        REQUIRE(it != arr.end());
        REQUIRE(*it == val1);
        ++it;
        REQUIRE(*it == val2);
        ++it;
        REQUIRE(it == arr.end());

        auto rit = arr.rbegin();
        REQUIRE(rit != arr.rend());
        REQUIRE(*rit == val2);
        ++rit;
        REQUIRE(*rit == val1);
        ++rit;
        REQUIRE(rit == arr.rend());

        size_t count = 0;
        for (const auto& item : arr) 
        {
            ++count;
            REQUIRE((item == val1 || item == val2));
        }
        REQUIRE(count == 2);

        auto end_it = arr.end();
        --end_it;
        REQUIRE(*end_it == val2);
        --end_it;
        REQUIRE(*end_it == val1);
        REQUIRE(end_it == arr.begin());

        REQUIRE(arr.end() - arr.begin() == 2);
        REQUIRE(arr.begin() + 2 == arr.end());
        REQUIRE(arr.end() - 2 == arr.begin());

        REQUIRE(arr.begin()[0] == val1);
        REQUIRE(arr.begin()[1] == val2);
    }
}