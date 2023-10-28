#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "compressor.cpp"

using namespace std;

int main()
{
  Compressor compressor;
  std::string source_path;
  std::string dest_path;
  cout << "Enter the relative path to the file to be compressed: ";
  cin >> source_path;
  cout << "Enter the relative path to the file to be written to: ";
  cin >> dest_path;
  compressor.compress_file(source_path, dest_path);
  return 0;
}
