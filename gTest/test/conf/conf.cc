#include <gtest/gtest.h>
#include "../../../src/conf/conf.hpp"
#include <memory>

/**
// ? Parameterized test https://www.sandordargo.com/blog/2019/04/24/parameterized-testing-with-gtest
// ? Private classes test: How should be used, not like this (making public in testing purposes)
 * https://stackoverflow.com/questions/47354280/what-is-the-best-way-of-testing-private-methods-with-googletest
 * https://www.gamedev.net/articles/programming/general-and-gameplay-programming/the-c-pimpl-r1794/
*/

struct ConfTest: testing::Test
{
	ft::conf	*conf;
	ConfTest()
	{
		conf = new ft::conf();
	}
	virtual ~ConfTest()
	{
		delete conf;
	}
};

struct sample_path
{
	std::string path;
	bool expected;
};

struct ValidPathMultipleParametersTests :ConfTest, testing::WithParamInterface<sample_path> {
	protected:
	const bool	is_valid = conf->_valid_path( GetParam().path );

	ValidPathMultipleParametersTests() {}
	~ValidPathMultipleParametersTests() {}
};

TEST_P(ValidPathMultipleParametersTests, ChecksIfPathIsCorrected) {
	EXPECT_EQ(is_valid, GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(
	ValidPathTests,
	ValidPathMultipleParametersTests,
	::testing::Values(
		sample_path{"",false},
		sample_path{"/",true},
		sample_path{"/tmp",true},
		sample_path{"/tmp/www",true},
		sample_path{"tmp/www",false},

		// invaid charset
		sample_path{"/tmp//www",false},
		sample_path{"/tmp/./www",false},
		sample_path{"/tmp/~/www",false},
		sample_path{"/tmp/../www",false},

		// invalid ending
		sample_path{"/tmp/www/",false},
		sample_path{"/tmp/www/.",false},
		sample_path{"/tmp/www/~",false},
		sample_path{"/tmp/www/..",false},
		sample_path{"/tmp/www/..",false},
		sample_path{"/tmp/www{",false},
		sample_path{"/tmp/www {",false}
	)
);

struct sample_redirect
{
	std::string redirect;
	bool expected;
};

struct ValidRedirectMultipleParametersTests :ConfTest, testing::WithParamInterface<sample_redirect> {
	protected:
	const bool	is_valid = conf->_valid_redirect_url( GetParam().redirect );

	ValidRedirectMultipleParametersTests() {}
	~ValidRedirectMultipleParametersTests() {}
};

TEST_P(ValidRedirectMultipleParametersTests, ChecksIfRedirectIsCorrected) {
	EXPECT_EQ(is_valid, GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(
	ValidRedirectTests,
	ValidRedirectMultipleParametersTests,
	::testing::Values(

		sample_redirect{"http://",true},
		sample_redirect{"https://",true},
		sample_redirect{"ahttp://",false},
		sample_redirect{"ahttps://",false},
		sample_redirect{"",false},
		sample_redirect{"/",true},
		sample_redirect{"/tmp",true},
		sample_redirect{"/tmp/www",true},
		sample_redirect{"tmp/www",false},

		// invaid charset
		sample_redirect{"/tmp//www",false},
		sample_redirect{"/tmp/./www",false},
		sample_redirect{"/tmp/~/www",false},
		sample_redirect{"/tmp/../www",false},

		// invalid ending
		sample_redirect{"/tmp/www/",false},
		sample_redirect{"/tmp/www/.",false},
		sample_redirect{"/tmp/www/~",false},
		sample_redirect{"/tmp/www/..",false},
		sample_redirect{"/tmp/www/..",false},
		sample_redirect{"/tmp/www{",false},
		sample_redirect{"/tmp/www {",false}
	)
);

struct ParseRedirectFixtureTests: testing::Test {
protected:
	ft::conf		*conf;
	ft::serverconf	*serverconf;
    ft::location	*location;
	ParseRedirectFixtureTests()
	{
		conf = new ft::conf();
		serverconf = new ft::serverconf(NULL);
		location = new ft::location();
		conf->_set_location_defaults(location);
		location->request_path = "pathA";
		conf->_parse_redirect("301 /pathB", location, *serverconf);
		serverconf->locations.insert(std::make_pair(location->request_path, *location));
		conf->_set_location_defaults(location);
		location->request_path = "pathB";
		conf->_parse_redirect("301 /pathC", location, *serverconf);
		serverconf->locations.insert(std::make_pair(location->request_path, *location));
		conf->_set_location_defaults(location);
		location->request_path = "pathC";
		conf->_parse_redirect("301 /pathA", location, *serverconf);
		serverconf->locations.insert(std::make_pair(location->request_path, *location));
	}
	~ParseRedirectFixtureTests()
	{
		delete location;
		if (serverconf->locations.size())
			serverconf->locations.clear();
		delete serverconf;
		delete conf;
	}

};

TEST_F(ParseRedirectFixtureTests, CheckIfRedirectCantLoop) {
    EXPECT_EQ(serverconf->locations["pathA"].redirect.second, "pathB" );
    EXPECT_EQ(serverconf->locations["pathB"].redirect.second, "pathC" );
    EXPECT_NE(serverconf->locations["pathC"].redirect.second, "pathA" );
    EXPECT_EQ(serverconf->locations["pathC"].redirect.second, "" );
}

struct sample_methods
{
	std::string methods;
	int 		expected;
};

enum e_accepted_mock_methods
{  MOCK_GET = 0x1, MOCK_POST = 0x2, MOCK_DELETE = 0x4 };


struct ParseMethodsHasPermissionMultipleParametersTests :ConfTest, testing::WithParamInterface<sample_methods> {
	protected:
	ft::location *some_location;

	ParseMethodsHasPermissionMultipleParametersTests(){
		some_location = new ft::location();
		conf->_set_location_defaults(some_location);
		conf->_parse_methods( GetParam().methods, some_location );
	}
	~ParseMethodsHasPermissionMultipleParametersTests() {
		delete some_location;
	}
};

TEST_P(ParseMethodsHasPermissionMultipleParametersTests, CheckHasPermisions) {
	EXPECT_EQ(some_location->methods & GetParam().expected, GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(
	ParseMethodsTests,
	ParseMethodsHasPermissionMultipleParametersTests,
	::testing::Values(
		sample_methods{"GET", MOCK_GET},
		sample_methods{"POST", MOCK_POST},
		sample_methods{"DELETE", MOCK_DELETE},
		sample_methods{"GET POST", MOCK_GET},
		sample_methods{"GET POST", MOCK_POST},
		sample_methods{"DELETE GET", MOCK_DELETE},
		sample_methods{"DELETE GET", MOCK_GET},
		sample_methods{"DELETE POST GET", MOCK_DELETE},
		sample_methods{"DELETE POST GET", MOCK_POST},
		sample_methods{"DELETE POST GET", MOCK_GET}
	)
);

struct ParseMethodsHasNotPermissionMultipleParametersTests :ConfTest, testing::WithParamInterface<sample_methods> {
	protected:
	ft::location *some_location;

	ParseMethodsHasNotPermissionMultipleParametersTests(){
		some_location = new ft::location();
		conf->_set_location_defaults(some_location);
		conf->_parse_methods( GetParam().methods, some_location );
	}
	~ParseMethodsHasNotPermissionMultipleParametersTests() {
		delete some_location;
	}
};


TEST_P(ParseMethodsHasNotPermissionMultipleParametersTests, CheckHasNotPermisions) {
	EXPECT_NE(some_location->methods & GetParam().expected, GetParam().expected);
}
INSTANTIATE_TEST_SUITE_P(
	ParseMethodsTests,
	ParseMethodsHasNotPermissionMultipleParametersTests,
	::testing::Values(
		sample_methods{"", MOCK_GET},
		sample_methods{"", MOCK_POST},
		sample_methods{"", MOCK_DELETE},
		sample_methods{"GET", MOCK_POST},
		sample_methods{"POST", MOCK_DELETE},
		sample_methods{"DELETE", MOCK_GET},

		sample_methods{"GET POST", MOCK_DELETE},
		sample_methods{"DELETE GET", MOCK_POST},
		sample_methods{"POST DELETE", MOCK_GET}
	)
);


struct ParseMethodsThrowUnknownMultipleParametersTests :ConfTest, testing::WithParamInterface<std::string> {
	protected:
	ft::location *some_location;

	ParseMethodsThrowUnknownMultipleParametersTests(){
		some_location = new ft::location();
		conf->_set_location_defaults(some_location);
	}
	~ParseMethodsThrowUnknownMultipleParametersTests() {
		delete some_location;
	}
};


TEST_P(ParseMethodsThrowUnknownMultipleParametersTests, CheckHasNotPermisions) {
	EXPECT_THROW(conf->_parse_methods( GetParam(), some_location ), std::invalid_argument);
}
INSTANTIATE_TEST_SUITE_P(
	ParseMethodsTests,
	ParseMethodsThrowUnknownMultipleParametersTests,
	::testing::Values(
		std::string("HOLA"),
		std::string("GET HOLA"),
		std::string("HOLA POST"),
		std::string("POST DELETE HOLA")
	)
);
