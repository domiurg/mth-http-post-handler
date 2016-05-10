from BaseHTTPServer import BaseHTTPRequestHandler
from os import curdir, sep
import SocketServer
import cgi

PORT = 8000


class PostHandler(BaseHTTPRequestHandler):

    def do_POST(self):
        # Parse the form data posted
        form = cgi.FieldStorage(
            fp=self.rfile,
            headers=self.headers,
            environ={'REQUEST_METHOD': 'POST',
                     'CONTENT_TYPE': self.headers['Content-Type'],
                     })
        # Iterate over Key-Value pair
        for key in form.keys():
            print key, form.getvalue(key)
        return


httpd = SocketServer.TCPServer(("", PORT), PostHandler)
print("Server Up")

httpd.serve_forever()

