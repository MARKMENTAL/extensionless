import http.server
import socketserver
import os

# Define the port for the web server
PORT = 8000

# Set up a custom request handler to serve files from the current directory
class CustomHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        # Get the requested path
        path = self.path

        # If the path ends with '/', add 'index.html' to serve 'index.html'
        if path.endswith('/'):
            path += 'index.html'

        # Sanitize the path
        sanitized_path = os.path.abspath(os.path.normpath('.' + path))
        if not sanitized_path.startswith(os.path.abspath('.')):
            self.send_error(403, 'Access Denied')
            return

        # Check if the requested file exists and is a '.html', '.css', '.png', '.jpg', or '.jpeg' file
        for ext in ['.html', '.css', '.png', '.jpg', '.jpeg']:
            file_path = sanitized_path if sanitized_path.endswith(ext) else sanitized_path + ext
            if os.path.exists(file_path):
                self.send_response(200)

                # Set appropriate Content-type based on file extension
                if file_path.endswith('.html'):
                    self.send_header('Content-type', 'text/html')
                elif file_path.endswith('.css'):
                    self.send_header('Content-type', 'text/css')
                elif file_path.endswith(('.png', '.jpg', '.jpeg')):
                    self.send_header('Content-type', 'image/' + ext.strip('.'))

                self.end_headers()

                # Open the file and send its contents as the response
                with open(file_path, 'rb') as file:
                    self.wfile.write(file.read())
                return

        # If the file doesn't exist or is not an acceptable extension, return a 404 error
        self.send_error(404, 'Extension Search Exhausted: File Not Found')

# Create the server with the custom handler
with socketserver.TCPServer(("", PORT), CustomHandler) as httpd:
    print(f"extensionless Server started on port {PORT}")

    try:
        # Start the server and keep it running until interrupted
        httpd.serve_forever()
    except KeyboardInterrupt:
        # Gracefully shut down the server when CTRL+C is pressed
        httpd.shutdown()
        print("\nServer stopped.")
