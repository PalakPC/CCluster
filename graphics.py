import matplotlib.pyplot as plt
import networkx as nx
import json
import csv
from networkx.readwrite import json_graph
colorOptions = ['crimson','deeppink','gold','lavender','mediumpurple','yellowgreen','silver','cyan','lightseagreen','orange','dodgerblue','tan','teal']
def DrawGraph(filename,output_file,x):
    #G = nx.DiGraph()

    with open(filename) as f:
        js_graph = json.load(f)
    G = json_graph.node_link_graph(js_graph,True,False)
    labels = {}
    k=0
    colours = []
    for n in G.nodes():
        labels[n] = n
        colours.append(colorOptions[G.nodes[n]['group']])
        k = k + 1
    plt.figure(x)
    pos=nx.shell_layout(G) # positions for all nodes
    nx.draw(G,pos, node_size = 1500, node_color=colours, with_labels = True)

    plt.axis('off')
    plt.savefig(output_file) # save as png
    #plt.show() # display

def CreateTable(filename, output_file):
    # initializing the titles and rows list
    fields = []
    rows = []
    htmlfile = open(output_file, "w")
    # initialize rownum variable
    rownum = 0

    # write <table> tag

    htmlfile.write('<table border="1">')
    # reading csv file
    with open(filename, 'r') as csvfile:
        # creating a csv reader object
        reader = csv.reader(csvfile)

        # extracting field names through first row
        # fields = next(reader)
        for row in reader:  # Read a single row from the CSV file

            # write header row. assumes first row in csv contains header
            if rownum == 0:
                htmlfile.write('<tr>')  # write <tr> tag
                for column in row:
                    htmlfile.write('<th>' + column + '</th>')
                htmlfile.write('</tr>')

            # write all other rows
            else:
                htmlfile.write('<tr>')
                for column in row:
                    htmlfile.write('<td>' + column + '</td>')
                htmlfile.write('</tr>')

            # increment row count
            rownum += 1

            # write </table> tag
    htmlfile.write('</table>')


DrawGraph("sample.blif.dag.json","dag.png",1);
DrawGraph("sample.blif.label.json","label.png",2);
DrawGraph("sample.blif.cluster.json","cluster.png",3);
CreateTable("sample.blif.matrix.csv","matrix.html");
CreateTable("sample.blif.result.csv","result.html");
