#!/usr/bin/python3

import os
import cgi
import gc

form = cgi.FieldStorage()
name = form.getvalue('name', 'World')

fileBegin = "./basicweb/site/cgi/cgiGetBegin.html"
fileEnd = "./basicweb/site/cgi/cgiGetEnd.html"

#print the begining of the html
with open(fileBegin, 'r') as file:
    # Loop through each line in the file
    for line in file:
        print(line.strip())
# print the name
print(f"<h1>My first Python CGI</h1><h2>Hello, {name}!</h2>")
#print the end of the html
with open(fileEnd, 'r') as file:
    # Loop through each line in the file
    for line in file:
        print(line.strip())

del form, name, fileBegin, fileEnd
gc.collect()