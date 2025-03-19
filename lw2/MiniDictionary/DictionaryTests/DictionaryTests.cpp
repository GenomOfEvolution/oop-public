#define CATCH_CONFIG_MAIN
#include <DictionaryLogic.h>
#include <catch.hpp>

TEST_CASE("FindTranslations finds and formats translations correctly") 
{
    Dictionary dict = { {"яблоко", "apple"}, {"яблоко", "pomme"}, {"книга", "book"} };

    auto translations = FindTranslations(dict, "яблоко");
    REQUIRE(translations.has_value());          
    REQUIRE(*translations == "apple, pomme");    

    auto noTranslations = FindTranslations(dict, "машина");
    REQUIRE(!noTranslations.has_value());           
}

TEST_CASE("AddTranslation adds translations to both dictionaries") 
{
    Dictionary ruToEn, enToRu;

    AddTranslation(ruToEn, enToRu, "машина", "car");

    auto carRange = ruToEn.equal_range("машина");
    REQUIRE(carRange.first != carRange.second);     
    REQUIRE(carRange.first->second == "car");     

    auto машинаRange = enToRu.equal_range("car");
    REQUIRE(машинаRange.first != машинаRange.second);
    REQUIRE(машинаRange.first->second == "машина");

    AddTranslation(ruToEn, enToRu, "машина", "auto");
    auto carRange2 = ruToEn.equal_range("машина");
    int count = 0;
    for (auto it = carRange2.first; it != carRange2.second; ++it) 
    {
        count++;
    }

    REQUIRE(count == 2);                           
}