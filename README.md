# Extensionless Web Framework

This Python-based web framework allows you to serve HTML, CSS, and image files (PNG, JPG, JPEG) without requiring extensions. It also includes a component generator to help create new HTML pages with consistent styling and comes with an example HTML page and the Morph Bootswatch theme to get started quickly.

## Features

- Extensionless routing for HTML, CSS, PNG, JPG, and JPEG files.
- File-based routing for quickly putting together web applications.
- Component generator to create new HTML pages with Bootstrap styling and ready-to-customize templates.
- Component creator feature: Automatically converts URLs in the input paragraph into clickable links in the created HTML page.
- Serves files from the directory the script is running in.
- Comes with an example HTML page and Morph Bootswatch theme for immediate use and customization.
- Does not require any libraries outside of a default Python 3 install.

## Getting Started

### Running the Server

1. Save the server code as `extensionless.py`.
2. In the terminal, navigate to the directory containing the `extensionless.py` file and the example HTML page.
3. Run the following command:
   ```bash
   python3 extensionless.py
   ```
4. Access the web app by visiting `http://localhost:8000` in your browser.

### Using the Component Generator

1. Save the component generator code as `create_extensionless.py`.
2. In the terminal, navigate to the directory containing the `create_extensionless.py` file.
3. Run the following command:
   ```bash
   python3 create_extensionless.py
   ```
4. Follow the prompts to enter the title, heading, and paragraph for the new page.
5. **Note:** The component creator is designed to provide a basic HTML template that you can tweak and customize after creation. It includes Bootstrap classes and automatically generated links to facilitate your customizations.

### Example HTML Page and Theme

The framework comes with an example HTML page and Morph Bootswatch theme. You can explore and modify this page to learn more about how the framework works and how to customize it to your needs.

## Customization

### Linking to Other Pages

The component generator will automatically create navigation buttons for other HTML files in the directory.

### Styling

You can easily customize the styling by modifying the Bootstrap classes in the generated HTML files or changing the Bootswatch theme.

## Security Considerations

The code includes path sanitation to prevent malicious path traversal attempts.

## Contributing

Feel free to modify the code and adapt it to your specific needs.
