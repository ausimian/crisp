ARFLAGS = cr

noinst_LIBRARIES = src/lib/libcrisp.a
noinst_HEADERS   = src/lib/term.h \
				   src/lib/read.h

bin_PROGRAMS = src/bin/crisp

src_lib_libcrisp_a_SOURCES = $(src_lib_libcrisp_a_HEADERS) \
							 src/lib/term.c                \
							 src/lib/read.c

src_bin_crisp_SOURCES  = src/bin/main.c
src_bin_crisp_CPPFLAGS = -I$(top_srcdir)/src
src_bin_crisp_LDADD    = $(top_builddir)/src/lib/libcrisp.a $(AM_LDFLAGS)
