#include <gtest/gtest.h>
#include "../../src/general.hpp"

// ? Inspiration https://www.sandordargo.com/blog/2019/04/24/parameterized-testing-with-gtest

// Fixtured tests
class CorrectPathFixtureTest :public ::testing::Test {
protected:
    std::string input;
};

TEST(CorrectPathFixtureTest, EmptyString_ShouldBeEqual) {
    EXPECT_EQ("",correct_path(""));
    EXPECT_EQ(std::string(),correct_path(std::string()));
	EXPECT_EQ("42",correct_path("42"));
}

TEST(CorrectPathFixtureTest, SingleBackLash_ShouldNotBeEqual) {
    EXPECT_NE("/",correct_path("/"));
}

// Parameterized tests
class CorrectPathMultipleParametersTests :public ::testing::TestWithParam<std::tuple<std::string, bool>> {
protected:
    std::string corrected_input = correct_path(std::get<0>(GetParam()));
};

TEST_P(CorrectPathMultipleParametersTests, ChecksIfPathIsCorrected) {
	std::string input  = std::get<0>(GetParam());
	bool isEqual = std::get<1>(GetParam());
	if (isEqual)
		EXPECT_EQ(input, corrected_input);
	else
		EXPECT_NE(input, corrected_input);
}

INSTANTIATE_TEST_SUITE_P(
	CorrectPathTests,
	CorrectPathMultipleParametersTests,
	::testing::Values(
		std::make_tuple("holamundo",true),
		std::make_tuple("hola/mundo",true),
		std::make_tuple("hola.mundo",true),
		std::make_tuple("hola~mundo",true),
		std::make_tuple("hola..mundo",true),
		std::make_tuple("hola//mundo",false),

		std::make_tuple("/holamundo",false),
		std::make_tuple("~/holamundo",false),
		std::make_tuple("//holamundo",false),
		std::make_tuple("./holamundo",false),
		std::make_tuple("../holamundo",false),

		std::make_tuple("holamundo/",false),
		std::make_tuple("holamundo/~",false),
		std::make_tuple("holamundo//",false),
		std::make_tuple("holamundo/.",false),
		std::make_tuple("holamundo/..",false),

		std::make_tuple("hola./mundo",true),
		std::make_tuple("hola/.mundo",true),
		std::make_tuple("hola../mundo",true),
		std::make_tuple("hola/..mundo",true),
		std::make_tuple("hola~/mundo",true),
		std::make_tuple("hola/~mundo",true),

		std::make_tuple("hola/./mundo",false),
		std::make_tuple("hola/../mundo",false),
		std::make_tuple("hola/~/mundo",false)
	)
);

