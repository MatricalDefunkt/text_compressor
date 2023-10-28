#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "lexer.cpp"
#include "dictionary.cpp"
#define COMPRESSOR

using namespace std;

class Compressor
{
public:
  void compress_file(std::string source_path, std::string dest_path)
  {
    auto compression_dictionary = Dictionary::get_words('\n');
    ifstream source_file(source_path);
    ofstream compressed_file(dest_path);
    string word;
    vector<CompressionType> compression_types;
    vector<char> punctuations_map;

    while (source_file >> word)
    {
      tuple<string, CompressionType, char> normalized_word = Lexer::normalize_string(word);

      // Create a compression map to ease decompression
      CompressionType compression_type = get<1>(normalized_word);
      compression_types.push_back(compression_type);
      punctuations_map.push_back(get<2>(normalized_word));

      Mapper mapper(compression_types, punctuations_map);

      // Remove capitalization, and punctuation if present
      word = get<0>(normalized_word);

      // If the word is in the map, write the key to the file
      if (compression_dictionary.find(word) != compression_dictionary.end())
      {
        compressed_file << compression_dictionary[word] << " ";
      }
      // Otherwise, write the word to the file
      else
      {
        compressed_file << word << " ";
      }
    }

    Mapper mapper(compression_types, punctuations_map);

    compressed_file << '\n'
                    << mapper.generate_map()
                    << '\n';
  }
};