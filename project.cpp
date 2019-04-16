#include<iostream>
#include<fstream>
#include<string.h>
#include<sstream>
#include<vector>

using namespace std;
static int i; //maintaining data set number

vector<float> x[22];
vector<float> y[22];
vector<float> z[22];
vector<float> latitude[22];
vector<float> longitude[22];
vector<float> speed[22];
vector<float> sound[22];
vector<float> timestamp[22];

void record_data()
{
  int j=0;
  string c;
  float k;
  string line,word,temp;
  
  while(i<22)
  {
    fstream fin;
    string ext="/home/abhijit/csv_docu/overtake_";
    c=to_string(i);
    string name=".csv";
    name.insert(0,c);
    ext.append(name);
    cout<<ext<<endl;
    int first_flag=1;
    fin.open(ext,ios::in);
    cout<<"d"<<endl;

    while(fin>>temp)
    {
      cout<<"e"<<endl;
      if(first_flag==1)
      {
        cout<<"f"<<endl;
        first_flag=0;
        continue;
      }


      fin>>line;
      stringstream s(line);
      cout<<line<<endl;

       while (getline(s, word, ',')) 
      {
        cout<<"g"<<endl;
        switch(j)
        {

          case 0:
             // k=stof(word);
              x[i].push_back(stof(word));
              break;
              case 1:
              y[i].push_back(stof(word));
              break;
              case 2:
              z[i].push_back(stof(word));
              break;
              case 3:
              latitude[i].push_back(stof(word));
              break;
              case 4:
              longitude[i].push_back(stof(word));
              break;
              case 5:
              speed[i].push_back(stof(word));
              break;
              case 6:
              sound[i].push_back(stof(word));
              break;
              case 7:
              timestamp[i].push_back(stof(word));
              break;
        }
        cout<<"a"<<endl;
        j++;

      }
      cout<<"b"<<endl;
      j=0;
    }
    cout<<"c"<<endl;
    first_flag=1;
    i++;

}
}
int main()
{
  i=1;
  record_data();
  return 0;

}



