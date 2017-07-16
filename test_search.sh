#!/bin/bash

FAILURES=0

if ! diff -u <(find /etc 2> /dev/null| sort) \
             <(./search /etc 2> /dev/null | sort); then
    echo "Search no arguments test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -type f 2> /dev/null| sort) \
             <(./search /etc -type f 2> /dev/null| sort); then
    echo "Search -type f argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -type d 2> /dev/null| sort) \
             <(./search /etc -type d 2> /dev/null| sort); then
    echo "Search -type d argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -executable 2> /dev/null| sort) \
             <(./search /etc -executable  2> /dev/null| sort); then
    echo "Search -executable argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -readable 2> /dev/null| sort) \
             <(./search /etc -readable 2> /dev/null| sort); then
    echo "Search -readable argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -writable 2> /dev/null| sort) \
             <(./search /etc -writable 2> /dev/null| sort); then
    echo "Search -writable argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -empty 2> /dev/null| sort) \
             <(./search /etc -empty 2> /dev/null| sort); then
    echo "Search -empty argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -name '*.conf' 2> /dev/null| sort) \
             <(./search /etc -name '*.conf' 2> /dev/null| sort); then
    echo "Search -name argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -path '*security/*.conf' 2> /dev/null| sort) \
             <(./search /etc -path '*security/*.conf' 2> /dev/null| sort); then
    echo "Search -path argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -perm 600 2> /dev/null| sort) \
             <(./search /etc -perm 600 2> /dev/null| sort); then
    echo "Search -perm argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -newer /etc/passwd 2> /dev/null| sort) \
             <(./search /etc -newer /etc/passwd 2> /dev/null| sort); then
    echo "Search -newer argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -uid 0 2> /dev/null| sort) \
             <(./search /etc -uid 0 2> /dev/null| sort); then
    echo "Search -uid argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -gid 0 2> /dev/null| sort) \
             <(./search /etc -gid 0 2> /dev/null| sort); then
    echo "Search -gid argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -exec echo \{\} \; 2> /dev/null| sort) \
             <(./search /etc -exec echo \{\} \; 2> /dev/null| sort); then
    echo "Search -exec argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -type f -executable 2> /dev/null| sort) \
             <(./search /etc -type f -executable 2> /dev/null| sort); then
    echo "Search -type f -executable arguments test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -type d -readable 2> /dev/null| sort) \
             <(./search /etc -type d -readable 2> /dev/null| sort); then
    echo "Search -type d -readable arguments test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -type d -name '*conf*' 2> /dev/null| sort) \
             <(./search /etc -type d -name '*conf*' 2> /dev/null| sort); then
    echo "Search -type d -name arguments test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -print 2> /dev/null| sort) \
             <(./search /etc -print 2> /dev/null| sort); then
    echo "Search -print argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if ! diff -u <(find /etc -empty -exec stat \{\} \; 2> /dev/null| sort) \
             <(./search /etc -empty -exec stat \{\} \; 2> /dev/null| sort); then
    echo "Search -empty -exec argument test failed!"
    FAILURES=$(($FAILURES + 1))
fi

if [ $FAILURES -eq 0 ]; then
    echo "Search test successful!"
else
    echo "Search test had $FAILURES failures!"
fi

exit $FAILURES
