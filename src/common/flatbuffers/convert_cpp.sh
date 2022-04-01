#!/usr/bin/env bash
flatc -c *.fbs --scoped-pointers --gen-name-strings --gen-mutable --filename-suffix "" --filename-ext "hpp"
