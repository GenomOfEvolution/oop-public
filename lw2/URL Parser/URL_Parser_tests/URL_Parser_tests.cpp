#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <URL_Parser.h>
#include <string>

Protocol protocol;
int port;
std::string url, host, document;

TEST_CASE("Empty URL")
{
	url = "";
	bool result = ParseURL(url, protocol, port, host, document);
	REQUIRE(!result);
}

TEST_CASE("Incorrect protocol")
{
	url = "htps://example.com/";
	bool result = ParseURL(url, protocol, port, host, document);
	REQUIRE(!result);
}

TEST_CASE("Incorrect ://")
{
	url = "http:/example.com/";
	bool result = ParseURL(url, protocol, port, host, document);
	REQUIRE(!result);
}

TEST_CASE("No host")
{
	url = "https://:8080/";
	bool result = ParseURL(url, protocol, port, host, document);
	REQUIRE(!result);
}

TEST_CASE("Port out of range")
{
	url = "https://localhost:123456/";
	bool result = ParseURL(url, protocol, port, host, document);
	REQUIRE(!result);
}

TEST_CASE("Correct url")
{
	url = "https://example.com/docs/doc.txt";
	bool result = ParseURL(url, protocol, port, host, document);
	REQUIRE(result);
	REQUIRE(protocol == Protocol::HTTPS);
	REQUIRE(port == 443);
	REQUIRE(host == "example.com");
	REQUIRE(document == "docs/doc.txt");
}

TEST_CASE("Lw example")
{
	url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	bool result = ParseURL(url, protocol, port, host, document);
	REQUIRE(result);
	REQUIRE(protocol == Protocol::HTTP);
	REQUIRE(port == 80);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}