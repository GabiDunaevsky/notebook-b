#include "Direction.hpp"
#include <string>
#include <map>

using namespace std;
namespace ariel{
    const short maxColLen = 100;
    const int min_char = 32;
    const int max_char = 126;

    class Notebook{
        map<string,char>loc;
        map<int,int>lastRow;
        public:

        Notebook();
        ~Notebook();

        void write (int page,int row,int column,Direction dir , string const & word);
        

        string read(int page,int row,int column, Direction dir, int len);
        
        void erase(int page,int row, int column, Direction dir,int len);

        void show(int page);

        void checkingForMaxRow(int page,int row);
    };
}