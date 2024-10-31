#!/usr/bin/python3

import os
import cgi
import cgitb
import shutil
import gc

cgitb.enable()

# files containing all the information about the uploaded file
# either html code or the name of the file
fileBegin = "./basicweb/site/cgi/cgiPostBegin.html"
fileEnd = "./basicweb/site/cgi/cgiPostEnd.html"
filename = os.environ.get('FILE_NAME')
#print the begining of the html
with open(fileBegin, 'r') as file:
    # Loop through each line in the file
    for line in file:
        print(line.strip())
#print the image
value = filename.split('=')[1].strip('"')
print(f"<h1>Uploaded file:\n{value}</h1>")
print('<img src="generic_image" alt="Uploaded Image" style="max-width:100%; height:auto;">')
#print the end of the html
with open(fileEnd, 'r') as file:
    # Loop through each line in the file
    for line in file:
        print(line.strip())

# delete the file
del fileBegin, fileEnd, filename, value
gc.collect()