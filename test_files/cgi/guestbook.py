
import json
import os
from urllib.parse import parse_qs

# Get the value of the QUERY_STRING environment variable
query_string = os.environ.get('QUERY_STRING')

# Parse the query string into JSON
query_params = parse_qs(query_string)

# Read JSON data from a file
with open('cgi/comments.json') as file:
    json_data = json.load(file)

print("Content-type:text/html")
print()

print("<!DOCTYPE html>")
print("<html lang=\"en-US\">")
print("<head>")
print("<title>Guestbook</title>")
print("<style>")
print(".card {")
print("border: 1px solid #ccc;")
print("border-radius: 4px;")
print("box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);")
print("width: 300px;")
print("margin: 10px;")
print("padding: 20px;")
print("}")
print(".card h3 {")
print("margin-top: 0;")
print("}")
print(".card p {")
print("margin-bottom: 0;")
print("}")
print("</style>")
print("</head>")
print("<body>")
print("<h2>Guest book</h2>")

comments = json_data['comments']

if query_params:
    # Convert the parsed query parameters into JSON format
    new_object = {key: value[0] for key, value in query_params.items()}
    filtercomments = [x for x in comments if x['user_login'] == new_object['login']]
    for comment in filtercomments:
        print("<div class=\"card\">")
        print("<h3>", comment['user_login'],"</h3>")
        print("<p>", comment['user_message'],"</p>")
        print("</div>")

else :
    for comment in comments:
        print("<div class=\"card\">")
        print("<h3>", comment['user_login'],"</h3>")
        print("<p>", comment['user_message'],"</p>")
        print("</div>")

print("<button onclick=\"redirectToURL()\">New message</button>")

print("<script>")
print("function redirectToURL() {")
print("window.location.href = \"newmessage.html\";")
print("}")
print("</script>")
print("</body>")
print("</html>")