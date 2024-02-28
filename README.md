# file-finder - a coding challenge

OK here it is.  In the vein for kiiding things simple, I just dropped some thread functions into main.cpp.

There is an example, non building unit test based on GTest, just to show that this is how it wold be done.

There are lots of warts - for instance:
* not checking if the scan is complete before dumping.  Spam the d button, you get inconsistent results.
* exception handling is non existant.
* This code is very inefficient as well.

### Building file-finder

To build file-finder, simply `cd` above the top level directory of this repository.

Then run cmake:
    > cmake -S crwd -B build_crwd
    > cmake --build .

 To run:
    $ ./build_crwd/src/bin/file-finder/file-finder /tmp aa bb
    