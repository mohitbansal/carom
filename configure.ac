AC_INIT([carom], [1.1], [mohitbansal031290@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_LANG(C++)
AC_PROG_CXX
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 data/Makefile
])
dnl Check for SDL
  SDL_VERSION=2.0.0
  AM_PATH_SDL2($SDL_VERSION,
            :,
            AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
  )
  CXXFLAGS="$CXXFLAGS $SDL_CXXFLAGS"
  LIBS="$LIBS $SDL_LIBS"

PKG_CHECK_MODULES([DEPENDENCIES], [SDL2_image SDL2_ttf SDL2_mixer])
CXXFLAGS="$CXXFLAGS $DEPENDENCIES_CFLAGS"
LIBS="$LIBS $DEPENDENCIES_LIBS"
AC_OUTPUT