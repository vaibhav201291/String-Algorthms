#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

typedef vector<string> bw_matrix; //(bwm is Burrows-Wheeler Matrix)

bw_matrix createRotMatrix(int &st, bw_matrix &mat)
{
  bw_matrix rmat;
  rmat = mat;

  for (int i = 0; i < st; i++)
  {
    for (int j = 0; j < st; j++)
    {
      int shift_ind = i + j;
      if (shift_ind > st - 1)
      {
        rmat[i][j] = mat[i][shift_ind - st];
      }
      else
      {
        rmat[i][j] = mat[i][shift_ind];
      }
    }
  }
  mat = rmat;
  return mat;
}

string BWT(const string &text)
{
  string result = "";

  int size_text = text.size();
  bw_matrix mat(size_text);

  for (int i = 0; i < size_text; i++)
  {
    mat[i] = text;
  }

  cout << endl;

  createRotMatrix(size_text, mat); // generates a matrix out of all the rotations

  ////////// To print the matrices /////////////
  // for (int i = 0; i < size_text; i++)
  // {
  //   for (int j = 0; j < size_text; j++)
  //   {
  //     cout << mat[i][j] << "  ";
  //   }
  //   cout << endl;
  // }
  /////////////////////////////////////////////

  sort(mat.begin(), mat.end()); // sorts the rotation matrix

  for (int i = 0; i < size_text; i++)
  {
    result += mat[i][size_text - 1];
  }
  cout << endl;

  return result;
}

int main()
{
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}