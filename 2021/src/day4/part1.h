#ifndef DAY4_1
#define DAY4_1

#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::string;
using std::fstream;

class BingoNumber {
  public:
    BingoNumber(int n);
    int number;
    bool called;
};

class BingoCard {
  public:
    vector<vector<BingoNumber>> rows;
    vector<int> row_numbers(int number);
    void add_line(vector<int> line);
    bool is_winner();
    void call(int number);
};

void run4_1(const char*);
vector<int> read_numbers(fstream*);
vector<BingoCard> read_cards(fstream*);
BingoCard read_card(fstream *file);
vector<string> split_str(string str, string separator);
string remove_extra_spaces(string str);
void print_winner(BingoCard card, int winning_number);

#endif
