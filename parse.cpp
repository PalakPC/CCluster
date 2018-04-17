/*
 * Parsing 
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include "node.h"

unsigned int total_nodes;
void parsing() 
{ 
   std::filebuf fb;

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
            Node a;
            a.name = temp;
            a.is_PI = true;
            a.cluster.push_back(a.name);
            nodes.insert(std::make_pair(a.name, a));
            PIs.push_back(a.name);
            total_nodes++;
         }
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
            nodes.insert(std::make_pair(a.name, a));
            POs.push_back(a.name);
            total_nodes++;
         }
         is>>temp;
      }

      while (1)
      {
         if (temp == ".latch")
         {
            is>>temp;
            auto got_in = nodes.find(temp);
            
            if (got_in != nodes.end())
            {
               got_in->second.is_PO = 1;
            }

            else
            {
               Node a;
               a.name = temp;
               a.is_PO = true;
               a.cluster.push_back(a.name);
               nodes.insert(std::make_pair(a.name, a));
               total_nodes++;
            }

            if (std::find(POs.begin(), POs.end(), temp) == POs.end())
            {
               POs.push_back(temp);
            }
            
            is>>temp;
            auto got_out = nodes.find(temp);
            
            if (got_out != nodes.end())
            {
               got_out->second.is_PI = 1;
            }

            else
            {
               Node a;
               a.name = temp;
               a.is_PI = true;
               a.cluster.push_back(a.name);
               nodes.insert(std::make_pair(a.name, a));
               total_nodes++;
            }
            
            if (std::find(PIs.begin(), PIs.end(), temp) == PIs.end())
            {
               PIs.push_back(temp);
            }
         
            is.ignore(300,'\n');
         }

         else
         {
            if (temp == ".names")
            {
               getline(is, temp);

               unsigned int len = temp.size();
               unsigned int pos = temp.find_last_of(' ');
               unsigned int midpos;

               std::string output = temp.substr(pos+1, len - pos - 2);
               std::string delimiter = " ";
               std::string token;
               std::vector<std::string> inputs;

               unsigned int start = 1;

               while ((midpos = temp.find(delimiter, start)) <= pos)
               {            
                  token = temp.substr(start, midpos - start);
                  inputs.push_back(token);
                  start = midpos + 1;
               }

               for (auto i = inputs.begin(); i != inputs.end(); ++i)
               {
                  auto got = nodes.find(*i);

                  if (got != nodes.end())
                  {
                     got->second.output.push_back(output);
                  }

                  else
                  {
                     Node a;
                     a.name = *i;
                     a.output.push_back(output);
                     a.cluster.push_back(a.name);
                     nodes.insert(std::make_pair(a.name, a));
                     total_nodes++;
                  }
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
                  nodes.insert(std::make_pair(a.name, a));
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
