#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import csv
import urllib2
import cgi
import cgitb
cgitb.enable()

#GET URL AND INVENTORY
form_inv = cgi.FieldStorage()
inventory = form_inv["inv"].value
inventory1 = inventory.replace(',0', '%2')

form_url = cgi.FieldStorage()
url = form_url["url"].value

url_cprogram="http://cgi.cs.mcgill.ca/~naharo/cgi-bin/room.cgi?inventory="+inventory1+"C0&user_input=REFRESH"

#GET OCCUPIED STATUS
response = urllib2.urlopen("http://cgi.cs.mcgill.ca/~naharo/cgi-bin/resources.csv")
csvFile=csv.reader(response)
manna=0;gold=0;occupied=0;
for row in csvFile:
    manna=row[0]
    gold=row[1]
    occupied=row[2]

#ROOM IS OCCUPIED: SEND THEM BACK
if(occupied != '0'):
    print "Content-type: text/html"
    print
    print """
    <html>
    <meta http-equiv="refresh" content="0; url=%s"/>
    </html>
    """%(url)

#ROOM IS UNOCCUPIED
else:
    with open('resources.csv', 'w') as resources:
        writer=csv.writer(resources,delimiter=',')
        writer.writerow([manna,gold,'1'])

    print "Content-type: text/html"
    print
    print """
     <html>
    <meta http-equiv="refresh" content="0; url=%s" />
     </html>
     """%(url_cprogram)
