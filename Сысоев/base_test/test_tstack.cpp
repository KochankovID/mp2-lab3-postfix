#include "stack.h"
#include <gtest.h>

TEST(TStack_Constructors, Constructor_dy_default)
{
	ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack_Constructors, Constructor_Copy)
{
	TStack<double> y;
	y.push(6.66);
	ASSERT_NO_THROW(TStack<double> s(y));
	TStack<double> s(y);
	EXPECT_EQ(s.pop(), 6.66);
	EXPECT_TRUE(s.isEmpty());
}

TEST(TStack_Methods, The_isFull_works)
{
	TStack<int> s;
	for (int i = 0; i < 100; i++) {
		s.push(i);
	}
	EXPECT_TRUE(s.isFull());
}

TEST(TStack_Methods, The_isEmpty_works)
{
	TStack<int> s;
	EXPECT_TRUE(s.isEmpty());
}

TEST(TStack_Methods, The_push_works)
{
	TStack<int> s;
	ASSERT_NO_THROW(s.push(10));
	EXPECT_EQ(s.top(), 10);
	ASSERT_NO_THROW(s.push(100));
	EXPECT_EQ(s.top(), 100);
}

TEST(TStack_Methods, The_push_can_reach_overflow)
{
	TStack<int> s;
	for (int i = 0; i < 101; i++) {
		if (s.isFull()) {
			EXPECT_EQ(i, 100);
			ASSERT_ANY_THROW(s.push(i));
			break;
		}
		s.push(i);
	}
}

TEST(TStack_Methods, The_pop_works)
{
	TStack<int> s;
	for (int i = 0; i < 5; i++) {
		s.push(i);
	}
	ASSERT_NO_THROW(s.pop());
	for (int i = 3; i >= 0; i--) {
		EXPECT_EQ(s.pop(), i);
	}
}

TEST(TStack_Methods, The_pop_can_reach_empty_stack)
{
	TStack<int> s;
	ASSERT_ANY_THROW(s.pop());
	for (int i = 0; i < 5; i++) {
		s.push(i);
	}
	for (int i = 4; i >= 0; i--) {
		s.pop();
	}
	EXPECT_ANY_THROW(s.pop());
}

TEST(TStack_Methods, The_top_works)
{
	TStack<int> s;
	for (int i = 0; i < 5; i++) {
		s.push(i);
	}
	ASSERT_NO_THROW(s.top());
	for (int i = 4; i >= 0; i--) {
		EXPECT_EQ(s.top(), i);
		s.pop();
	}
}

TEST(TStack_Methods, The_top_cannt_work_with_empty_stack)
{
	TStack<int> s;
	EXPECT_ANY_THROW(s.top());
}
