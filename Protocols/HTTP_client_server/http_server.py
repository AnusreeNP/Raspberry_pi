#!/usr/bin/env python

from http.server import BaseHTTPRequestHandler, HTTPServer
import os

#Create custom HTTPRequestHandler class
class CustomHTTPRequestHandler(BaseHTTPRequestHandler):

    #handle GET command
    def do_GET(self):
        rootdir = '/home/anusree/' #file location
        try:
            if self.path.endswith('.html'):
                f = open(rootdir + self.path) #open requested file

                #send code 200 response
                self.send_response(200)

                #send header first
                self.send_header('Content-type','text-html')
                self.end_headers()

                #send file content to client
                self.wfile.write(f.read().encode())
                f.close()
                return

        except IOError:
            self.send_error(404, 'file not found')

def run():
    print('http server is starting...')

    #ip and port of servr
    #by default http server port is 80
    port = 8080
    server_address = ('127.0.0.1', port)
    httpd = HTTPServer(server_address, CustomHTTPRequestHandler)
    print('http server is running on port ' + str(port))
    httpd.serve_forever()

if __name__ == '__main__':
    run()
