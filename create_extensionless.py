# Import the os, glob, and re modules to check for existing HTML files and find links
import os
import glob
import re

# Ask the user for the filename of the page (without extension)
filename = input("Enter the filename of the page (without extension): ")

# Check if the file already exists
if os.path.exists(filename + ".html"):
    # If yes, print an error message and exit
    print("Error: A file with that name already exists.")
    exit()
else:
    # If not, create a new file with that name and extension
    file = open(filename + ".html", "w")

    # Ask the user for the basic content to be in the page
    title = input("Enter the title of the page: ")
    heading = input("Enter the main heading of the page: ")
    paragraph = input("Enter a paragraph of text for the page: ")

    # Get a list of all HTML files in the same directory (excluding the current one)
    html_files = [f for f in glob.glob("*.html") if f != filename + ".html"]

    # Initialize an empty list to store the button links
    buttons = []

    # Loop through the HTML files
    for f in html_files:
        # Get the base name of the file (without extension)
        base_name = os.path.splitext(f)[0]

        # Capitalize the first letter of the base name
        button_text = base_name.capitalize()

        # Get the path of the file (relative to the current directory) without extension
        button_link = "/" + base_name

        # Append a tuple of button text and link to the list
        buttons.append((button_text, button_link))

    # Find all links in the paragraph using a regular expression
    links = re.findall(r"https?://\S+", paragraph)

    # Loop through the links
    for link in links:
        # Replace each link with an <a> tag with target="_blank" set
        paragraph = paragraph.replace(link, f'<a href="{link}" target="_blank">{link}</a>')

    # Write the HTML template to the file, using the user input as content
    file.write(f"""<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <link href="/bootstrap.min" rel="stylesheet"><!-- Replace "/path/to/bootstrap.min.css" with the actual path to your Bootstrap CSS file -->
    <title>{title}</title>
</head>
<body>
    <div class="container mt-5">
        <div class="card border-0 shadow p-3 mb-5 bg-light rounded">
            <div class="card-body">
                <h1 class="display-4">{heading}</h1>
                <p class="lead">{paragraph}</p>
                <!-- Loop through the button links and create a Bootstrap button for each one -->
                {"".join([f'<a href="{link}" class="btn btn-primary btn-lg">{text}</a>' for text, link in buttons])}
            </div>
        </div>
    </div>
</body>
</html>""")

    # Close the file
    file.close()

    # Print a success message
    print(f"Successfully created {filename}.html")
