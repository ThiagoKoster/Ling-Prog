#!/usr/bin/env perl
# q to quit
do{print("perl> ");$_x=<>;chomp $_x;print(eval($_x)."\n")}while($_x ne "q")