#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <CHttpUrl.h>
#include <CUrlParsingError.h>

namespace
{
	constexpr unsigned short DEFAULT_HTTP_PORT = 80;
	constexpr unsigned short DEFAULT_HTTPS_PORT = 443;
	constexpr unsigned short MAX_PORT = 65535;
	constexpr unsigned short MIN_PORT = 1;
}

TEST_CASE("Valid URL single string constructor")
{
	REQUIRE_NOTHROW(CHttpUrl("https://github.com/alexey-malov/oop/tree/master/tasks/06"));

	CHttpUrl url("https://github.com/alexey-malov/oop/tree/master/tasks/06");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetPort() == DEFAULT_HTTPS_PORT);
	CHECK(url.GetDomain() == "github.com");
	CHECK(url.GetDocument() == "/alexey-malov/oop/tree/master/tasks/06");
	CHECK(url.GetURL() == "https://github.com/alexey-malov/oop/tree/master/tasks/06");
}

TEST_CASE("Valid URL not string constructor")
{
	REQUIRE_NOTHROW(CHttpUrl("example.com", "/CoolDocument/"));
	CHttpUrl url1("example.com", "/CoolDocument.html/");

	CHECK(url1.GetDocument() == "/CoolDocument.html/");
	CHECK(url1.GetDomain() == "example.com");
	CHECK(url1.GetPort() == DEFAULT_HTTP_PORT);
	CHECK(url1.GetProtocol() == Protocol::HTTP);
	CHECK(url1.GetURL() == "http://example.com/CoolDocument.html/");
	
	REQUIRE_NOTHROW(CHttpUrl("example.com", "/CoolDocument/", Protocol::HTTPS, 8127));
	CHttpUrl url2("example.com", "/CoolDocument.html/", Protocol::HTTPS, 8127);

	CHECK(url2.GetDocument() == "/CoolDocument.html/");
	CHECK(url2.GetDomain() == "example.com");
	CHECK(url2.GetPort() == 8127);
	CHECK(url2.GetProtocol() == Protocol::HTTPS);
	CHECK(url2.GetURL() == "https://example.com:8127/CoolDocument.html/");
}

TEST_CASE("Constructor not with string throws std::invalid_argument")
{
	CHECK_THROWS_AS(CHttpUrl("", "/CoolDocument.txt", Protocol::HTTPS), std::invalid_argument);
	CHECK_THROWS_AS(CHttpUrl("", "/CoolDocument.txt", Protocol::HTTP, 228), std::invalid_argument);
	CHECK_THROWS_AS(CHttpUrl("Example.com", "/CoolDocument.txt", Protocol::HTTP, 0), std::invalid_argument);
}

TEST_CASE("Different case protocol is Valid URL")
{
	REQUIRE_NOTHROW(CHttpUrl("HTtPs://github.com/alexey-malov/oop/"));
	CHttpUrl url1("HTtPs://github.com/alexey-malov/oop/");
	CHECK(url1.GetProtocol() == Protocol::HTTPS);

	REQUIRE_NOTHROW(CHttpUrl("HttP://github.com/alexey-malov/oop/"));
	CHttpUrl url2("HttP://github.com/alexey-malov/oop/");
	CHECK(url2.GetProtocol() == Protocol::HTTP);
}

TEST_CASE("Default port must be not included")
{
	CHttpUrl url1("https://github.com:443/alexey-malov/oop/");
	CHECK(url1.GetURL() == "https://github.com/alexey-malov/oop/");

	CHttpUrl url2("http://github.com:80/alexey-malov/oop/");
	CHECK(url2.GetURL() == "http://github.com/alexey-malov/oop/");
}

TEST_CASE("Port borders")
{
	CHECK_NOTHROW(CHttpUrl("https://github.com:1/alexey-malov/"));
	CHttpUrl urlMinPort("https://github.com:1/alexey-malov/");
	CHECK(urlMinPort.GetPort() == MIN_PORT);

	CHECK_NOTHROW(CHttpUrl("https://github.com:65535/alexey-malov/"));
	CHttpUrl urlMaxPort("https://github.com:65535/alexey-malov/");
	CHECK(urlMaxPort.GetPort() == MAX_PORT);

	CHECK_THROWS_AS(CHttpUrl("https://github.com:0/alexey-malov/"), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl("https://github.com:65536/alexey-malov/"), CUrlParsingError);
}

TEST_CASE("Document name must start with /")
{
	CHttpUrl url("https://example.com");
	CHECK(url.GetURL() == "https://example.com/");
	CHECK(url.GetDocument() == "/");
}

TEST_CASE("Invalid protocol")
{
	CHECK_THROWS_AS(CHttpUrl("ftp://example.com"), CUrlParsingError);
}

TEST_CASE("Empty URL")
{
	CHECK_THROWS_AS(CHttpUrl(""), CUrlParsingError);
}

// TODO: invalid document or domain
TEST_CASE("Invalid domain")
{
	CHECK_THROWS_AS(CHttpUrl("https://github/oop"), CUrlParsingError);
}

TEST_CASE("Invalid document symbol")
{
	CHECK_THROWS_AS(CHttpUrl("https://github.com/oop   _6"), CUrlParsingError);
}

TEST_CASE("Constructor with protocol (auto port)")
{
	CHECK_THROWS_AS(CHttpUrl("", "/", Protocol::HTTP), std::invalid_argument);
	CHECK_THROWS_AS(CHttpUrl("invalid_domain", "/", Protocol::HTTPS), std::invalid_argument);
	CHECK_THROWS_AS(CHttpUrl("example.com", "no_leading_slash", Protocol::HTTP), std::invalid_argument);
}