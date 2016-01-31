#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>

namespace {

  static const size_t FileIdx = 1;
  static const size_t SizeIdx = 2;
  static const size_t PatternIdx = 3;

  // *****************************************************************
  // @brief Read the last numLines from a file
  // @param lines - read lines
  // @param filePath - file path
  // @numLines - Number of lines to read
  // *****************************************************************
  void
  readFile(std::queue<std::string>&  lines,
	   const std::string&        filePath,
	   const size_t              numLines)
  {
    std::ifstream ifs(filePath.c_str());
    if (ifs.is_open()) {
      std::string line;
      while (std::getline(ifs, line)) {
	if (lines.size() >= numLines) {
	  // if we have exceeded num lines,
	  // we will throw away the first
	  lines.pop();
	} // if
	lines.push(line);
      } // while
    } // if
  } // readFile

  // *****************************************************************
  // @brief Take in a pattern (with a wild card - *),
  // and see if the given line, contains the pattern (case insensitive)
  // @brief line - line to read
  // @brief pattern - pattern to match
  // @return - match or not
  // *****************************************************************
  bool
  matchLine(const std::string& line, const std::string& pattern)
  {
    static const char Wcard('*');
    int p = 0;
    for (size_t i=0; i < line.size(); ++i) {
      if (std::toupper(line[i]) == toupper(pattern[p])
	  || pattern[p] == Wcard) {
	// look for the consecutive character match
	++p;
      } else {
	// reset to pattern idx to start the match again
	p = 0;
      } // if

      // if we have matched all, return so
      if (p >= pattern.size()) {
	return true;
      }
    } // for
    
    // no match
    return false;
    
  } // matchline


  // *****************************************************************
  // @brief Take in a pattern (with a wild card - *),
  // and see if the given lines, contains the pattern (case insensitive)
  // @param matchLines - lines matching the pattern
  // @param lines - line to check
  // @param pattern - pattern to match
  // @return - match or not
  // *****************************************************************
  void
  matchLines(std::vector<std::string>& matchLines,
	     std::queue<std::string>& lines,
	     const std::string& pattern)
  {
    while (lines.empty() == false) {
      std::string line = lines.front();
      lines.pop();
      if (matchLine(line, pattern) == true) {
	matchLines.push_back(line);
      } // if
    } // while
  } // matchLines


  void
  printUsage()
  {
    std::cout << "<executable> <FilePath> <NumberofLines> <Pattern String>"
	      << std::endl;
  } // printUsage
  
} // namespace


int main(int argc, char* argv[])
{
  static const size_t NumArgs = 3;
  if (argc <= NumArgs) {
    std::cerr << "Provide required args" << std::endl;
    printUsage();
    return 1;
  } // if

  const std::string fileName = argv[FileIdx];
  const size_t numLines      = std::atoi(argv[SizeIdx]);
  const std::string pattern  = argv[PatternIdx];

  std::queue<std::string> lines;
  readFile(lines, fileName, numLines);
  std::vector<std::string> mLines;
  matchLines(mLines, lines, pattern);

  for (int i=0; i < mLines.size(); ++i) {
    std::cout << mLines[i] << std::endl;
  } // for
  
  return 0;
}
