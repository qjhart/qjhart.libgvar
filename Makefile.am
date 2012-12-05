MAINTAINERCLEANFILES    = Makefile.in
ACLOCAL_AMFLAGS = -I m4

pkginclude_HEADERS      = selFloat.h cdaTime.h  frameCheck.h  gvar.h Gvar.h  LineDoc.h  SourceChannelIDText.h  SpaceCraftIDText.h  types.h Block0Doc.h  Block.h

lib_LTLIBRARIES           = libgvar.la

libgvar_la_LDFLAGS = -version-info 1:0:1
libgvar_la_SOURCES=selFloat.cpp Header.cpp Block.cpp LineDoc.cpp unpack10.cpp cdaTime.cpp Block3to10.cpp Block0.cpp Block0Doc.cpp Block1or2.cpp

bin_PROGRAMS = gvar_inspector
gvar_inspector_SOURCES = gvar_inspector.cpp GvarFile.cpp GvarFile.h
gvar_inspector_LDADD = libgvar.la
