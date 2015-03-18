*Libgvar* is a library that is used to parse the incoming GOES GVAR
Stream.  The GVAR stream is described in depth in the
[GOES Tech Notes](http://goes.gsfc.nasa.gov/text/goestechnotes.html).
The library is used most importantly in the grass program r.in.gvar
which reads the GVAR stream, and converts the stream to GRASS
datafiles.  

There is also a *gvar_inspector* code which will allow usres to investigate a GVAR file.

# Compiling

## Redhat
```
#!bash
yum install boost boost-program-options
```

To compile the library.

```
#!bash
./configure --prefix=<the directory you want the library to be generated>
make
sudo make install
```

Developers can recreate the autogenerated files by running 
```
#!bash
./bootstrap
```

# History

Starting around 2003 the CSTARS program began modeling incoming solar
radiation for California from GOES satellite data.  We manipulate the
rasters using grass.  The libgvar library was written to allow us to
import the realtime gvar stream directly into grass.

