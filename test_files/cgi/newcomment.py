import json
import os
from urllib.parse import parse_qs
import sys

# Get the content length from the CONTENT_LENGTH environment variable
content_length = int(os.environ.get('CONTENT_LENGTH', 0))

# Read the request body from stdin
request_body = sys.stdin.read(content_length)

# # Get the value of the QUERY_STRING environment variable
# query_string = os.environ.get('QUERY_STRING')

# Parse the query string into JSON
query_params = parse_qs(request_body)

# Convert the parsed query parameters into JSON format
new_object = {key: value[0] for key, value in query_params.items()}

# Read JSON data from file
with open('cgi/comments.json', 'r') as file:
    json_data = json.load(file)

# Access the array within JSON data
array_data = json_data['comments']

# Add the new object to the array
array_data.append(new_object)

# Write the updated JSON data back to the file
with open('cgi/comments.json', 'w') as file:
    json.dump(json_data, file, indent=4)

print("Location:guestbook.py\r\n")

print("Object added to the array in the JSON file.")