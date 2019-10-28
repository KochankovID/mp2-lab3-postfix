#include "variable.h"
#include <gtest.h>

TEST(variable_Constructors, Constructor_initializer)
{
	ASSERT_NO_THROW(variable o("x", 5));
	variable o("x", 5);
	EXPECT_EQ(o.getName(), "x");
	EXPECT_FALSE(o.getType());
	EXPECT_EQ(o.getValue(), 5);
}

TEST(variable_Constructors, Constructor_copy)
{
	variable o("x", 5);
	ASSERT_NO_THROW(variable t(o));
	variable t(o);
	EXPECT_EQ(o.getName(), "x");
	EXPECT_FALSE(o.getType());
	EXPECT_EQ(o.getValue(), 5);
}

TEST(variable_Methods, getType_is_works)
{
	variable o("x", 5);
	EXPECT_FALSE(o.getType());
}

TEST(variable_Methods, getValue_is_works)
{
	variable o("x", 5);
	EXPECT_EQ(o.getValue(), 5);
}

TEST(variable_Methods, setValue_is_works)
{
	variable o("x", 5);
	ASSERT_NO_THROW(o.setValue(6));
	EXPECT_EQ(o.getValue(), 6);
}

TEST(variable_Methods, getName_is_works)
{
	variable o("x", 5);
	EXPECT_EQ(o.getName(), "x");
}

TEST(variable_Methods, setName_is_works)
{
	variable o("x", 5);
	o.setName("y");
	EXPECT_EQ(o.getName(), "y");
}
