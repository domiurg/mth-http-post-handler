from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
from SocketServer import ThreadingMixIn
import cgi
import threading

#from os import curdir, sep

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


class ThreadedHTTPServer(ThreadingMixIn, HTTPServer):
    """handle requests in a separate thread"""

# httpd = SocketServer.TCPServer(("", PORT), PostHandler)
# print("Server Up")
# httpd.serve_forever()

server = ThreadedHTTPServer(('', PORT), PostHandler)
print 'Starting server, use <Ctrl-C> to stop'
server.serve_forever()