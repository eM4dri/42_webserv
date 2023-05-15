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
	const bool	is_valid = conf->valid_path( GetParam().path );

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
	const bool	is_valid = conf->valid_redirect( GetParam().redirect );

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

