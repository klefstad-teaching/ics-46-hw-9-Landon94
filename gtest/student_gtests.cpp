#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"


TEST(edit_distance_within, dif) {
  EXPECT_TRUE(edit_distance_within("cat", "bat", 1));

  EXPECT_TRUE(edit_distance_within("chat", "cheat", 1));

  EXPECT_FALSE(edit_distance_within("chat", "fill", 1));
}

TEST(ladder, order) {
  set<string> s;

  load_words(s, "src/words.txt");

  vector<string> ladder = generate_word_ladder("car", "cheat",s);

  vector<string> expected = {
    "car",
    "cat",
    "chat",
    "cheat"
  };

  for (int i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i], ladder[i]);
  }
}