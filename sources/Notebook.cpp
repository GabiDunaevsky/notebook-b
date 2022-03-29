#include "Notebook.hpp"

#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

namespace ariel
{   
    // Constructor
    Notebook::Notebook(){   
    }
    
    // Destructor
    Notebook::~Notebook(){}

    // write function throwing all the exceptions.
    void Notebook::write(int page, int row, int column,Direction dir , string const & word){
        int wLen = int(word.size());
        if (word.find('~') != string::npos){
        throw invalid_argument( "the char '~' can't be written" );
    }
        if(column >= maxColLen){throw invalid_argument("Your massage is over the row limit.");}
        if(column + wLen > maxColLen && dir == Direction::Horizontal){ throw invalid_argument("Your massage is over the row limit.");}
        if(page < 0|| row < 0 || column < 0){ throw invalid_argument("One of your params is negative.");}
         for (unsigned long i = 0; i < word.length(); i++)
    {
        if (int(word.at(i)) < min_char || int(word.at(i)) > max_char){
            throw invalid_argument("there is at least one not printable char!");
        }
    }
        string sPage = to_string(page);
        string sRow = to_string(row);
        string sCol = to_string(column);
        string key = to_string(page).append(",").append(sRow).append(",").append(sCol);
        if(dir == Direction::Horizontal){
            checkingForMaxRow(page,row);
            int tmpCol = column;
            string stmpCol;
            for(int j = 0; j <word.length();j++){
                 if(loc.count(key) > 0  && loc[key] != '_'){
                    throw invalid_argument( "This place is already writen" );
                }
                tmpCol++;
                stmpCol = to_string(tmpCol);
                key = to_string(page).append("," ).append(sRow).append(",").append(stmpCol);
            }
            key = to_string(page).append(",").append(sRow).append(",").append(sCol);
            tmpCol = column;
            for(unsigned long i = 0 ; i < word.length();i++){
                char c = word.at(i);
                loc.insert(std::pair<string,char>(key , c));
                tmpCol++;
                stmpCol = to_string(tmpCol);
                key = to_string(page).append("," ).append(sRow).append(",").append(stmpCol);
            }
        }else{
            checkingForMaxRow(page,row);
            int tmpRow = row;
            string stmpRow;
            for(int j =0; j < word.length();j++){
                 if(loc.count(key) > 0 && loc[key] != '_'){
                    throw invalid_argument( "This place is already writen" );
                }
                tmpRow++;
                stmpRow = to_string(tmpRow);
                key = key = to_string(page).append(",").append(stmpRow).append(",").append(sCol);
            }
            key = to_string(page).append(",").append(sRow).append(",").append(sCol);
            tmpRow = row;
            for(unsigned long i = 0 ; i < word.length(); i++){
                loc.insert(std::pair<string,char>(key , word.at(i)));
                tmpRow++;
                stmpRow = to_string(tmpRow);
                key = key = to_string(page).append(",").append(stmpRow).append(",").append(sCol);
            }
        }
    }

    // read function throwing all the exceptions.
    string Notebook::read( int page,int row,  int column, Direction dir, int len){
        if(column >= maxColLen){throw invalid_argument("Your massage is over the row limit.");}
        if(column + len > maxColLen && dir == Direction::Horizontal ){ throw invalid_argument("Your massage is over the row limit.");}
        if(page < 0 || row < 0 || column < 0){ throw invalid_argument("One of your params is negative.");}
        if(len < 0 ){ throw invalid_argument("Length can't be negative");}
        string sPage = to_string(page);
        string sRow = to_string(row);
        string sCol = to_string(column);
        string key = to_string(page).append(",").append(sRow).append(",").append(sCol);
        string ans;
        if(dir == Direction::Horizontal){
            int tmpCol = column;
            string stmpCol;
            for(int i = 0; i < len; i++){
                if(loc.count(key) == 0){
                    ans += '_';
                    tmpCol++;
                    stmpCol = to_string(tmpCol);
                    key = to_string(page).append(",").append(sRow).append(",").append(stmpCol);
                }else{
                    ans +=  loc[key];
                    tmpCol++;
                    stmpCol = to_string(tmpCol);
                    key = to_string(page).append(",").append(sRow).append(",").append(stmpCol);
                }
            }
        }else{
           int tmpRow = row;
            string stmpRow;
            for(int i = 0; i < len; i++){
                if(loc.count(key) == 0){
                    ans += '_';
                    tmpRow++;
                    stmpRow = to_string(tmpRow);
                    key =to_string(page).append(",").append(stmpRow).append(",").append(sCol);
                }else{
                    ans +=  loc[key];
                    tmpRow++;
                    stmpRow = to_string(tmpRow);
                    key =to_string(page).append(",").append(stmpRow).append(",").append(sCol);
                }
            } 
        }
        return ans;
    }
// erase function throwing all the exceptions.
    void Notebook::erase( int page, int row,  int column, Direction dir,  int len){
        if(column >= maxColLen){throw invalid_argument("Your massage is over the row limit.");}
        if(column +len > maxColLen && dir == Direction::Horizontal ){ throw invalid_argument("Your massage is over the row limit.");}
        if(page < 0 || row < 0|| column < 0){ throw invalid_argument("One of your params is negative.");}
        if(len < 0 ){ throw invalid_argument("Length can't be negative");}
        string sPage = to_string(page);
        string sRow = to_string(row);
        string sCol = to_string(column);
        string key = sPage.append(",").append(sRow).append(",").append(sCol);
        if(dir == Direction::Horizontal){
            checkingForMaxRow(page,row);
            int tmpCol = column;
            string stmpCol;
            for(int i = 0; i < len;i++){
                loc[key] = '~';
                tmpCol++;
                stmpCol = to_string(tmpCol);
                key = to_string(page).append(",").append(sRow).append(",").append(stmpCol);
            }
        }else{
            checkingForMaxRow(page,row);
            int tmpRow = row;
            string stmpRow;
            for(int i = 0; i < len;i++){
                loc[key] = '~';
                tmpRow++;
                stmpRow = to_string(tmpRow);
                key =to_string(page).append(",").append(stmpRow).append(",").append(sCol);
            }
        }
    }
    void Notebook::show(int page){
        if(page < 0 ){ throw invalid_argument("Page can't be negative");}
        if(lastRow.count(page) == 0){
            cout<< "This page is still empty." << endl;
            return;
        }
        string ans;
        int len =lastRow[page];
        for(int i = 0; i <= len ; i++){
            ans += read(page,i,0,Direction::Horizontal, maxColLen) + "\n";
        }
        cout<< ans << endl;
    }

    void Notebook::checkingForMaxRow(int page , int row){
        if(lastRow.count(page) > 0 ){
                if(lastRow[page] < row){
                    map<int, int>::iterator it = lastRow.find(page); 
                    it->second = row;
                }
            } else{
                lastRow.insert(std::pair<int,int>(page ,row)); 
            }
    }
}

