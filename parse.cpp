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
                     nodes.find(*it)->second.orig_output.insert(inputs[inputs.size() - 1]);
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


void dag_json()
{
   std::ofstream jsonf(file_name + ".dag.json");

   jsonf << "{\n";
   jsonf << "\"nodes\": [\n";

   for (auto it = nodes.begin(); it != nodes.end(); ++it)
   {
      jsonf << "{\"id\": \"" << it->first << "\", \"group\": 0},\n"; 
   }

   long pos = jsonf.tellp();
   jsonf.seekp(pos-2);
   jsonf << "\n";

   jsonf << "],\n";

   jsonf <<"\"links\": [\n";

   for (auto it3 = nodes.begin(); it3 != nodes.end(); ++it3)
   {
      for (auto it2 = it3->second.orig_output.begin(); it2 != it3->second.orig_output.end(); ++it2)
      {
         jsonf << "{\"source\": \"" << it3->first << "\", \"target\": \"" << *it2 << "\", \"value\": 1},\n";
      }
   }
  
   pos = jsonf.tellp();
   jsonf.seekp(pos - 2);
   jsonf << "\n";

   jsonf << "]\n";
   jsonf << "}\n";
}

void label_json()
{
   std::ofstream jsonf(file_name + ".label.json");

   jsonf << "{\n";
   jsonf << "\"nodes\": [\n";

   for (auto it = nodes.begin(); it != nodes.end(); ++it)
   {
      jsonf << "{\"id\": \"" << it->first << " = " << it->second.label << "\", \"group\": 0},\n"; 
   }

   long pos = jsonf.tellp();
   jsonf.seekp(pos-2);
   jsonf << "\n";

   jsonf << "],\n";

   jsonf << "\"links\": [\n";

   for (auto it3 = nodes.begin(); it3 != nodes.end(); ++it3)
   {
      for (auto it2 = it3->second.orig_output.begin(); it2 != it3->second.orig_output.end(); ++it2)
      {
         jsonf << "{\"source\": \"" << it3->first << "\", \"target\": \"" << *it2 << "\", \"value\": 1},\n"; 
      } 
   }

   pos = jsonf.tellp();
   jsonf.seekp(pos-2);
   jsonf << "\n";
   
   jsonf<<"]\n";
   jsonf<<"}\n";
}

void cluster_json()
{
   unsigned int count = 1;
   std::ofstream jsonf(file_name + ".cluster.json");

   jsonf << "{\n";
   jsonf << "\"nodes\": [\n";

   std::unordered_map<std::string, unsigned int> nodes_seen;

   if (post)
   {
      for (unsigned int it = 0; it != fclusters.size(); ++it)
      {
         for (auto it2 = fclusters[it].begin(); it2 != fclusters[it].end(); ++it2)
         {
            auto got = nodes_seen.find(*it2);
            if (got == nodes_seen.end())
            {
               nodes_seen.insert(std::make_pair(*it2, 1));
               jsonf << "{\"id\": \"" << *it2 << "0\", \"group\": " << count << "},\n"; 
            }
            else
            {
               jsonf << "{\"id\": \"" << *it2 << got->second << "\", \"group\": " << count << "},\n"; 
               ++(got->second);
            }
         }
         ++count;
      }
   }
   else
   {
      for (auto it = final_clusters.begin(); it != final_clusters.end(); ++it)
      {
         for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
         {
            auto got = nodes_seen.find(*it2);
            if (got == nodes_seen.end())
            {
               nodes_seen.insert(std::make_pair(*it2, 1));
               jsonf << "{\"id\": \"" << *it2 << "0\", \"group\": " << count << "},\n"; 
            }
            else
            {
               jsonf << "{\"id\": \"" << *it2 << got->second << "\", \"group\": " << count << "},\n"; 
               ++(got->second);
            }
         }
         ++count;
      }
   }

   long pos = jsonf.tellp();
   jsonf.seekp(pos-2);
   jsonf << "\n";

   jsonf << "],\n";

   jsonf<<"\"links\": [\n";

   for (auto it3 = nodes.begin(); it3 != nodes.end(); ++it3)
   {
      for (auto it2 = it3->second.orig_output.begin(); it2 != it3->second.orig_output.end(); ++it2)
      {
         for (unsigned int i = 0; i < nodes_seen.find(it3->first)->second; ++i)
         {
            for (unsigned int j = 0; j < nodes_seen.find(*it2)->second; ++j)
            {
               jsonf << "{\"source\": \"" << it3->first << i << "\", \"target\": \"" << *it2 << j << "\", \"value\": 1},\n"; 

            }
         }
      }
   }

   pos = jsonf.tellp();
   jsonf.seekp(pos-2);
   jsonf << "\n";
   
   jsonf<<"]\n";
   jsonf<<"}\n";
}
