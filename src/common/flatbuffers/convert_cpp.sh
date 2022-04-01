#!/usr/bin/env bash
flatc -c *.fbs --scoped-enums --gen-name-strings --gen-mutable --filename-suffix "" --filename-ext "hpp"
