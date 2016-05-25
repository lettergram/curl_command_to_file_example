cURL --libcurl Example
====

One thing I never realized, was I could use the command:

    $ curl http://austingwalters.com --libcurl austingwalters.c

To export a curl call to a c file, which can then be compiled by adding '-lcurl':

    $ gcc austingwalters.c -lcurl

This has helped me create several funcions which call APIs in C within minutes.
