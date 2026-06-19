use strict;
use warnings;

my @arr = ();

for (my $i = 0; $i < 1000000; $i++) {
    push @arr, $i;
}

my $sum = 0;

for (my $i = 0; $i < 1000000; $i++) {
    $sum += $arr[$i];
}

print "$sum\n";