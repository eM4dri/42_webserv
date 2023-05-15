
use strict;
use warnings;
use CGI;

# Inserting '\' before dollar sign to prevent variable substitution from bash
my $cgi = CGI->new;
# Array of query keys
my @q_keys;

# Subroutine to add an HTML paragraph
sub addParagraph {
  print "<p>";
  # Extracts the first item off the list of arguments and prints it
  print shift;
  print "</p>";
}
# Prints Content-Type: text/html
print $cgi->header;
# Opens html and body tags and sets the argument as title
print $cgi->start_html("Query Parameters");
# Inserts query keys into array
@q_keys = $cgi->param();
# Checks if array is empty
if (@q_keys == 0) {
  addParagraph("Include query parameters in the url.");
  addParagraph("Example: localhost:9000/query.pl?hola=mundo&hello=world");
}
else {
  my $key;
  my $value;

  foreach $key (@q_keys) {
    $value = $cgi->param($key);
    addParagraph("$key = $value");
  }
}
# Closes html and body tags
print $cgi->end_html;
