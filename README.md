http-tiny 1.2 support for POST and Basic auth

For support basic auth you should be implement your own
function for base64 encoding or use another one, see
http\_set\_base64\_encoder.

- http\_post added
- http\_set\_basic\_auth added
