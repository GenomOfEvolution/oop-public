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
        // проверить что массивы одинаковые
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

        auto it = arr.begin();
        REQUIRE(it != arr.end());

        auto rit = arr.rbegin();
        REQUIRE(rit != arr.rend());

        // range based for end++ begin-- *end
    }
}