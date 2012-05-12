include(LibFindMacros)

# Dependencies
libfind_package(TCLAP TCLAP)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(TCLAP_PKGCONF tclap)

# Include dir
find_path(TCLAP_INCLUDE_DIR
	NAMES tclap/CmdLine.h
	PATHS ${TCLAP_PKGCONF_INCLUDE_DIRS}
	    )


	# Set the include dir variables and the libraries and let libfind_process do the rest.
	# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
	set(TCLAP_PROCESS_INCLUDES TCLAP_INCLUDE_DIR TCLAP_INCLUDE_DIRS)
	libfind_process(TCLAP)

