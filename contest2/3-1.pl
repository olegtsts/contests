#!/usr/bin/perl

use strict;
use warnings;

print 1e5 . " " . 1e5 . "\n";
print join(" ", 1 .. 1e5) . "\n";

print "0\n";
my $cur_course = 1;
while ($cur_course < 1e5) {
    print 1 . " " . $cur_course . "\n";
    ++$cur_course;
}
