#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <iterator> 
#include "filesystem.h"
#include "algorithm"
#include <vector>
#include "indent.h"
using namespace std;
using namespace std::string_literals;

/*Replace the given string first 2 element and give back the name of variable*/
string replace_string(string r)
{
  r.replace(0,2,""); 
  return r;
}

/*States by line by line during reading from file */
enum STATE{
  LIST,     /* ls -l */
  CHANGE_DIR,   /* cd ./ dirname */
  NEXT_LINE,    /* total X */
  UP,           /* cd .. */
  DATA_DIR,     /* dXXX */
  DATA_FILE,    /* -XX */
  IDLE          /* init */
  };

/*if STATE == DATA_DIR add directory*/
void newDirectory(Directory& dir,const string& name)
{
  dir.addDir(name);
}

/*if STATE == DATA_FILE add file to actual parent dir*/
void newFile(Directory& dir,const string& name, const string& size)
{
  File *f=(dir.addFile(name));
  f->setSize(stoi(size));
}

/* if STATE == CHANGE_DIR change directory name */
Directory* changeDirectory(Directory& dir, string cdName)
{
  string s = replace_string(cdName);
  auto map = dir.getSubDirs();
  return dir.addDir(s);
}

/*if STATE == LIST noticed this is a list command*/
void list_list()
{
  cout <<"list"<< endl;
}

/* The given line decide witch will be te current state */
enum STATE current_line_state(string line)
{
  STATE st = IDLE;
  switch(line[0])
  {
    case 't': // total
      st = NEXT_LINE;
      break;
    case 'd':
      st = DATA_DIR;
      break;
    case '-':
      st = DATA_FILE;
      break;
    default:
      if(line[2] == 'c' && line[3] == 'd')
      {
        if(line[6] == '.') /* cd.. */
        {
          st = UP;
        }
        if(line[6]=='/') /* new directory */
        {
          st = CHANGE_DIR;
        }
      }
      if(line[2] == 'l')
        st = LIST;
  }
  return st;
}

/* Print close to JSON form the file */
Indent ii;
std::ostream& operator<<(std::ostream& out, const Directory& d)
 {
   ii.push();
   for(auto it: d.subDirs)
    {
      ii.push();
      out <<ii <<" \"" << it.first <<"\": {"<<endl;
      ii.push();
      out <<ii << it.second <<" }" << endl;
      ii.pop();
      ii.pop();
    }
    for(auto it5: d.files)
    {
        ii.push();
        out <<ii <<it5.first<<"\": {" <<endl;
        ii.pop();
        out<< ii<<"\t"<<"\"Size\": " <<
        (it5.second).getSize() <<endl;
        ii.pop();
        out << ii<< "}," << endl;
    }
    out<< "}"<< endl;
    return out;
 }

int main() {
  ifstream myfile("log.txt");
  STATE cur = IDLE; 
  Directory root;
  string line;
  Directory* actualDir=&root;
  if(myfile.is_open())
  {
    cout<< "opened" << endl;
    /* Read line by line */
    while(getline(myfile,line))
    {
      cur = current_line_state(line);
      istringstream ss(line);
      //cout<< line << endl;
      vector<string> results((istream_iterator<string>(ss)),
                                 istream_iterator<string>());
      
      /* Select current state and execute the function */
      switch(cur)
      {
        case DATA_DIR:
          newFile(*actualDir,results[8],results[4]);
          cout<< "DATA_DIR" << endl;
          break;
        case DATA_FILE:
          newDirectory(*actualDir,results[8]);
          cout<< "DATA" << endl;
        break;
        case NEXT_LINE:
          cout<< "DATA_FILE" << endl;
        break;
        case UP:
          actualDir = actualDir->getParent();
          cout<< "UP" << endl;
        break;
        case LIST:
          list_list();
        break;
        case CHANGE_DIR: // cd./folder
          actualDir = changeDirectory(*actualDir,results[2]);
          cout << "CHANGE_DIR" <<endl;
        break;
        default:
          cout << "do nothing";
      }
    }
     myfile.close();
     cout <<"{" << endl <<root << endl <<"}"<< endl;
    cout<< "closed" << endl;
  }
  else
     cout << "Unable to open file"<< endl;
}

