#!/bin/bash

for i in 16 20 32
do
     /nethome/pchoudhary32/ram_wong_clustering/ram_wong_clustering -s $i -p 1 /nethome/pchoudhary32/ram_wong_clustering/input_blifs/s9234.blif > /nethome/pchoudhary32/ram_wong_clustering/s9234-$i.txt
     /nethome/pchoudhary32/ram_wong_clustering/ram_wong_clustering -s $i -p 1 /nethome/pchoudhary32/ram_wong_clustering/input_blifs/s13207.blif > /nethome/pchoudhary32/ram_wong_clustering/s13207-$i.txt
     /nethome/pchoudhary32/ram_wong_clustering/ram_wong_clustering -s $i -p 1 /nethome/pchoudhary32/ram_wong_clustering/input_blifs/b20_opt.blif > /nethome/pchoudhary32/ram_wong_clustering/b20_opt-$i.txt
     /nethome/pchoudhary32/ram_wong_clustering/ram_wong_clustering -s $i -p 1 /nethome/pchoudhary32/ram_wong_clustering/input_blifs/b22_opt.blif > /nethome/pchoudhary32/ram_wong_clustering/b22_opt-$i.txt
     /nethome/pchoudhary32/ram_wong_clustering/ram_wong_clustering -s $i -p 1 /nethome/pchoudhary32/ram_wong_clustering/input_blifs/b17_opt.blif > /nethome/pchoudhary32/ram_wong_clustering/b17_opt-$i.txt
done
