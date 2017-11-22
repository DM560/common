#include "punct_stream.h"

// using namespace std;

Punct_stream& Punct_stream::operator>>(string& s)
{
  while (!(buffer>>s)) {
    // try to read from buffer
    if (buffer.bad() || !source.good()) return *this;
    buffer.clear();
    string line;
    getline(source,line);
    // get a line from source
    // do character replacement as needed:
    for (char& ch : line)
      if (is_whitespace(ch))
        ch = ' ';    // to space
      else if (!sensitive)
        ch = tolower(ch);  // to lower case
    buffer.str(line);
  }
  return *this;  // put string into stream
}

bool Punct_stream::is_whitespace(char c)
{
  for (char w : white)
    if (c==w) return true;
  return false;
}


Punct_stream::operator bool()
{
  return !(source.fail() || source.bad()) && source.good();
}

int main ()
// given text input, produce a sorted list of all words in that text
// ignore punctuation and case differences
// eliminate duplicates from the output
{
  Punct_stream ps {cin};
  ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~"); // note \“ means ” in string
  ps.case_sensitive(false);
  cout << "please enter words (ctrl-D to terminate)\n";
  vector<string> vs;
  for (string word; ps>>word; )
    vs.push_back(word); // read words

  sort(vs.begin(),vs.end());   // sort in lexicographical order
  for (int i=0; i<vs.size(); ++i)    // write dictionary
    if (i==0 || vs[i]!=vs[i-1]) cout << vs[i] << '\n';
}
