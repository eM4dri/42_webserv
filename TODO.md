**To keep tracking everything we acknowledge as TODO**
- [X] Validate route path of request
- [X] Integrate conf with request
- [X] Use albgarci's ubuntu docker
	> Included section on `NOTES.md` explaining how to use this
- [X] Formats unifing passing (`const &`, private var and methods,...)
	> About `const &` https://42born2code.slack.com/archives/CNA2Z8RBP/p1680868478345079
- [X] Validate multiple locations on same level on loading `.conf` example `location	/file /hola	`
- [X] Parse index on `conf` default page
- [X] Parse `conf` configure root in every location, apeeding server root
- [X] Create default `/` location
- [X] Cgi
- [X] Apply `correct_path()` on `conf` default_root, file_root & request_path.
	> Return KO if not complains `valid_path` on conf files (starts with `/`, not end with `/`, `.`,`{`, `~`, not allowed `//`,`/./``/../``/~/`)
- [X] Fix errors `example.conf` look for kapouet
- [X] Handle error with throws `conf`
- [X] Agreed Cgi comunications between Request or responses
- [X] Unit test parsed redirect to test circular references, using mock methods for valid redirect
- [X] use `curl` verbose to review  HTTP header response  curl -v localhost:8080
- [X] Review why main cannot launch two servers at the same time (edu)
- [X] Parse body on `POST`
- [X] Review `POST` removing files contents
- [X] Disable validate directory on redirects
- [X] Review parse locations