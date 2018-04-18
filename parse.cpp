/*
 * Parsing 
 */

# include <fstream>
# include <sstream>

# include "node.h"

unsigned int total_nodes;

void parsing() 
{ 
   std::filebuf fb;
   std::string temp;

   total_nodes = 0;

   if (fb.open("./new_sample.blif",std::ios::in))
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
            a.label = 1;
            a.cluster.insert(temp);
            nodes.insert(std::make_pair(temp, a));
            p_input.insert(temp);
            total_nodes++;
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
            a.cluster.insert(temp);
            nodes.insert(std::make_pair(temp, a));
            p_output.insert(temp);
            total_nodes++;
         }
         is >> temp;
      }

      while (1)
      {
         if (temp == ".latch")
         {
            is >> temp;
            
            auto got_in = nodes.find(temp);
            if (got_in == nodes.end())
            {
               Node a;
               a.cluster.insert(temp);
               nodes.insert(std::make_pair(temp, a));
               total_nodes++;
            }

            auto it = p_output.find(temp);
            if (it == p_output.end())
            {
               p_output.insert(temp);
            }
            
            is >> temp;

            auto got_out = nodes.find(temp);
            if (got_out != nodes.end())
            {
               got_out->second.label = 1;
            }

            else
            {
               Node a;
               a.label = 1;
               a.cluster.insert(temp);
               nodes.insert(std::make_pair(temp, a));
               total_nodes++;
            }
            
            auto it2 = p_input.find(temp);
            if (it2 == p_input.end())
            {
               p_input.insert(temp);
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

               while(getline(linestream, temp, ' '))
               {
                  auto got = nodes.find(temp);
                  if (got == nodes.end())
                  {
                     Node a;
                     a.cluster.insert(temp);
                     nodes.insert(std::make_pair(temp, a));
                     total_nodes++;
                  }
                  inputs.push_back(temp);
               }

               for (auto it = inputs.begin(); it != (inputs.end() - 1); ++it)
               {
                  nodes.find(*it)->second.output.insert(inputs[inputs.size() - 1]);
                  nodes.find(inputs[inputs.size() - 1])->second.input.insert(*it);
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
