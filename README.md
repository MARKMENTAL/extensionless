# Extensionless Web Framework

This C-based web framework allows you to serve HTML, CSS, and image files (PNG, JPG, JPEG) without requiring extensions. It provides a minimalist approach to web development, designed for optimal performance and compatibility with low-spec systems.

## Features

- Extensionless routing for HTML, CSS, PNG, JPG, and JPEG files.
- File-based routing for quickly putting together web applications.
- Minimalist design for performance and efficiency.
- Compatibility with low-spec systems, tested on VMs with less than 4GB of RAM.
- Serves files from the directory the program is running in.

## Dependencies

The framework relies on GNU Libmicrohttpd (microhttpd), a C library that provides a simple HTTP server. You'll need to have this library installed in your system to compile the framework. Visit the [GNU Libmicrohttpd website](https://www.gnu.org/software/libmicrohttpd/) for more information and installation instructions.

## Getting Started

### Running the Server

1. Compile and build the server code using a C compiler (e.g., GCC).
2. Run the compiled executable.
3. Access the web app by visiting `http://localhost:8000` in your browser.

### Compile and Run Script

To simplify the compilation and running process, an included script named `compile_run.sh` can be used. Here's how to use it:

1. Open a terminal in the directory containing the framework's files.
2. Run the following command to make the script executable:
   ```bash
   chmod +x compile_run.sh
   ```
3. Run the script:
   ```bash
   ./compile_run.sh
   ```
4. Access the web app by visiting `http://localhost:8000` in your browser.

### Routing and File Serving

The framework automatically handles routing and serves HTML, CSS, and image files without requiring extensions. Simply place your files in the same directory as the executable and access them using clean, extensionless URLs.

### Example HTML Page

The framework comes with an example HTML page. You can explore and modify this page to learn more about how the framework works and how to customize it to your needs.

## Customization

### Linking to Other Pages

You can easily link to other pages in the same directory using relative URLs. The framework will handle the routing for you.

### Styling

The provided example HTML page uses Bootstrap styling. Feel free to enhance it by adding your own CSS or using a front-end framework.

## Security Considerations

The code includes path sanitation to prevent malicious path traversal attempts, ensuring the security of your web application.

## Contributing

Feel free to modify the code and adapt it to your specific needs. If you encounter any issues or have suggestions for improvements, please submit a pull request or open an issue on the repository.
