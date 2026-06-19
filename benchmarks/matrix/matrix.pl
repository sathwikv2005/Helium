use strict;
use warnings;

my $N = 150;

my @A;
my @B;
my @C;

for my $i (0 .. $N - 1) {
    $A[$i] = [];
    $B[$i] = [];
    $C[$i] = [];

    for my $j (0 .. $N - 1) {
        push @{$A[$i]}, (($i + $j) % 100);
        push @{$B[$i]}, (($i * $j) % 100);
        push @{$C[$i]}, 0;
    }
}

for my $i (0 .. $N - 1) {
    for my $j (0 .. $N - 1) {
        my $sum = 0;

        for my $k (0 .. $N - 1) {
            $sum += $A[$i][$k] * $B[$k][$j];
        }

        $C[$i][$j] = $sum;
    }
}

print "$C[0][0]\n";
print "$C[$N-1][$N-1]\n";