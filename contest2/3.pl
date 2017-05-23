#!/usr/bin/perl

use strict;
use warnings;

use List::Util qw(min max);

my $n = 100000;
my $k = 70000;
print "$n $k\n";
my $main_courses = {};
while (scalar(keys %$main_courses) < $k) {
    my $new_course = int(rand($n)) + 1;
    $main_courses->{$new_course} = 1;
}

print join(" ", keys %$main_courses) . "\n";

my $cur_course_index = 0;
my $sum_of_depends = 0;
while ($cur_course_index < $k) {
    my $depends_count = min(int(rand(100)), max($cur_course_index - 1, 0));
    $sum_of_depends += $depends_count;
    if ($sum_of_depends < 1e5) {
        my $depends = {};
        my $cur_depend_index = 0;
        while ($cur_depend_index < $depends_count) {
            if ($cur_course_index >= 1) {
                my $depend = int(rand($cur_course_index - 1)) + 1;
                if ($depend >= 1 && $depend <= $cur_course_index) {
                    $depends->{$depend} = 1;
                }
            }
            ++$cur_depend_index;
        }
        print scalar(keys %$depends) . " " . join(" ", keys %$depends) . "\n";
    } else {
        print "0\n";
    }
    ++$cur_course_index;
}

