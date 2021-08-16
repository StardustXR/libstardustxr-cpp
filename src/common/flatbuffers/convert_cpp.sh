#!/usr/bin/env bash
flatc -c *.fbs --gen-mutable --filename-suffix "" --filename-ext "hpp"
