**To keep tracking everything we acknowledge as TODO**
- [ ] Validate route path of request
- [ ] Integrate conf with request
- [X] Use albgarci's ubuntu docker
> Included section on `NOTES.md` explaining how to use this
- [ ] Formats unifing passing (`const &`, private var and methods,...)
> About `const &` https://42born2code.slack.com/archives/CNA2Z8RBP/p1680868478345079
- [ ] Validate multiple locations on same level on loading `.conf` example `location	/file /hola	`
- [ ] Parse index on `conf` default page
- [X] Parse `conf` configure root in every location, apeeding server root
- [X] Create default `/` location
- [X] Cgi
- [F] Apply `correct_path()` on `conf` default_root, file_root & request_path.
> Return KO if not complains `valid_path` on conf files (starts with `/`, not end with `/`, `.`,`{`, `~`, not allowed `//`,`/./``/../``/~/`)
- [X] Fix errors `example.conf` look for kapouet
- [X] Handle error with throws `conf`
- [ ] Agreed Cgi comunications between Request or responses
- [ ] Unit test parsed redirect to test circular references, using mock methods for valid redirect