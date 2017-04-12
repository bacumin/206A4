#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import csv
import urllib2
import cgi
import cgitb
cgitb.enable()

#GET URL AND INVENTORY
form = cgi.FieldStorage()
inventory=form["inv"].value
pManna, pGold=inventory.split(',')
url = form["url"].value

#url of our C program, in cas of success
url_cprogram="http://cgi.cs.mcgill.ca/~bcumin1/cgi-bin/room.cgi?inventory="+(pManna-1)+ "%%2C" + pGold+"C0&user_input=REFRESH"

#GET OCCUPIED STATUS
response = urllib2.urlopen("http://cgi.cs.mcgill.ca/~bcumin1/cgi-bin/resources.csv")
csvFile=csv.reader(response)
manna=0;gold=0;occupied=0;
for row in csvFile:
    manna=row[0]
    gold=row[1]
    occupied=row[2]

#FAILURE - ROOM IS OCCUPIED: SEND THEM BACK
if(occupied != '0'):
    print "Content-type: text/html"
    print
    print """
    <html>
        <meta http-equiv="refresh" content="0; url=%s"/>
    </html>
    """%(url)



#SUCCESS - ROOM IS UNOCCUPIED - change our room status to 1, calls other room's success.py.
# Passing information with url.
else:
    with open("resources.csv", 'w') as our_resources:
        writer=csv.writer(our_resources,delimiter=',')
        writer.writerow([manna,gold,'1'])

    #METHOD 1: PASS THE USERNAME
    idx_cgi=url.find("cgi-bin")-1
    idx_user=url.find("~")
    user_name=url[idx_user:idx_cgi]
    url_success="http://cgi.cs.mcgill.ca/"+user_name+"/cgi-bin/success.py?user_name=bcumin1"

    #METHOD 2: ENCODE THE C URL, PASS THAT
    import urllib
    x=urllib.urlencode({'url_c' : url_cprogram})
    url_success="http://cgi.cs.mcgill.ca/"+user_name+"/cgi-bin/success.py?"+x
    if inventory[:1]=="0":
        print "Content-type: text/html"
        print
        with open("dead.html", 'r') as fin:
            print fin.read()
    else:
        print "Content-type: text/html"
        print
        print """
         <html>
            <meta http-equiv="refresh" content="0; url=%s" />
         </html>
         """%(url_success)
#    <meta http-equiv="refresh" content="0; url=%s" />
