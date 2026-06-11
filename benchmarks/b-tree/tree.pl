package Node;

sub new {
    my ($class, $value) = @_;

    my $self = {
        value => $value,
        left  => undef,
        right => undef,
    };

    bless $self, $class;
    return $self;
}

sub insert {
    my ($self, $value) = @_;

    if ($value < $self->{value}) {
        if (!defined $self->{left}) {
            $self->{left} = Node->new($value);
        } else {
            $self->{left}->insert($value);
        }
    } else {
        if (!defined $self->{right}) {
            $self->{right} = Node->new($value);
        } else {
            $self->{right}->insert($value);
        }
    }
}

sub sum {
    my ($self) = @_;

    my $total = $self->{value};

    if (defined $self->{left}) {
        $total += $self->{left}->sum();
    }

    if (defined $self->{right}) {
        $total += $self->{right}->sum();
    }

    return $total;
}

package main;

my $N = 100000;

my $root = Node->new(50000);

my $i = 0;
while ($i < $N) {
    $root->insert(($i * 7919) % $N);
    $i++;
}