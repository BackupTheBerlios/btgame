SUBDIRS = neo3d 

bin_PROGRAMS = n3dViewer

n3dViewer_SOURCES = n3dViewer.cxx
n3dViewer_LDADD = neo3d/libneo3d.a

AM_LDFLAGS = @GL_LIBS@ @MATHLIB@ @SDL_LIBS@ -lSDL_image -lSDL_mixer
