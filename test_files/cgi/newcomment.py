import json
import os
from urllib.parse import parse_qs

# Get the value of the QUERY_STRING environment variable
query_string = os.environ.get('QUERY_STRING')

# Parse the query string into JSON
query_params = parse_qs(query_string)

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

print("Location:guestbook.py")

print("Object added to the array in the JSON file.")