#!/bin/sh

cd ../../genericga/
make genericga
cd ../healthcaredp/lib

rm -r genericga
rm libgenericga.so

cp -r ../../genericga/include/genericga .
cp ../../genericga/lib/libgenericga.so .
