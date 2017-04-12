#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import csv
import urllib2
import cgi
import cgitb
cgitb.enable()

#Change the occupied status from 1 to 0
response = urllib2.urlopen("http://cgi.cs.mcgill.ca/~bcumin1/cgi-bin/resources.csv")
csvFile=csv.reader(response)
manna=0;gold=0;occupied=0;
for row in csvFile:
    manna=int(row[0])+1
    gold=row[1]
    occupied=row[2]

with open("resources.csv", 'w') as res:
    writer=csv.writer(res,delimiter=',')
    writer.writerow([manna,gold,'0'])

#redirect to the other page's C program

form=cgi.FieldStorage()
url_c=form["url_c"].value

print "Content-type: text/html"
print
print """
 <html>
    <meta http-equiv="refresh" content="0; url=%s" />
 </html>
 """%(url_c)
