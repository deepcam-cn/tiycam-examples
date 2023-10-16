#!/bin/sh
# build ipk package
PACK_TOOL=../../../ipkg_tool/ipkg-build
if [ $# != 1 ] ; then
echo "USAGE: $0 app_name"
exit 1;
fi

chmod 777 $1/CONTROL/*
chmod 777 $1/etc/init.d/*
$PACK_TOOL $1
