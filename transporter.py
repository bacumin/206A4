#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import csv
import urllib2
import cgi
import cgitb
cgitb.enable()

#receives url player came from a.out, and inventory
urls= {
    "North":"http://cgi.cs.mcgill.ca/~bcumin1",
    "South":"http://cgi.cs.mcgill.ca/~bcumin1",
    "West":"http://cgi.cs.mcgill.ca/~bcumin1",
    "East":"http://cgi.cs.mcgill.ca/~bcumin1",
}

url='http://cgi.cs.mcgill.ca/~bcumin1/room.html'
inventory='10,10'

form = cgi.FieldStorage()
direction=form["direction"].value
base_url = urls[direction]

url_resources=base_url+"/resources.csv"
url_redirect=base_url+"/cgi-bin/a.out"

occupied="abc"
response = urllib2.urlopen(url_resources)
csvFile=csv.reader(response)
manna=0;gold=0;occupied=0;
for row in csvFile:
    manna=row[0]
    gold=row[1]
    occupied=row[2]

#if it is occupied
if(occupied != '0'):
    print("Status: 303 See other")
    print("Location: /~bcumin1/a.out?user_input=REFRESH")
else:
    print("")
    print("Status: 303 See other")
    print("Location: /"+url_redirect)


print "Content-type: text/html"
print
print """
<html>
    <h1> %s </h1>
</html>
"""%(occupied)
