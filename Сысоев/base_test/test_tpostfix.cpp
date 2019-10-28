#include "postfix.h"
#include <gtest.h>

TEST(TPostfix_constructors, Constructor_initializer)
{
	ASSERT_NO_THROW(TPostfix s("1+1"));
	TPostfix s("1+1");
	EXPECT_EQ(s.GetInfix(), "1+1");
}

TEST(TPostfix_Methods, GetInfix_works)
{
	TPostfix s("1+1");
	EXPECT_EQ(s.GetInfix(), "1+1");
}

TEST(TPostfix_Methods, isCorrectBrakets)
{
	TPostfix s("(())");
	ASSERT_NO_THROW(s.GetPostfix());

	TPostfix s1("(()");
	EXPECT_ANY_THROW(s1.GetPostfix());

	TPostfix s2("())");
	EXPECT_ANY_THROW(s2.GetPostfix());

	TPostfix s3(")(");
	EXPECT_ANY_THROW(s3.GetPostfix());
}

TEST(TPostfix_Methods, GetPostfix_works)
{
	TPostfix s("1+1");
	EXPECT_EQ(s.GetPostfix(), "1 1+");

	TPostfix s1("(1+1) * 4");
	EXPECT_EQ(s1.GetPostfix(), "1 1+4*");

	TPostfix s2("1+1 * 4");
	EXPECT_EQ(s2.GetPostfix(), "1 1 4*+");

	TPostfix s3("6/2*3");
	EXPECT_EQ(s3.GetPostfix(), "6 2/3*");

	TPostfix s4("sin(15) - 10");
	EXPECT_EQ(s4.GetPostfix(), "15sin10-");

	TPostfix s5("1 - 1 * (5 +9 - (++8))");
	EXPECT_EQ(s5.GetPostfix(), "1 1 5 9+8++-*-");

	TPostfix s6("(ln100 + 6*(10/4))");
	EXPECT_EQ(s6.GetPostfix(), "100ln6 10 4/*+");
	TPostfix s7("9/3/4/5/6/20-30-303-40");
	EXPECT_EQ(s7.GetPostfix(), "9 3/4/5/6/20/30-303-40-");
}

TEST(TPostfix_Methods, Calculate_works)
{
	TPostfix s("1+1");
	EXPECT_EQ(s.Calculate(), 2);

	TPostfix s1("(1+1) * 4");
	EXPECT_EQ(s1.Calculate(), 8);

	TPostfix s2("1+1 * 4");
	EXPECT_EQ(s2.Calculate(), 5);

	TPostfix s3("6/2*3");
	EXPECT_EQ(s3.Calculate(), 9);

	TPostfix s4("sin(15) - 10");
	EXPECT_FLOAT_EQ(s4.Calculate(), -9.3497124);

	TPostfix s5("1 - 1 * (5 +9 - (++8))");
	EXPECT_EQ(s5.Calculate(), -4);

	TPostfix s6("(ln100 + 6*(10/4))");
	EXPECT_FLOAT_EQ(s6.Calculate(), 19.605169);

	TPostfix s7("9/3/4/5/6/20-30-303-40");
	EXPECT_FLOAT_EQ(s7.Calculate(), -372.99875);
}

TEST(TPostfix_Methods, Tests_from_the_manual)
{
	TPostfix s("1+2");
	ASSERT_NO_THROW(s.GetPostfix());
	EXPECT_EQ(s.GetPostfix(), "1 2+");
	EXPECT_EQ(s.Calculate(), 3);

	TPostfix s1("1+2*(3-2)-4");
	ASSERT_NO_THROW(s1.GetPostfix());
	EXPECT_EQ(s1.GetPostfix(), "1 2 3 2-*+4-");
	EXPECT_EQ(s1.Calculate(), -1);

	TPostfix s2("(((1+23)*1-22)+5)*2-(7");
	ASSERT_ANY_THROW(s2.GetPostfix());

	TPostfix s3("1+2/(3-3)");
	ASSERT_NO_THROW(s3.GetPostfix());
	EXPECT_EQ(s3.GetPostfix(), "1 2 3 3-/+");
	ASSERT_ANY_THROW(s3.Calculate());

	TPostfix s4("1+2+");
	ASSERT_ANY_THROW(s4.Calculate());
}




