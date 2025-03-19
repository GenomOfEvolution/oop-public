#define CATCH_CONFIG_MAIN
#include <DictionaryLogic.h>
#include <catch.hpp>

TEST_CASE("FindTranslations finds and formats translations correctly") 
{
    Dictionary dict = { {"������", "apple"}, {"������", "pomme"}, {"�����", "book"} };

    auto translations = FindTranslations(dict, "������");
    REQUIRE(translations.has_value());          
    REQUIRE(*translations == "apple, pomme");    

    auto noTranslations = FindTranslations(dict, "������");
    REQUIRE(!noTranslations.has_value());           
}

TEST_CASE("AddTranslation adds translations to both dictionaries") 
{
    Dictionary ruToEn, enToRu;

    AddTranslation(ruToEn, enToRu, "������", "car");

    auto carRange = ruToEn.equal_range("������");
    REQUIRE(carRange.first != carRange.second);     
    REQUIRE(carRange.first->second == "car");     

    auto ������Range = enToRu.equal_range("car");
    REQUIRE(������Range.first != ������Range.second);
    REQUIRE(������Range.first->second == "������");

    AddTranslation(ruToEn, enToRu, "������", "auto");
    auto carRange2 = ruToEn.equal_range("������");
    int count = 0;
    for (auto it = carRange2.first; it != carRange2.second; ++it) 
    {
        count++;
    }

    REQUIRE(count == 2);                           
}