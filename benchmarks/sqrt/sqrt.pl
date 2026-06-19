use strict;
use warnings;

my $sum = 0.0;

for my $n (1 .. 100000) {
    my $x = $n * 12345.6789;
    my $guess = $x;

    for (1 .. 20) {
        $guess = 0.5 * ($guess + $x / $guess);
    }

    $sum += $guess;
}

print "$sum\n";