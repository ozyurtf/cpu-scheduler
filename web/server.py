import http.server
import socketserver
import urllib.parse
import subprocess
import os
import json

PORT = 8000

class Handler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/':
            self.path = '/visualizer.html'
        return http.server.SimpleHTTPRequestHandler.do_GET(self)

    def do_POST(self):
        if self.path == '/run':
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            params = json.loads(post_data.decode('utf-8'))
            
            algo = params.get('algo', 'F')
            input_file = params.get('input', 'input1')
            
            # Allow input0..input9
            allowed_inputs = [f'input{i}' for i in range(10)]
            if input_file not in allowed_inputs:
                input_file = 'input0'
                
            algo_flag = f'-s{algo}'
            
            try:
                # Use current directory scheduler
                cmd = ['./scheduler', '-v', algo_flag, f'test/{input_file}', 'test/rfile']
                res = subprocess.run(cmd, capture_output=True, text=True, check=False)
                
                self.send_response(200)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                
                response = {
                    'trace': res.stdout
                }
                self.wfile.write(json.dumps(response).encode('utf-8'))
                
            except Exception as e:
                self.send_response(500)
                self.send_header('Content-type', 'text/plain')
                self.end_headers()
                self.wfile.write(str(e).encode('utf-8'))
        else:
            self.send_error(404, "Not Found")

socketserver.TCPServer.allow_reuse_address = True
with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print(f"Serving at http://localhost:{PORT}")
    httpd.serve_forever()
