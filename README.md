http-tiny
=========

http-tiny 1.2 improvments

http-tiny is good implementation of HTTP for embedded 
applications.

For support basic auth you should be implement your own
function for base64 encoding or use another one, see
http-basic-auth.c for example of implementation.

Added multi-thread support with functions httpmt.

- http\_post added
- http\_set\_basic\_auth added
- http_read_buffer_eof (GET/POST support for read body without Content length header field) 
- httpmt\_\*.

TODO

- Update manual pages.
