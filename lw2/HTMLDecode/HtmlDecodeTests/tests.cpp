#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <HtmlDecode.h>

//вынести все в отдельные строки

TEST_CASE("Проверить декодирование пустой строки")
{
	REQUIRE(HtmlDecode("") == "");
}

TEST_CASE("Некорректная html-сущность")
{
	REQUIRE(HtmlDecode("&lp;Cat") == "&lp;Cat");
}

TEST_CASE("Множество строк")
{
	REQUIRE(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s\nMy name is &quot;Heisenberg&quot;") == 
		"Cat <says> \"Meow\". M&M's\nMy name is \"Heisenberg\"");
}

TEST_CASE("Текст без html-сущностей")
{
	REQUIRE(HtmlDecode("Hello") == "Hello");
}

TEST_CASE("Проверить декодирование всех html-сущностей")
{
	REQUIRE(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s") == "Cat <says> \"Meow\". M&M's");
}
