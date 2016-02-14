#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

namespace {
  
  // ******************************************************************************
  // @brief read the contents of a file into a single string with line breaks
  // @param line - (out) the line that was read
  // @param fileName - the file to read from
  // ******************************************************************************
  void
  readFile(std::string&  line, const std::string& fileName)
  {
    std::ifstream ifs(fileName.c_str());

    if (ifs.is_open() == true) {
      std::string l;
      while (std::getline(ifs, l)) {
	line += l;
	// handle new lines in the file itself
	// getline will read them as separate lines
	line += "\n";
      } // while
    } // if
  } // readFile


  // ******************************************************************************
  // @brief Perform a word wrap of the given line per the given line size.
  // The line is wrapped such that no words are broken
  // (break is performed at a space character)
  // @note Only single byte characters are handled for now
  // @param line - (in/out) the line to wrap
  // 2param - lineSize - the size of every line
  // ******************************************************************************  
  void
  wordWrap(std::string& line, const size_t lineSize)
  {
    // track the index of the last space encountered
    // this is where we will wrap
    int s = -1;
    int ls = 0; // current line size
    int currLineSt = 0; // current line start index
    
    for (int i= 0; i < line.size(); ++i) {
      // if we have a new line, reset the current line size
      if (line[i] == '\n') {
	ls = 0;
	continue;
      } // if
      
      // increment the current line size 
      ++ls;

      // if the current line exceeds the wrap size, wrap it
      if (ls > lineSize) {	
	// we break after the last space encountered to avoid breaking words
	size_t bIdx = s + 1;
	
	// the entire string did not contain a space character to
	// break on.  (s would be -1)
	// We have no option but to break a word
	if (bIdx <= currLineSt) {
	  // we break at the current position
	  bIdx = i;
	} // if

	// insert a new line before the character at break index
	line.insert(bIdx, "\n");
	
	// current line starts after the break
	currLineSt = bIdx + 1;
	
	// update the line size:
	// current position in string - current line start index
	ls = (i - currLineSt) + 1;
      } // if

      // track the last space encountered
      // we track this towards the end to avoid breaking after the space occuring exactly at the limit
      // for example if the space is the last character violating the size constraint,
      // we should break at the previous space
      if (std::isspace(line[i]) != 0
	  || std::ispunct(line[i]) != 0) {
	s = i;
      } // if
      
    } // for
  } // wordWrap


  void
  printUsage()
  {
    std::cout << "<Program> <FileName> <LineSize>" << std::endl;
  } // printUsage

  
} // namespace
  
int main(int argc, char* argv[])
{
  if (argc < 3) {
    printUsage();
    return 1;
  } // if

  std::string line;
  readFile(line, argv[1]);

  wordWrap(line, std::atoi(argv[2]));
  std::cout << line << std::endl;
  
  return 0;
}
