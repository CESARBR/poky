SUMMARY = "Xlib: C Language X Interface library"

DESCRIPTION = "This package provides a client interface to the X Window \
System, otherwise known as 'Xlib'.  It provides a complete API for the \
basic functions of the window system."

require xorg-lib-common.inc

FILESEXTRAPATHS =. "${FILE_DIRNAME}/libx11:"

PE = "1"

SRC_URI[md5sum] = "034fdd6cc5393974d88aec6f5bc96162"
SRC_URI[sha256sum] = "910e9e30efba4ad3672ca277741c2728aebffa7bc526f04dcfa74df2e52a1348"

PROVIDES = "virtual/libx11"

XORG_PN = "libX11"
LICENSE = "MIT & MIT-style & BSD"
LIC_FILES_CHKSUM = "file://COPYING;md5=172255dee66bb0151435b2d5d709fcf7"

DEPENDS += "xorgproto xtrans libxcb"
DEPENDS += "xorgproto-native"

EXTRA_OECONF += "--with-keysymdefdir=${STAGING_INCDIR}/X11/ --disable-xf86bigfont"
EXTRA_OEMAKE += 'CWARNFLAGS=""'

PACKAGECONFIG ??= "xcms"
PACKAGECONFIG[xcms] = "--enable-xcms,--disable-xcms"

# src/util/makekeys is built natively but needs -D_GNU_SOURCE defined.
CPPFLAGS_FOR_BUILD += "-D_GNU_SOURCE"

PACKAGES =+ "${PN}-xcb"
PACKAGES_remove = "${PN}-locale"

FILES_${PN} += "${datadir}/X11/XKeysymDB ${datadir}/X11/XErrorDB ${datadir}/X11/Xcms.txt"
FILES_${PN}-xcb += "${libdir}/libX11-xcb.so.*"

# locale data files would be provided by libx11-locale recipe
do_install_append() {
	rm -rf ${D}${datadir}/X11/locale
	rm -rf ${D}${libdir}/X11/locale
}
