# file-finder - a coding challenge

OK here it is.  In the vein for keeping things simple, I just dropped some thread functions into main.cpp.

Normally these would be classes, blahblah, but the intent is to demonstrate threading knowledge.

There is an example, non building unit test based on GTest, just to show that this is how it wold be done.

There are lots of warts - for instance:
* CORRECTNESS:::: not checking if the scan is complete before dumping.  Spam the 'd' button, you get inconsistent results.
* exception handling is non existant.
* This code is very inefficient.  Uses way too much CPU.
* I did not run againt a leak detector, but I am "pretty sure" it is not leaking.  :-)
* I am not one to be very concerned about typos.
* let's face it - A lot of error checking is just flat out ignored.

### Building file-finder

You need CMake.  This targets MacOS running:
```
geoffrey@redchip source % clang --version
Apple clang version 15.0.0 (clang-1500.0.40.1)
```

I do not have a VM of Linux with a version of gcc supporting C++17 - but I bet it would work fine.  Same for Windows.

To build file-finder, simply `cd` above the top level directory of this repository.

Then run cmake:
 * cmake -S crwd -B build_crwd
 * cmake --build .

 To run:
    $ ./build_crwd/src/bin/file-finder/file-finder /tmp aa bb
    
## Output
```
geoffrey@redchip source % cmake -S crwd -B build_crwd                            
-- The C compiler identification is AppleClang 15.0.0.15000040
-- The CXX compiler identification is AppleClang 15.0.0.15000040
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /Users/geoffrey/source/build_crwd
geoffrey@redchip source % cmake --build build_crwd                                                     
[ 33%] Building CXX object src/bin/file-finder/CMakeFiles/file-finder.dir/Container.cpp.o
[ 66%] Building CXX object src/bin/file-finder/CMakeFiles/file-finder.dir/main.cpp.o
[100%] Linking CXX executable file-finder
[100%] Built target file-finder
geoffrey@redchip source % ls -l /tmp                                                                   
lrwxr-xr-x@ 1 root  wheel  11 Jan 12 02:19 /tmp -> private/tmp
geoffrey@redchip source % ls -l /tmp/
total 0
-rw-r--r--  1 geoffrey  wheel    0 Feb 28 08:06 aaaaa.pdf
-rw-r--r--  1 geoffrey  wheel    0 Feb 28 08:06 bbbbb.txt
drwxr-xr-x  4 geoffrey  wheel  128 Feb 28 08:07 cccc
-rw-------  1 geoffrey  wheel    0 Feb 26 09:47 com.adobe.acrobat.rna.RdrCefBrowserLock.DC
srwxr-xr-x  1 geoffrey  wheel    0 Feb 26 09:47 com.adobe.reader.rna.0.1f5.DC
srwxr-xr-x  1 geoffrey  wheel    0 Feb 26 09:47 com.adobe.reader.rna.eba.1f5
drwx------  3 geoffrey  wheel   96 Feb 26 09:28 com.apple.launchd.D3DbvwcDCa
drwx------  3 geoffrey  wheel   96 Feb 26 09:28 com.apple.launchd.uAIfIIUx65
srwxrwxrwx  1 geoffrey  wheel    0 Feb 26 09:29 ovpnconnect-local-ipc.sock
drwxr-xr-x  2 root      wheel   64 Feb 26 09:28 powerlog
drwxr-xr-x  2 geoffrey  wheel   64 Feb 27 16:35 {5D1F1DA6-4AA4-C145-8A35-4DC202E24710}
drwxr-xr-x  2 geoffrey  wheel   64 Feb 28 09:10 {BB4FC2DF-49B8-6443-ADE0-EF41DD3D91F9}
geoffrey@redchip source % ls -l /tmp/cccc 
total 0
-rw-r--r--  1 geoffrey  wheel   0 Feb 28 08:07 aaaa.txt
drwxr-xr-x  3 geoffrey  wheel  96 Feb 28 08:07 zzzzz
geoffrey@redchip source % ls -l /tmp/cccc/zzzzz 
total 0
-rw-r--r--  1 geoffrey  wheel  0 Feb 28 08:07 aaaa.txt
geoffrey@redchip source % ./build_crwd/src/bin/file-finder/file-finder /tmp aa bb                      
file-finder starting
file-finder searching: /tmp
d
Dumping container
/tmp/aaaaa.pdf
/tmp/bbbbb.txt
/tmp/cccc/aaaa.txt
/tmp/cccc/zzzzz/aaaa.txt
Dumped 4 values
Dumping container
/tmp/aaaaa.pdf
/tmp/bbbbb.txt
/tmp/cccc/aaaa.txt
/tmp/cccc/zzzzz/aaaa.txt
Dumped 4 values
Dumping container
/tmp/aaaaa.pdf
/tmp/bbbbb.txt
/tmp/cccc/aaaa.txt
/tmp/cccc/zzzzz/aaaa.txt
Dumped 4 values
d
Dumping container
/tmp/aaaaa.pdf
/tmp/bbbbb.txt
/tmp/cccc/aaaa.txt
/tmp/cccc/zzzzz/aaaa.txt
Dumped 4 values
q
file-finder exiting
geoffrey@redchip source % 
```