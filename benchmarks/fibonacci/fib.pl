use strict;
use warnings;

sub fib {
    my ($n) = @_;
    return $n if $n < 2;
    return fib($n - 2) + fib($n - 1);
}

print fib(35), "\n";