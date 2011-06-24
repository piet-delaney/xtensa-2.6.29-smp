#!/bin/sh
#
# xcc-version [-p] xcc-command
#
# Prints the xcc version of `xcc-command' in a canonical 5-digit
# form from the Major.Intermediate.Minor version number.
# Examples:
#	   `09002' for xcc-9.0.2
#	   `08001' for xcc-8.0.1
#	   '07101' for xcc-7.1.1     [Intermediate Release 1]
#
# With the -p option the format will be the same. Seems the trend
# is to not provide PATCHLEVEL visibility, so we wont use it.
#

if [ "$1" = "-p" ] ; then
	with_patchlevel=1;
	shift;
fi

compiler="$*"

if [ ${#compiler} -eq 0 ]; then
	echo "Error: No compiler specified."
	echo -e "Usage:\n\t$0 <xcc-command>"
	exit 1
fi


MAJOR=$($compiler --version  | grep version | sed -e "s/.* version \([0-9*]\)\.\([0-9*]*\)\.\([0-9]*\)\(.*\)/\1/")
INTERM=$($compiler --version | grep version | sed -e "s/.* version \([0-9*]\)\.\([0-9*]*\)\.\([0-9]*\)\(.*\)/\2/")
MINOR=$($compiler --version  | grep version | sed -e "s/.* version \([0-9*]\)\.\([0-9*]*\)\.\([0-9]*\)\(.*\)/\3/")

printf "%02d%01d%02d\\n" $MAJOR $INTERM $MINOR
