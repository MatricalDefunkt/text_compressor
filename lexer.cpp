#include <string>
#include "compression_map.cpp"
#define LEXER

using namespace std;

class CaptitalizationProcesor
{
protected:
  tuple<string, bool> static remove_capitalization(string word)
  {
    string new_word = "";
    for (int i = 0; i < word.length(); i++)
    {
      new_word += tolower(word[i]);
    }
    return make_tuple(new_word, word != new_word);
  }
};

class PunctuationProcessor
{
protected:
  tuple<string, char> static remove_punctuation(string word)
  {
    string new_word = "";
    for (int i = 0; i < word.length(); i++)
    {
      if (isalpha(word[i]))
      {
        new_word += word[i];
      }
    }

    return make_tuple(new_word, word.length() > new_word.length() ? word[word.length() - 1] : '\0');
  }
};

class Lexer : public CaptitalizationProcesor, public PunctuationProcessor
{
public:
  /**
   * @brief Normalizes a given string by removing capitalization and punctuation.
   *
   * @param word The string to be normalized.
   * @return The normalized string.
   */
  std::tuple<std::string, CompressionType, char> static normalize_string(std::string word)
  {
    // Remove punctuation
    tuple<string, char> punctuation_result = remove_punctuation(word);
    string punctuation_removed_word = get<0>(punctuation_result);
    char punctuation = get<1>(punctuation_result);

    // Remove capitalization
    tuple<string, bool> capitalization_result = remove_capitalization(punctuation_removed_word);
    string capitalization_removed_word = get<0>(capitalization_result);
    bool capitalization = get<1>(capitalization_result);

    // Determine compression type
    CompressionType compression_type = NONE;
    if (punctuation != '\0' && capitalization)
    {
      compression_type = BOTH;
    }
    else if (capitalization)
    {
      compression_type = CAPITALIZATION;
    }
    else if (punctuation != '\0')
    {
      compression_type = PUNCTUATION;
    }
    else if (word.length() < 3 && word.length() > 0)
    {
      compression_type = INELIGIBLE;
    }

    return make_tuple(capitalization_removed_word, compression_type, punctuation);
  }
};
