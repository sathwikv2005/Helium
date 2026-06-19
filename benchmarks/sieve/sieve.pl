use strict;
use warnings;

my $n = 1000000;
my @prime = ();

for (my $i = 0; $i <= $n; $i++) {
    push @prime, 1;
}

$prime[0] = 0;
$prime[1] = 0;

for (my $i = 2; $i * $i <= $n; $i++) {
    if ($prime[$i]) {
        for (my $j = $i * $i; $j <= $n; $j += $i) {
            $prime[$j] = 0;
        }
    }
}

my $count = 0;

for (my $i = 0; $i <= $n; $i++) {
    $count++ if $prime[$i];
}

print "$count\n";