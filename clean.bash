#!/bin/bash
find . -name "*.o" | while read F; do rm -v "$F"; done;
