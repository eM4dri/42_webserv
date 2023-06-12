use CGI;
use CGI::Cookie;

# Retrieve the value of a cookie
sub get_cookie_value {
    my ($cookie_name) = @_;

    my $cookie = CGI::Cookie->fetch();
    return $cookie->{$cookie_name}->value if $cookie->{$cookie_name};

    return undef;
}

# Set a cookie
sub set_cookie {
    my ($cookie_name, $cookie_value, $expires) = @_;

    my $cookie = CGI::Cookie->new(
        -name    => $cookie_name,
        -value   => $cookie_value,
        -expires => $expires
    );

    print "Set-Cookie: $cookie\r\n";
}

# Retrieve QUERY_STRING
my $query_string = $ENV{'QUERY_STRING'};

# Create a CGI object
my $cgi = CGI->new($query_string);

# Retrieve the value of a specific key
my $value = $cgi->param('username');


# Example usage
my $cookie_name = '42_cookie_username';

# Get the value of a cookie named 'username'
my $username = get_cookie_value($cookie_name);
if (!$username) {
    set_cookie($cookie_name, 'Marvin', '+1h');
}
if ($value){
    set_cookie($cookie_name, $value, '+1h');
}
print "Content-type:text/html\r\n\r\n";
if ($username) {
    print "Welcome back, $username!\r\n";
} else {
    print "Welcome, new user!\r\n";
}
