#include <iostream>
#include "./part1.h"

extern "C" {
  #include "./../file.h"
}

using std::ios;

BingoNumber::BingoNumber(int n) {
  number = n;
  called = false;
}

void BingoCard::add_line(vector<int> numbers) {
  vector<BingoNumber> bingo_numbers;
  bingo_numbers.reserve(numbers.size());

  for (int n : numbers) {
    bingo_numbers.push_back(BingoNumber(n));
  }

  rows.push_back(bingo_numbers);
}

vector<int> BingoCard::row_numbers(int row_number) {
  auto row = rows.at(row_number);
  vector<int> ints;

  for (auto bingo_number : row) {
    ints.push_back(bingo_number.number);
  }

  return ints;
}

bool BingoCard::is_winner() {
  // Check across
  for (auto row : rows) {
    int numbers_called = 0;
    for (auto bingo_number : row) {
      if (bingo_number.called)
        numbers_called++;

      if (numbers_called >= row.size())
        return true;
    }
  }

  // Check down
  for (int col = 0; col < rows.size(); col++) {
    int numbers_called = 0;
    for (int row = 0; row < rows.size(); row++) {
      if (rows[row][col].called)
        numbers_called++;
    }

    if (numbers_called >= rows.size())
      return true;
  }

  return false;
}

void BingoCard::call(int number) {
  for (auto &row : rows) {
    for (auto &bingo_number : row) {
      if (bingo_number.number == number) {
        bingo_number.called = true;
      }
    }
  }
}

vector<string> split_str(string str, string separator) {
  vector<string> result;

  auto start = 0U;
  auto end = str.find(separator);
  while (end != string::npos) {
    string ele = str.substr(start, end - start);
    result.push_back(ele);

    start = end + separator.length();
    end = str.find(separator, start);
  }

  result.push_back(str.substr(start, str.length()));

  return result;
}

vector<int> read_numbers(fstream *file) {
  string line;
  getline(*file, line);

  auto numbers_as_strings = split_str(line, ",");

  vector<int> ints;
  ints.reserve(numbers_as_strings.size());

  for (auto str : numbers_as_strings) {
    ints.push_back(stoi(str));
  }

  return ints;
}

string remove_extra_spaces(string str) {
  string new_string = "";
  const char initial = '\0';
  char last_ch = initial;

  for (char ch : str) {
    if (last_ch == initial && ch == ' ')
      continue;

    if (ch == ' ' && last_ch == ' ')
      continue;

    new_string = new_string + ch;
    last_ch = ch;
  }

  return new_string;
}

vector<int> line_to_numbers(vector<string> numbers_s) {
  vector<int> numbers;
  numbers.reserve(numbers_s.size());

  for (string number : numbers_s) {
    numbers.push_back(stoi(number));
  }

  return numbers;
}

BingoCard read_card(fstream *file) {
  BingoCard card;

  // Card has 5 lines, so read those
  for (int i = 0; i < 5; i++) {
    string line;
    getline(*file, line);
    line = remove_extra_spaces(line);
    vector<string> numbers_s = split_str(line, " ");
    vector<int> numbers_i = line_to_numbers(numbers_s);

    card.add_line(numbers_i);
  }

  return card;
}

vector<BingoCard> read_cards(fstream *file) {
  vector<BingoCard> cards;
  cards.reserve(5);
  string line;

  while(file->peek() != EOF) {
    auto position = file->tellg();
    getline(*file, line);

    if (line.length() != 0) {
      file->seekg(position);
      auto card = read_card(file);
      cards.push_back(card);
    }
  }

  return cards;
}

void print_winner(BingoCard card, int winning_number) {
  printf("Found a winner!\n\n");

  int sum = 0;
  for (auto row : card.rows) {
    for (auto bingo_number : row) {
      printf("%-2d ", bingo_number.number);
      if (!bingo_number.called)
        sum = sum + bingo_number.number;
    }
    printf("\n");
  }

  printf("\nSum of uncalled numbers: %d\n", sum);
  printf("Sum of uncalled times last number: %d\n", sum * winning_number);
}

static const short BUFFER_LENGTH = 255;
void run4_1(const char *filename) {
  fstream file;
  file.open(filename, ios::in);

  vector<int> numbers = read_numbers(&file);
  vector<BingoCard> cards = read_cards(&file);

  printf("Playing with %lu cards\n", cards.size());

  for (int number : numbers) {
    printf("Calling %d\n", number);

    for (auto &card : cards) {
      card.call(number);

      if (card.is_winner()) {
        print_winner(card, number);
        return;
      }
    }
  }

  printf("There were no winners :(\n");
}
