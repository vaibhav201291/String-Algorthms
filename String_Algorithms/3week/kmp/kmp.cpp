#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<int> ComputePrefixFun(string &t)
{
  vector<int> s(t.size());
  s[0] = 0;
  int b = 0;

  for (int i = 1; i < t.size(); i++)
  {
    while ((b > 0) && (t[i] != t[b]))
    {
      b = s[b - 1];
    }
    if (t[i] == t[b])
    {
      b = b + 1;
    }
    else
    {
        b = 0;
    }
    s[i] = b;
  }
  // for(int i = 0; i < t.size(); i++)
  // {
  //   cout << s[i] << " ";
  // }
  // cout << endl;

  return s;
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where
// the pattern starts in the text.
vector<int> find_pattern(const string &pattern, const string &text)
{
  vector<int> result;

  string augText = pattern + '$' + text;
  // cout << "t is : " << augText << endl;

  vector<int> borderArray(augText.size());
  borderArray = ComputePrefixFun(augText);

  // for(int i = 0; i < augText.size(); i++)
  // {
  //   cout << borderArray[i] << " ";
  // }
  // cout << endl;

  for (int i = pattern.size() + 1; i < augText.size(); i++)
  {
    if (borderArray[i] == pattern.size())
    {
      result.push_back(i - (2 * pattern.size()));
    }
  }

  return result;
}

int main()
{
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i)
  {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
