/*
 * Parsing 
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include "starter.h"


void parsing() 
{ 
   std::filebuf fb;

   std::vector<std::string> latch_inputs;
   std::vector<std::string> latch_outputs;

   std::string temp;
   total_nodes = 0;

   std::string tempchar;

   if (fb.open ("./sample.blif",std::ios::in))
   {
      std::istream is(&fb);

      is >> temp;
      while (temp != "inputs")
      {
         is.ignore(256, '.');
         is >> temp;
      }

      is >> temp;
      while (temp != ".outputs")
      {
         if (temp != "\\")
         {
/*            Node a;
            a.name = temp;
            a.is_PI = true;
            a.is_PO = false;
            a.label = 1;
            a.input.clear();
            a.cluster.push_back(a.name);
            nodes.insert(std::make_pair(temp, a));
*/         }
         actual_inputs.push_back(temp);
//         total_nodes++;
         is>>temp;
      }

      is >> temp;
      while (temp[0] != '.')
      {
         if (temp != "\\")
         {
            Node a;
            a.name = temp;
            a.is_PO = true;
            a.cluster.push_back(a.name);
            nodes.insert(std::make_pair(temp, a));
         }
         POs.push_back(temp);
         total_nodes++;
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
               getline(is, temp);
               unsigned int len = temp.length();
               unsigned int pos = temp.find_last_of(' ');
               unsigned int midpos;

               std::string output = temp.substr(pos+1, len);
               std::string delimiter = " ";
               std::string token;
               std::vector<std::string> inputs;

               unsigned int start = 0;

               while ((midpos = temp.find(delimiter, start)) < pos)
               {
                  
                  token = temp.substr(start, midpos - start);
                  inputs.push_back(token);
                  start = midpos + 1;
               }

               bool ai = true;

               std::cout << "I work till line 104" << std::endl;
               for (auto i = inputs.begin(); i != inputs.end(); ++i)
               {
                  if (std::find(actual_inputs.begin(), actual_inputs.end(), *i) != actual_inputs.end() == false)
                  {
                     ai = false;

                     auto got = nodes.find(*i);

                     if (got != nodes.end())
                     {
                        got->second.output.push_back(output);
                     }

                     else
                     {
                        Node a;
                        a.name = token;
                        a.output.push_back(output);
                        a.cluster.push_back(a.name);
                        nodes.insert(std::make_pair(temp, a));
                        total_nodes++;
                     }
                  }
               }

               if (ai)
               {
                  PIs.push_back(output);
               }

               auto got = nodes.find(output);

               if (got != nodes.end())
               {
                  got->second.input = inputs;
               }

               else
               {
                  Node a;
                  a.name = output;
                  a.input = inputs;
                  a.cluster.push_back(a.name);
                  nodes.insert(std::make_pair(temp, a));
                  total_nodes++;
               }
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
