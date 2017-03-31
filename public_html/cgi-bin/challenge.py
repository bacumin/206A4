#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import cgi
import cgitb; cgitb.enable()  # for troubleshooting

print "Content-type: text/html"
print

print """
<html>

<head><title>Sample CGI Script</title></head>


  <body background="http://image.shutterstock.com/z/stock-photo-seamless-pattern-with-petroglyph-goats-handmade-blue-watercolor-goats-on-white-background-222380659.jpg">
    <h1 style="color:red;text-align:center;"> The goat stares wisely into the distance... <br>
    </h1>

    <img src="https://s-media-cache-ak0.pinimg.com/originals/8c/d0/6a/8cd06a1e9863595ba76ee9932fc4a164.jpg"
          alt="goat master"
          style="width:530px;height:400px;margin: 0px auto; display:block;">

    <h3 style="color:black;text-align:center;"> He has only one question: <br> In 1 word or less: what is your favorite animal
    and why is it the goat? <br>
    </h3>
"""

form = cgi.FieldStorage()
message = form.getvalue("message", "(no message)")

print """

  <form action="challenge.py" method="post" align="center">
    <input align="center" style="width: 750px; height 100px  opacity:0.6;"
    type="text" name="user_input" placeholder="Enter your answer">
    <input title="commands: PLAY, DROP, EXIT, REFRESH" style="width:100px
      ;height:20px;" type="submit" value="Enter">
  </form>

</body>

</html>
"""
if(form.getvalue('user_input') in ['goat']):
    import csv
    import urllib2
    url="http://cgi.cs.mcgill.ca/~bcumin1/resources.csv"
    response = urllib2.urlopen(url)
    csvFile=csv.reader(response)
    for row in csvFile:
        manna=row[0]
        gold=row[1]

    print """
    <html>
    <body background="https://previews.123rf.com/images/vitanovski/vitanovski1305/vitanovski130500078/19493512-Cash-Background-Stock-Photo.jpg">
    <h1 style="color:red;text-align:center;"> Well done! Scroll to collect your reward </h1>
    <img src="http://www.somepets.com/wp-content/uploads/2013/08/most-hilarious-animals6.jpg"
          alt="goat master"
          style="width:530px;height:400px;margin: 0px auto; display:block;">

    <h1 style="color:red;text-align:center;">
            <p>There is: %s manna
                <form action="http://cgi.cs.mcgill.ca/~bcumin1/room.html">
                <input title="commands: PLAY, DROP, EXIT, REFRESH" style="width:150px
                      ;height:40px;" type="submit" value="Take the manna">
                      </p>
                </form>
            <p>There is: %s gold
                <form action="http://cgi.cs.mcgill.ca/~bcumin1/room.html" method="post" align="center">
                <input align="center" title="commands: PLAY, DROP, EXIT, REFRESH" style="width:150px
                    ;height:40px;" type="submit" value="Take the gold"></p>
                </form>
            </h1>
    </body>
    </html>
    """ %(manna, gold)
elif(form.getvalue('user_input') in ['PLAY']):
    print """
    <html>
    </html>
    """
elif(form.getvalue('user_input') in ['QUIT']):
    print """
    <html>
    <META http-equiv="refresh" content="2;URL=http://cgi.cs.mcgill.ca/~bcumin1/room.html">
    </html>
    """
else:
    print """
    <html>
    <body>
    <h1 style="color:red;text-align:center;"> You got bamboozled! Try again </h1>
    </body>
    </html>
    """
