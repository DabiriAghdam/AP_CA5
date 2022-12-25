#include "Game_Window.hpp"

using namespace std;

int main() 
{
    try 
    {
      string map_address;
      cout << "enter map address: ";
      cin >> map_address;
      Game_Window gw(map_address);
      gw.show();
    } 
    catch (string exception) 
    {
      cerr << "EXCEPTION: " << exception << endl;
      exit(EXIT_FAILURE);
    }
  return 0;
}