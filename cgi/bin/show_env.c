#include <unistd.h>
#include <stdlib.h>
#include <string.h>


const char *ENV[ 24 ] = {
   "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE",
   "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",
   "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",
   "HTTP_HOST", "HTTP_USER_AGENT", "PATH",
   "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",
   "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
   "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",
   "SERVER_NAME","SERVER_PORT","SERVER_PROTOCOL",
   "SERVER_SIGNATURE","SERVER_SOFTWARE" };

void	ft_putstr_fd(const char *str, int fd)
{
	write(fd, str, strlen(str));
}

int main () {
   ft_putstr_fd("Content-type:text/html\r\n\r\n", STDOUT_FILENO);
   ft_putstr_fd("<html>\n", STDOUT_FILENO);
   ft_putstr_fd("<head>\n", STDOUT_FILENO);
   ft_putstr_fd("<title>CGI Environment Variables</title>\n", STDOUT_FILENO);
   ft_putstr_fd("</head>\n", STDOUT_FILENO);
   ft_putstr_fd("<body>\n", STDOUT_FILENO);
   ft_putstr_fd("<table border = \"0\" cellspacing = \"2\">", STDOUT_FILENO);

   for ( int i = 0; i < 24; i++ ) {
      ft_putstr_fd("<tr><td>", STDOUT_FILENO);
      ft_putstr_fd(ENV[ i ], STDOUT_FILENO);
      ft_putstr_fd("</td><td>", STDOUT_FILENO);

      // attempt to retrieve value of environment variable
      char *value = getenv( ENV[ i ] );
      if ( value != 0 ) {
         ft_putstr_fd(value, STDOUT_FILENO);
      }
	  else {
         ft_putstr_fd("Environment variable does not exist.", STDOUT_FILENO);
      }
      ft_putstr_fd("</td></tr>\n", STDOUT_FILENO);
   }

   ft_putstr_fd("</table>\n", STDOUT_FILENO);
   ft_putstr_fd("</body>\n", STDOUT_FILENO);
   ft_putstr_fd("</html>\n", STDOUT_FILENO);

   return 0;
}
