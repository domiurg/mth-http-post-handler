#!/usr/bin/python

from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
from SocketServer import ThreadingMixIn
import cgi
import threading
import MySQLdb

PORT = 8000


class PostHandler(BaseHTTPRequestHandler):
    def do_POST(self):

        # # Define DB Object
        # db = MySQLdb.connect(host='domiurg-lab.duckdns.org',
        #                      user='arduino_user',
        #                      passwd='sometext',
        #                      db='arduino_user')
        # # Create Cursor object
        # # It will execute all our queries
        # cur = db.cursor()

        # Parse the form data posted
        form = cgi.FieldStorage(
            fp=self.rfile,
            headers=self.headers,
            environ={'REQUEST_METHOD': 'POST',
                     'CONTENT_TYPE': self.headers['Content-Type'],
                     })

        # Start constructing MySQL query

        # First try to create table if it does not exist
        # Differentiate tables by number of parameters
        # i.e data_<number_of_parameters>
        # and prepare header for the Insertion Query
        create_query = 'CREATE TABLE IF NOT EXISTS data_' + str(len(form.keys())) + ' (' \
                        'id int(11) NOT NULL AUTO_INCREMENT, '

        insert_query = 'INSERT INTO data_' + str(len(form.keys())) + ' ('
        # Iterate over Keys for DB Row names
        for key in form.keys():
            create_query += str(key) + ' varchar(50) DEFAULT NULL, '
            insert_query += str(key) + ','
        create_query += 'PRIMARY KEY (id));'

        insert_query = insert_query[:len(insert_query) - 1]
        insert_query += ') VALUES ('

        # Execute Creation query
        #cur.execute(create_query)

        # Next Prepare data for insertion query
        # Iterate over Key-Value pair
        for key in form.keys():
            insert_query += "'" + str(form.getvalue(key)) + "'" + ','
            print key, form.getvalue(key)

        insert_query = insert_query[:len(insert_query) - 1]
        insert_query += ');'

        # Execute data insertion query
        #cur.execute(insert_query)

        # Make sure that changes are commited to DB
        #db.commit()

        print create_query
        print insert_query
        # print threading.currentThread().getName()

        # db.close()
        return


class ThreadedHTTPServer(ThreadingMixIn, HTTPServer):
    """handle requests in a separate thread"""


server = ThreadedHTTPServer(('', PORT), PostHandler)
print 'Starting server, use <Ctrl-C> to stop'
server.serve_forever()
