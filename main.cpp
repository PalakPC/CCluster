#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
int main() {
    filebuf fb;


    //std::vector<std::array<char, 4>> v;
    char a[100];
    vector<string> inputs;
    vector<string> outputs;
    vector<string> latch_inputs;
    vector<string> latch_outputs;
    vector<string> gates;
    string temp;
    char tempchar[100];
    if (fb.open ("./s9234.blif",std::ios::in))
    {
        istream is(&fb);

        is >> temp;
        while (temp != "inputs")
        {
            is.ignore(200, '.');
            is >> temp;
        }
        is >> temp;
        while (temp != ".outputs")
        {
            if (temp != "\\")
                inputs.push_back(temp);
            is>>temp;
        }
        is >> temp;
        while (temp[0] != '.')
        {
            if (temp != "\\")
                outputs.push_back(temp);
            is>>temp;
        }
        while (1)
        {
            if (temp == ".latch")
            {
                is>>temp;
                latch_inputs.push_back(temp);
                is>>temp;
                latch_outputs.push_back(temp);
                is.ignore(300,'\n');
            }
            else
            {
                if (temp == ".names")
                {
                    is.getline(&tempchar[0],500);
                    temp = tempchar;
                    gates.push_back(temp);
                }
                else
                {
                    if (temp == ".end")
                        break;
                    else
                    {
                        is>> temp;
                        while (temp[0]!='.')
                            is>>temp;
                    }


                }
            }

        }


        //while (is)
            //std::cout << char(is.get());
        fb.close();
    }

    cout <<"\n The gates are \n";
    for(std::vector<string>::iterator it = gates.begin(); it != gates.end(); ++it) {
        cout<<*it<<"\n";
    }
    return 0;

}