#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::sort;
using std::string;
using std::vector;
using std::swap;

typedef vector<string> bw_matrix;

////////// To print the matrices /////////////
// cout << endl;
// for (int i = 0; i < bwt_s; i++)
// {
//   for (int j = 0; j < bwt_s; j++)
//   {
//     cout << mat[i][j] << "  ";
//   }
//   // cout << mat[i];
//   cout << endl;
// }
/////////////////////////////////////////////

string InverseBWT_basic(const string &bwt)
{
  string text = "";
  string init_text;

  int bwt_s = bwt.size();
  bw_matrix mat(bwt_s);

  for (int i = 0; i < bwt_s; i++)
  {
    init_text += '$';
  }
  for (int i = 0; i < bwt_s; i++)
  {
    mat[i] = init_text;
  }

  for (int i = bwt_s - 1; i >= 0; i--)
  {
    for (int j = 0; j < bwt_s; j++)
    {
      mat[j][i] = bwt[j];
    }
    sort(mat.begin(), mat.end());
  }

  for (int i = 0; i < bwt_s; i++)
  {
    if (mat[i][bwt_s - 1] == '$')
    {
      text = mat[i];
    }
  }

  return text;
}

void reverseStr(string &str)
{
  int n = str.length();

  // Swap character starting from two
  // corners
  for (int i = 0; i < n / 2; i++)
    swap(str[i], str[n - i - 1]);
}

string InverseBWT(const string &bwt)
{
  string text = "$";

  int cntA, cntC, cntG, cntT;
  cntA = cntC = cntG = cntT = 0;
  int bwt_s = bwt.size();
  int sub_script[bwt_s];

  for (int i = 0; i < bwt_s; i++)
  {
    if (bwt[i] == 'A')
    {
      cntA++;
      sub_script[i] = cntA;
    }
    if (bwt[i] == 'C')
    {
      cntC++;
      sub_script[i] = cntC;
    }
    if (bwt[i] == 'G')
    {
      cntG++;
      sub_script[i] = cntG;
    }
    if (bwt[i] == 'T')
    {
      cntT++;
      sub_script[i] = cntT;
    }
    // text[i] = bwt[i];
  }

  int cInd = 0;
  char cSymb;

  for (int i = 0; i < bwt_s - 1; i++)
  {
    // int cnt = 0;
    cSymb = bwt[cInd];
    // text[bwt_s - i - 1] = cSymb;
    text += cSymb;

    // cout << "Current index is " << cInd << "  current symbol is " << cSymb << endl;

    // for (int j = 0; j < cInd + 1; j++)
    // {
    //   if (cSymb == bwt[j])
    //   {
    //     cnt++;
    //   }
    // }
    if (cSymb == 'A')
    {
      cInd = sub_script[cInd];
    }
    if (cSymb == 'C')
    {
      cInd = cntA + sub_script[cInd];
    }
    if (cSymb == 'G')
    {
      cInd = cntA + cntC + sub_script[cInd];
    }
    if (cSymb == 'T')
    {
      cInd = cntA + cntC + cntG + sub_script[cInd];
    }
  }
  reverseStr(text); 

  // for (int i = 1; i < bwt_s; i++)
  // {
  //   cout << text[i];
  // }
  // cout << '$' ;

  return text;
}

int main()
{
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
