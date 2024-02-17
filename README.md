# Extensionless Web Framework

This C-based web framework enables the serving of HTML, CSS, and image files (PNG, JPG, JPEG) without requiring extensions in the URLs. It is specifically designed for lightweight applications, focusing on serving small text files, modest CSS, and images efficiently. With an emphasis on performance and compatibility, this framework is particularly suited for systems with limited resources.

## Features

- **Extensionless Routing**: Serve HTML, CSS, PNG, JPG, and JPEG files directly without needing URL extensions.
- **File-Based Routing**: Easily assemble web applications with direct URL-to-file mapping.
- **Minimalist Design**: Engineered for maximum efficiency and minimal overhead, perfect for high-performance needs.
- **Low-Spec System Compatibility**: Runs smoothly on systems with minimal hardware specifications, tested on VMs with less than 4GB of RAM.
- **Local Directory Serving**: Serves files from the executing directory, simplifying deployment and management.
- **1MB File Size Limit**: By default, the server will not serve files larger than 1MB, prioritizing quick load times and resource conservation.

## Dependencies

This framework is self-contained, requiring **no external dependencies**. It leverages standard C libraries and built-in network and socket libraries for all server functionalities. This enhancement in design by removing GNU Libmicrohttpd as a dependency makes the framework more accessible and straightforward for users and developers alike.

## Getting Started

### Running the Server

1. Compile the server code using a C compiler like GCC.
2. Execute the compiled binary to start the server.
3. Access the web app by navigating to `http://localhost:8000` in your browser.

### Compile and Run Script

A script, `compile_run.sh`, is provided to streamline compilation and execution:

1. In the framework's directory, open a terminal.
2. Make the script executable:
   ```bash
   chmod +x compile_run.sh
   ```
3. Execute the script:
   ```bash
   ./compile_run.sh
   ```
4. The web app will be accessible at `http://localhost:8000`.

### Routing and File Serving

Place your files in the server's directory to access them via clean, extensionless URLs. The framework handles routing automatically, allowing for a neat and organized file structure.

### Example HTML Page

An example HTML page is included to demonstrate the framework's capabilities. This example can be customized or expanded to fit your project's needs.

## Customization

### Linking to Other Pages

Utilize relative URLs for seamless linking between pages within your application, facilitated by the framework's efficient routing mechanism.

### Styling

The sample page uses Bootstrap for styling, but you are encouraged to apply custom CSS or integrate other styling libraries to personalize your application.

## Security Considerations

The framework includes basic path sanitation to guard against path traversal attacks, contributing to the security of applications built with it.

## Contributing

Contributions are welcome! Feel free to adapt the code, suggest enhancements, or report issues. If you make improvements, please consider submitting a pull request or opening an issue on GitHub.

