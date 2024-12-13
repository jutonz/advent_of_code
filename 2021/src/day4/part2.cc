#include <iostream>
#include <fstream>
#include <vector>
#include "./part1.h"

extern "C" {
  #include "./../file.h"
}

using std::fstream;
using std::vector;

void run4_2(const char *filename) {
  fstream file;
  file.open(filename, std::ios::in);

  vector<int> numbers = read_numbers(&file);
  vector<BingoCard> cards = read_cards(&file);

  printf("Playing with %lu cards\n", cards.size());

  vector<BingoCard> winners;
  int last_winning_number = 0;

  for (int number : numbers) {
    printf("Calling %d\n", number);

    vector<BingoCard> new_cards;
    new_cards.reserve(cards.size());

    for (auto card = cards.rbegin(); card != cards.rend(); ++card) {
      card->call(number);

      if (card->is_winner()) {
        last_winning_number = number;
        winners.push_back(*card);
      } else {
        new_cards.push_back(*card);
      }
    }

    cards = new_cards;
  }

  auto last_winner = winners.back();
  print_winner(last_winner, last_winning_number);
}
