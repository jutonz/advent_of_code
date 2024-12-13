#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include "../part1.h"

extern "C" {
#include "../../file.h"
}

using std::vector;
using std::ios;

TEST(split_str, splits_a_string) {
  string str = "1,2,3";

  auto result = split_str(str, ",");

  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], "1");
  EXPECT_EQ(result[1], "2");
  EXPECT_EQ(result[2], "3");
}

TEST(read_numbers, reads_numbers) {
  fstream file;
  file.open("test_fixtures/day4/input.txt", ios::in);

  vector<int> numbers = read_numbers(&file);

  EXPECT_EQ(numbers.size(), 4);
  EXPECT_EQ(numbers[0], 1);
  EXPECT_EQ(numbers[1], 2);
  EXPECT_EQ(numbers[2], 3);
  EXPECT_EQ(numbers[3], 4);
}

TEST(remove_extra_spaces, removes_spaces) {
  string input = "one two  three   four";

  string output = remove_extra_spaces(input);

  EXPECT_EQ(output, "one two three four");
}

TEST(remove_extra_spaces, removes_leading_spaces) {
  string input = "  one   two";

  string output = remove_extra_spaces(input);

  EXPECT_EQ(output, "one two");
}

TEST(read_card, reads_in_a_card) {
  fstream file;
  file.open("test_fixtures/day4/input.txt", ios::in);
  // Skip line of numbers to be called
  string line;
  getline(file, line);
  getline(file, line);

  BingoCard card = read_card(&file);

  vector<int> line0 {22, 13, 17, 11, 0};
  vector<int> line1 {8, 2, 23, 4, 24};
  vector<int> line2 {21, 9, 14, 16, 7};
  vector<int> line3 {6, 10, 3, 18, 5};
  vector<int> line4 {1, 12, 20, 15, 19};

  EXPECT_EQ(card.rows.size(), 5);
  EXPECT_EQ(card.row_numbers(0), line0);
  EXPECT_EQ(card.row_numbers(1), line1);
  EXPECT_EQ(card.row_numbers(2), line2);
  EXPECT_EQ(card.row_numbers(3), line3);
  EXPECT_EQ(card.row_numbers(4), line4);
}

TEST(read_cards, reads_many_cards) {
  fstream file;
  file.open("test_fixtures/day4/input.txt", ios::in);
  // Skip line of numbers to be called
  string line;
  getline(file, line);

  auto cards = read_cards(&file);

  vector<int> card0line4 = {1, 12, 20, 15, 19};
  vector<int> card1line4 = {14, 21, 16, 12, 6};

  EXPECT_EQ(cards.size(), 2);
  EXPECT_EQ(cards.at(0).row_numbers(4), card0line4);
  EXPECT_EQ(cards.at(1).row_numbers(4), card1line4);
}

TEST(BingoCard_is_winner, wins_across) {
  BingoCard card;
  card.add_line(vector<int> {1, 2});
  card.add_line(vector<int> {3, 4});

  EXPECT_FALSE(card.is_winner());
  card.call(1);
  EXPECT_FALSE(card.is_winner());
  card.call(2);
  EXPECT_TRUE(card.is_winner());
}

TEST(BingoCard_is_winner, wins_down) {
  BingoCard card;
  card.add_line(vector<int> {1, 2, 3});
  card.add_line(vector<int> {3, 4, 6});
  card.add_line(vector<int> {7, 8, 9});

  EXPECT_FALSE(card.is_winner());
  card.call(3);
  EXPECT_FALSE(card.is_winner());
  card.call(6);
  card.call(9);
  EXPECT_TRUE(card.is_winner());
}
