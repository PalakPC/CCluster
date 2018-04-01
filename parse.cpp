/*
 * Parsing 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "starter.h"

vector<Node> nodes;
using namespace std;

void parsing() {
   
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
		  {
			  Node a;
			  a.name = temp;
			  a.is_PI = true;
			  a.is_PO = false;
			  a.label = 1;
			  a.cluster.insert(a.name);
			  nodes.push_back(a);
		  }
           // inputs.push_back(temp);
         is>>temp;
      }
      
      is >> temp;
      while (temp[0] != '.')
      {
		  if (temp != "\\")
		  {
			  Node a;
			  a.name = temp;
			  a.is_PI = false;
			  a.is_PO = true;
			  //a.label = 1;
			  //a.cluster.insert(a.name);
			  nodes.push_back(a);
		 }
            //outputs.push_back(temp);
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
			   unsigned int len = temp.length();
               //gates.push_back(temp);
			   unsigned int pos = temp.find_last_of(' ');

			   std::stringstream ss(s);
			   std::string item;
			   while (std::getline(ss, item, delim)) {
				   *(result++) = item;
			   }
			   if 
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
      fb.close();
   }

   //cout <<"\n The gates are \n";
   //for(std::vector<string>::iterator it = gates.begin(); it != gates.end(); ++it)
   //{
   //   cout<<*it<<"\n";
   //}
}
