**To keep tracking everything we acknowledge as TODO**
- [ ] Validate route path of request
- [X] Integrate conf with request
- [X] Use albgarci's ubuntu docker
	> Included section on `NOTES.md` explaining how to use this
- [X] Formats unifing passing (`const &`, private var and methods,...)
	> About `const &` https://42born2code.slack.com/archives/CNA2Z8RBP/p1680868478345079
- [ ] Validate multiple locations on same level on loading `.conf` example `location	/file /hola	`
- [X] Parse index on `conf` default page
- [X] Parse `conf` configure root in every location, apeeding server root
- [X] Create default `/` location
- [X] Cgi
- [F] Apply `correct_path()` on `conf` default_root, file_root & request_path.
	> Return KO if not complains `valid_path` on conf files (starts with `/`, not end with `/`, `.`,`{`, `~`, not allowed `//`,`/./``/../``/~/`)
- [X] Fix errors `example.conf` look for kapouet
- [X] Handle error with throws `conf`
- [ ] Agreed Cgi comunications between Request or responses
- [ ] Unit test parsed redirect to test circular references, using mock methods for valid redirect
- [ ] use `curl` verbose to review  HTTP header response  curl -v localhost:8080
- [ ] Review why main cannot launch two servers at the same time (edu)
- [ ] Parse body on `POST`
- [ ] Review `POST` removing files contents
- [ ] Disable validate directory on redirects
	> [ ] Find out if a return location/file should redirect (edu)
- [ ] Add guestbook demo card detail and delete workflow (Must be handleled with POST, HTTP delete not used for cgi)
	> Add id json DataBase like Primary key, auto incremental with every new message
	> Add Url on every card with redirects to the same path with ?id=id
	> Filter Guestbook for id when query string comes with it
	> Add a buton delete on this detail version to redirect a deletecomment.py -> get inspiration from newcomment.py