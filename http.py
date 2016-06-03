#!/usr/bin/python
import urllib2
import re
import sys
import time

URL = "http://www.hacker.org/coil/index.php"
URL = URL + "?name=" + sys.argv[1] + "&password=" + sys.argv[2]

def GetPuzzle():
    response = urllib2.urlopen(URL)
    html = response.read()
    
    line_level = html.find("Level: ") + 7
    line_level_end = html.find("<br", line_level)
    line_level = html[line_level:line_level_end]
    
    line_vars = html.find("FlashVars=\"") + 11
    line_vars_end = html.find("\n", line_vars) - 1
    line_vars = html[line_vars:line_vars_end]
    
    size_x = line_vars.find("x=") + 2
    size_x_end = line_vars.find("&", size_x)
    
    size_y = line_vars.find("y=") + 2
    size_y_end = line_vars.find("&", size_y)
    
    size_x = line_vars[size_x:size_x_end]
    size_y = line_vars[size_y:size_y_end]
    
    board_data = line_vars.find("board=") + 6
    
    data = line_level + "\n" + size_x + "\n" + size_y + "\n" + line_vars[board_data:]
    
    comp = data.split("\n")
    comp[0] = int(comp[0])
    comp[1] = int(comp[1])
    comp[2] = int(comp[2])
    return comp

def PostSolution(path, x, y):
    url = URL
    url = url + "&path=" + path + "&x=" + str(x) + "&y=" + str(y)
    urllib2.urlopen(url)


if sys.argv[3] == "POST":
    f = open('solution.dat', "r")
    x = f.readline().rstrip('\r\n')
    y = f.readline().rstrip('\r\n')
    path = f.readline().rstrip('\r\n')
    f.close()
    PostSolution(path, x, y)

elif sys.argv[3] == "GET":
    data = GetPuzzle()
    f = open('board.dat', 'w')
    print >>f, data[0], "\n", data[1], "\n", data[2], "\n", data[3],
    f.close()
