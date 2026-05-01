use strict;
use warnings;

my $n = 10000000;
my $step = 1.0 / $n;
my $sum = 0.0;

my $i = 0;
while ($i < $n) {
    my $x = ($i + 0.5) * $step;
    $sum += 4.0 / (1.0 + $x * $x);
    $i = $i + 1;
}

my $pi = $sum * $step;
print "$pi\n";