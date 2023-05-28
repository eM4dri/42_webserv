- ¿Delete remove directories?
	> (pmira-pe) No, It doesn't, just files
- Chunks
	> Not implemeted or similar Maximun size
- Post files
	> ok
- Must CGI support HTTP delete?
	> (chatgpt )No, CGI does not specifically support or require the use of HTTP methods like DELETE.HTTP methods like GET, POST, and HEAD are commonly used with CGI scripts to handle form submissions, retrieve data, and perform other operations.

- Can the class `cgi` fail to construct? (Wrong path controlled by exceptions or status variables...)
	> No can''t fail to answer on execve behaviour or similar funcions.

- If so, does it need to be controlled here or does the `get_cgi_response()` method handle it?
	> All this errors must be handleded inside cgi class and shouldn't stop the server,
	> but the conected client has to receive an appropiate respnse, so we need to figure out a way do this
	> since the server.ccp get a request.cpp, to get a response.cpp wich calls cgi.cpp,
	> and we need to return this answer back to the client throught server.cpp,
	> maybe we need some agreed return variable to left the response on response.ccp,
	> or just call a formated error response

- Is this the last modification of the CGI file itself or the date of creation of the CGI's output?
	> This is one of the HTTP Header wich could be returned by cgi https://www.tutorialspoint.com/cplusplus/cpp_web_programming.htm
	> so I guess we can left at cgi will
	> by the way cgi returns this HTTP Headers with correct format, no need to do more work