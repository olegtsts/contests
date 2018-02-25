#!/usr/bin/perl
use strict;
use warnings;

foreach my $file (split(/\s+/,`ls tasks/division*.in`)) {
    my $new_file = $file;
    my $log_file = $file;
    $new_file =~ s/\.in/.ans/g;
    $log_file =~ s/\.in/.log/g;

    print("./a.out < $file > $new_file 2> $log_file & \\\n");
}
