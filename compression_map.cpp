#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <vector>
#define COMPRESSION_MAP

enum CompressionType
{
  NONE,
  CAPITALIZATION,
  PUNCTUATION,
  BOTH,
  INELIGIBLE
};

/**
 * @brief Provides functions to aid the generation and parsing of a compression map.
 *
 */
class Mapper
{
private:
  std::vector<CompressionType> _compression_types;
  std::vector<char> _punctuations;

public:
  Mapper(std::vector<CompressionType> &compression_types, std::vector<char> &punctuations)
  {
    _compression_types = compression_types;
    _punctuations = punctuations;
  }

  /**
   * @brief Generates a string representation of the compression map.
   * This function iterates over the `_compression_types` and `_punctuations` arrays,
   * appending each compression type and corresponding punctuation (if it exists) to a string.
   * The resulting string is formatted as "Map: [type1punc1type2punc2...]".
   *
   * @return std::string A string representation of the compression map.
   */
  std::string generate_map()
  {

    std::stringstream ss;
    ss << "Map: [";
    for (int i = 0; i < _compression_types.size(); i++)
    {
      ss << _compression_types[i];
      if (_punctuations[i] != '\0')
      {
        ss << _punctuations[i];
      }
    }
    ss << "]";
    return ss.str();
  }

  std::vector<std::string> read_map(const std::string &filename)
  {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> map;

    // Read the first line
    if (std::getline(file, line))
    {
      std::istringstream ss(line);

      // Split the line by commas
      std::string element;
      while (std::getline(ss, element, ','))
      {
        map.push_back(element);
      }
    }

    return map;
  }
};