/*
 * Parsing 
 */

# include <fstream>
# include <sstream>

# include "node.h"


void parsing(std::string file) 
{ 
   std::filebuf fb;
   std::string temp;

   if (fb.open(file, std::ios::in))
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
         auto it = nodes.find(temp);
         if ((temp != "\\") && (it == nodes.end()))
         {
            Node a;
            a.cluster.insert(temp);
            nodes.insert(std::make_pair(temp, a));
            p_input.insert(temp);
         }
         is >> temp;
      }

      is >> temp;
      while (temp[0] != '.')
      {
         auto it = nodes.find(temp);
         if ((temp != "\\") && (it == nodes.end()))
         {
            Node a;
            nodes.insert(std::make_pair(temp, a));
            p_output.insert(temp);
         }
         is >> temp;
      }

      while (1)
      {
         if (temp == ".latch")
         {
            std::string temp2;
            is >> temp;
            
            auto got_in = nodes.find(temp);
            if (got_in == nodes.end())
            {
               Node a;
               nodes.insert(std::make_pair(temp, a));
            }

            auto it = p_output.find(temp);
            if (it == p_output.end())
            {
               p_output.insert(temp);
            }
            
            is >> temp2;

            auto got_out = nodes.find(temp2);
            if (got_out == nodes.end())
            {
               Node a;
               a.cluster.insert(temp2);
               nodes.insert(std::make_pair(temp2, a));
            }
            else
            {
               got_out->second.cluster.insert(temp2);
            }
            
            auto it2 = p_input.find(temp2);
            if (it2 == p_input.end())
            {
               p_input.insert(temp2);
            }
            else
            {
               got_out->second.cluster.insert(temp2);
            }

            is.ignore(300,'\n');
         }

         else
         {
            if (temp == ".names")
            {
               std::string line;
               std::vector<std::string> inputs;
               
               getline(is, line);
               std::istringstream linestream(line);

               getline(linestream, temp, ' ');
               while(getline(linestream, temp, ' '))
               {
                  auto got = nodes.find(temp);
                  if (got == nodes.end())
                  {
                     Node a;
                     nodes.insert(std::make_pair(temp, a));
                  }
                  inputs.push_back(temp);
               }

               for (auto it = inputs.begin(); it != (inputs.end() - 1); ++it)
               {
                  auto got = p_output.find(*it);
                  auto got2 = p_input.find(inputs[inputs.size() - 1]);
                  if ((got == p_output.end()) && (got2 == p_input.end()))
                  {
                     nodes.find(*it)->second.output.insert(std::make_pair(inputs[inputs.size() - 1], node_delay));
                     nodes.find(inputs[inputs.size() - 1])->second.input.insert(std::make_pair(*it, node_delay));
                     nodes.find(inputs[inputs.size() - 1])->second.orig_input.insert(*it);
                  }
               }
            }
       
            else
            {
               if (temp == ".end")
               {
                  break;
               }
            
               else
               {
                  is >> temp;
                  while (temp[0] != '.')
                  {
                     is >> temp;
                  }
               }
            }
         }
      }
      fb.close();
   }

   else
   {
      std::cout << "Cannot open file\n";
   }
}
