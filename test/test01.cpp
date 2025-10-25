#include "../src/five.cpp"
#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>

TEST(FiveTest, DefaultConstructor) {
  Five f;
  std::ostringstream oss;
  oss << f;
  EXPECT_EQ(oss.str(), "0");
}

TEST(FiveTest, ConstructorWithSizeAndValue) {
  Five f(3, 2);
  std::ostringstream oss;
  oss << f;
  EXPECT_EQ(oss.str(), "222");
  EXPECT_THROW(Five(3, 5), std::invalid_argument);
}

TEST(FiveTest, ConstructorWithInitializerList) {
  Five f({1, 2, 3});
  std::ostringstream oss;
  oss << f;
  EXPECT_EQ(oss.str(), "321");
  EXPECT_THROW(Five({1, 2, 5}), std::invalid_argument);
}

TEST(FiveTest, ConstructorWithString) {
  Five f("123");
  std::ostringstream oss;
  oss << f;
  EXPECT_EQ(oss.str(), "321");
  EXPECT_THROW(Five("125"), std::invalid_argument);
  EXPECT_THROW(Five("12a"), std::invalid_argument);
}

TEST(FiveTest, CopyConstructor) {
  Five f1({1, 2, 3});
  Five f2(f1);
  std::ostringstream oss;
  oss << f2;
  EXPECT_EQ(oss.str(), "321");
  EXPECT_TRUE(f1 == f2);
}

TEST(FiveTest, MoveConstructor) {
  Five f1({1, 2, 3});
  Five f2(std::move(f1));
  std::ostringstream oss;
  oss << f2;
  EXPECT_EQ(oss.str(), "321");
  std::ostringstream oss2;
  oss2 << f1;
  EXPECT_EQ(oss2.str(), "0");
}

TEST(FiveTest, OperatorPlus) {
  Five f1({1, 3});
  Five f2({4, 1});
  Five result = f1 + f2;
  std::ostringstream oss;
  oss << result;
  EXPECT_EQ(oss.str(), "100");
}

TEST(FiveTest, OperatorMinus) {
  Five f1({0, 1});
  Five f2({2});
  Five result = f1 - f2;
  std::ostringstream oss;
  oss << result;
  EXPECT_EQ(oss.str(), "3");
  Five f3({1});
  Five f4({2});
  EXPECT_THROW(f3 - f4, std::invalid_argument);
}

TEST(FiveTest, OperatorEquals) {
  Five f1({1, 2, 3});
  Five f2({1, 2, 3});
  Five f3({3, 2, 1});
  EXPECT_TRUE(f1 == f2);
  EXPECT_FALSE(f1 == f3);
}

TEST(FiveTest, OperatorGreaterEqual) {
  Five f1({0, 1});
  Five f2({2});
  Five f3({0, 1});
  Five f4({1, 1});
  EXPECT_TRUE(f1 >= f2);
  EXPECT_TRUE(f1 >= f3);
  EXPECT_FALSE(f2 >= f4);
}

TEST(FiveTest, OperatorOutput) {
  Five f({3, 2, 1});
  std::ostringstream oss;
  oss << f;
  EXPECT_EQ(oss.str(), "123");
  Five f2;
  oss.str("");
  oss << f2;
  EXPECT_EQ(oss.str(), "0");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}