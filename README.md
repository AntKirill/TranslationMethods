# Lab2 for translation methods course

## Dependencies

Project uses Graphviz shared library. So the library is needed to be installed to /usr/lib/

## For building 
Go to the build folder and do

```bash
cmake ..
make
```

## For testing 

Go to build folder and write Paskal funtion/procedure declaration to input.txt. After that do

```bash
./Lab2
```

When parsing is finished with no errors, the file output.png that contains visualization of tree will be created at build and command 

```bash
xdg-open output.png
```

is automatically run.

If there is no input.txt at build then message about it appears on stderr and  parser is tested on all of the tests of folder tests/.

If something goes wrong the message about it appers on stderr.

## Example of output tree 
For test: function f(a8, _b, c, d,e,f,g: integer; g : double; Straustrup: String):int;

![alt text](https://user-images.githubusercontent.com/17815649/31891307-af6084fc-b80e-11e7-8bcc-d0f465eb9bbd.png)