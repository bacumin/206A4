#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import cgi
import cgitb; cgitb.enable()
import urllib2
import csv
import os


incorrect_output=0
form=cgi.FieldStorage()

#GET FORM VALUES
#form_manna=cgi.FieldStorage()
#inv_manna = form_manna.getvalue('inv_manna')
#form_gold=cgi.FieldStorage()
#inv_gold = form_gold.getvalue('inv_gold')
inv_manna=10
inv_gold=50

if form.has_key("inventory"):
    inv_manna, inv_gold = form.getvalue("inventory").split(',')

if int(inv_gold)>=100:
    print "Content-type: text/html"
    print
    with open("success.html", 'r') as fin:
        print fin.read()
else:

    # USER HAS ALREADY WON AND ENTERED VALUES
    if form.has_key("gold_output") and form.has_key("manna_output"):
        request_m=form.getvalue('manna_output')
        request_g=form.getvalue('gold_output')
        if(int(request_g)+int(request_m)>5):
                incorrect_output=1
        else:
            url="http://cgi.cs.mcgill.ca/~naharo/cgi-bin/resources.csv"
            response = urllib2.urlopen(url)
            csvFile=csv.reader(response)
            for row in csvFile:
                manna=row[0]
                gold=row[1]

            if int(manna)<int(request_m) or int(gold)<int(request_g):
                incorrect_output=2
            else:
                manna=int(manna)-int(request_m)
                inv_manna=int(inv_manna)+int(request_m)
                gold=int(gold)-int(request_g)
                inv_gold=int(inv_gold)+int(request_g)

                with open('resources.csv', 'w') as resources:
                    writer=csv.writer(resources,delimiter=',')
                    writer.writerow([manna,gold,'1'])
                #FIGURE OUT HOW TO PASS HIDDEN CGI INVENTORY TO C PROGRAM
                if not incorrect_output==2:
                    print "Content-type: text/html"
                    print
                    print """
                    <html>
                    <head>
                    <meta http-equiv="REFRESH" content="0;url=http://cgi.cs.mcgill.ca/~naharo/cgi-bin/room.cgi?inventory=%s%%2C%s&user_input=REFRESH">
                    </head>
                    </html>""" %(inv_manna, inv_gold)
            #IF I FIGURE THIS OUT, DO THE SAME FOR THE TRANSPORTER FILE

    # CORRECT USER INPUT
    if(form.getvalue('user_input') in ['goat'] or (incorrect_output==1 or incorrect_output==2)):
        import csv
        import urllib2

        message=""
        if(incorrect_output==1):
            message="Please only take 1 to 5 of each resource, and 5 maximum in total"
        if(incorrect_output==2):
            message="Please do not take a larger number than the amount that exists in the room's resources"

        url="http://cgi.cs.mcgill.ca/~naharo/cgi-bin/resources.csv"
        response = urllib2.urlopen(url)
        csvFile=csv.reader(response)
        for row in csvFile:
            manna=row[0]
            gold=row[1]
        print "Content-type: text/html"
        print
        print """
        <html>
        <body background="https://previews.123rf.com/images/vitanovski/vitanovski1305/vitanovski130500078/19493512-Cash-Background-Stock-Photo.jpg">
        <h1 style="color:red;text-align:center;"> Well done! Collect your reward </h1>
        <img src="http://www.somepets.com/wp-content/uploads/2013/08/most-hilarious-animals6.jpg"
              alt="goat master"
              style="width:480px;height:350px;margin: 0px auto; display:block;">
        
        <h1 style="color:red;text-align:center;">
                <p>There is %s manna, and %s gold. Take 1-5 of each, for 5 total maximum. <br/>
                %s <br/>
                    <h3> Your Manna is: %s <br>
                     Your Gold is: %s \n
                    </h3>
                    <form action="http://cgi.cs.mcgill.ca/~naharo/cgi-bin/challenge.py" method="post">
                    <input align="center" style="width: 750px; height 100px ; opacity:1;"
                    type="text" name="gold_output" placeholder="Gold: 1 to 5">
                    <input type="hidden" name="inventory" value="%s,%s">
                    <input align="center" style="width: 750px; height 100px ; opacity:1;"
                    type="text" name="manna_output" placeholder="Manna: 1 to 5"> <br/>
                    <input align="center" title="enter" style="width:150px
                        ;height:40px;" type="submit" value="Submit values">
                    </form>
                </h1>
        </body>
        </html>
        """ %(manna, gold, message,inv_manna, inv_gold,inv_manna, inv_gold)

    # FIRST TIME ENTER THE WEBSITE
    elif ("user_input" not in form and "inventory" in form):
        inv_manna, inv_gold = form.getvalue("inventory").split(',')
        print "Content-type: text/html"
        print
        print """
        <html>
        <head><title>Challenge</title></head>
          <body background="http://image.shutterstock.com/z/stock-photo-seamless-pattern-with-petroglyph-goats-handmade-blue-watercolor-goats-on-white-background-222380659.jpg">

            <h1 style="color:red;text-align:center;"> The goat stares wisely into the distance... <br>
            </h1>
        <div style="text-align: center;vertical-align:top">
            <img src="https://s-media-cache-ak0.pinimg.com/originals/8c/d0/6a/8cd06a1e9863595ba76ee9932fc4a164.jpg"
                  alt="goat master"
                  align="middle"
                  style="width:530px;height:400px;margin: 0px auto; display:block;">
            <h3> Your Manna is: %s <br>
                 Your Gold is: %s \n
            </h3>
        </div>
            <h3 style="color:black;text-align:center;"> His first question is: <br> In 1 word or less: what is your favorite animal
            and why is it the goat? <br>
            </h3>
          <form action="challenge.py" method="post" align="center">
            <input type="hidden" name="inventory" value="%s,%s">
            <input align="center" style="width: 750px; height 100px  opacity:0.6;"
            type="text" name="user_input" placeholder="Enter your answer">
            <input title="commands: PLAY, DROP, EXIT, REFRESH" style="width:100px
              ;height:20px;" type="submit" value="Enter">
          </form>
        </body>
        </html>
        """%(inv_manna, inv_gold,inv_manna, inv_gold)

    #OTHER USER INPUT
    elif(form.getvalue('user_input') in ['QUIT']):
        print "Content-type: text/html"
        print
        print """
        <html>
        <head>
        <meta http-equiv="REFRESH" content="0;url=http://cgi.cs.mcgill.ca/~naharo/cgi-bin/room.cgi?inventory=%s%%2C%s&user_input=REFRESH">
        </head>
        </html>""" %(inv_manna, inv_gold)
    else:
        print "Content-type: text/html"
        print
        print """
        <html>
        <head><title>Challenge</title></head>
          <body background="http://image.shutterstock.com/z/stock-photo-seamless-pattern-with-petroglyph-goats-handmade-blue-watercolor-goats-on-white-background-222380659.jpg">

            <h1 style="color:red;text-align:center;"> You got bamboozled! Try again <br>
            </h1>
        <div style="text-align: center;vertical-align:top">
            <img src="https://s-media-cache-ak0.pinimg.com/originals/8c/d0/6a/8cd06a1e9863595ba76ee9932fc4a164.jpg"
                  alt="goat master"
                  align="middle"
                  style="width:530px;height:400px;margin: 0px auto; display:block;">

            <h3> Your Manna is: %s <br>
                 Your Gold is: %s \n
            </h3>
        </div>
            <h3 style="color:black;text-align:center;"> His first question is: <br> In 1 word or less: what is your favorite animal
            and why is it the goat? <br>
            </h3>
          <form action="challenge.py" method="post" align="center">
            <input type="hidden" name="inventory" value="%s,%s">
            <input align="center" style="width: 750px; height 100px  opacity:0.6;"
            type="text" name="user_input" placeholder="Enter your answer">
            <input title="commands: PLAY, DROP, EXIT, REFRESH" style="width:100px
              ;height:20px;" type="submit" value="Enter">
          </form>
          %s
        </body>
        </html>
        """%(inv_manna, inv_gold,inv_manna, inv_gold, form.getvalue("user_input"))
