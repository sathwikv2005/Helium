package Node;

sub new {
    my ($class, $value, $next) = @_;

    my $self = {
        value => $value,
        next  => $next,
    };

    bless $self, $class;
    return $self;
}

sub sum {
    my ($self) = @_;

    my $total = 0;
    my $current = $self;

    while (defined $current) {
        $total += $current->{value};
        $current = $current->{next};
    }

    return $total;
}

package main;

my $N = 1000000;

my $head = undef;

my $i = 0;
while ($i < $N) {
    $head = Node->new($i, $head);
    $i++;
}