#include "operation.h"
#include <gtest.h>

TEST(operation_Constructors, Constructor_initializer)
{
	ASSERT_NO_THROW(operation o("+", 5, nullptr, 2));
	operation o("+", 5, nullptr, 2);
	EXPECT_EQ(o.getName(), "+");
	EXPECT_EQ(o.getPriority(), 5);
	EXPECT_TRUE(o.getType());
	EXPECT_EQ(o.get_koll_of_operands(), 2);
}

TEST(operation_Constructors, Constructor_copy)
{
	operation o("+", 5, nullptr, 2);
	ASSERT_NO_THROW(operation t(o));
	operation t(o);
	EXPECT_EQ(t.getName(), "+");
	EXPECT_EQ(t.getPriority(), 5);
	EXPECT_TRUE(t.getType());
	EXPECT_EQ(t.get_koll_of_operands(), 2);
}

TEST(operation_Methods, getType_is_works)
{
	operation o("+", 5, nullptr, 2);
	EXPECT_TRUE(o.getType());
}

TEST(operation_Methods, get_koll_of_operands_is_works)
{
	operation o("+", 5, nullptr, 2);
	EXPECT_EQ(o.get_koll_of_operands(), 2);
}

TEST(operation_Methods, getPriority_is_works)
{
	operation o("+", 5, nullptr, 2);
	EXPECT_EQ(o.getPriority(), 5);
}

TEST(operation_Methods, setPriority_is_works)
{
	operation o("+", 5, nullptr, 2);
	o.setPriority(2);
	EXPECT_EQ(o.getPriority(), 2);
}

TEST(operation_Methods, getName_is_works)
{
	operation o("+", 5, nullptr, 2);
	EXPECT_EQ(o.getName(), "+");
}

TEST(operation_Methods, setName_is_works)
{
	operation o("+", 5, nullptr, 2);
	o.setName("-");
	EXPECT_EQ(o.getName(), "-");
}


double funk(double a, double b) { return a + b; }

TEST(operation_Methods, operation_as_function_is_works)
{
	operation o("+", 5, funk, 2);
	EXPECT_EQ(o(5, 6), 11);
}