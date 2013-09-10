#!/bin/sh

find . -name "*.test" -exec echo \{\} \; -exec ./\{\} \;
