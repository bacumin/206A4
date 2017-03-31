#!/usr/bin/env python
# -*- coding: UTF-8 -*-
print("Content-type: text/html")
print()
print(""")
<html>

<head><title>Sample cgi script</title></head>

<body>

    <h3> sample h3 </h3>
"""

import cgi
form=cgi.FieldStorage()
message=form.getvalue("message", "(no message)")

print(""")

 <p>Previous message: %s</p>

    <p>form

        <form method="post" action="index.cgi">
        <p>message: <input type="text" name="message"/></p>
    </form>

</body>

</html>
""" % cgi.escape(message)
