#!/usr/bin/perl

use warnings;
use strict;
use GD;

# Read in data
my @data;
push @data, [split] while <>;
my $w     = scalar @{ $data[0] };
my $h     = scalar @data;
my $numel = $w * $h;

# Set up image
my $csize = 6;
my $imw   = $w * $csize;
my $imh   = $h * $csize;
my $im    = new GD::Image( $imw, $imh );
my $white = $im->colorAllocate( 255, 255, 255 );
my $gray  = $im->colorAllocate( 127, 127, 127 );
my $blue  = $im->colorAllocate( 0, 0, 255 );

# Draw grid
for my $row ( 0 .. $w ) {
    $im->line( $row * $csize, 0, $row * $csize, $imh, $gray );
}
for my $col ( 0 .. $h ) {
    $im->line( 0, $col * $csize, $imw, $col * $csize, $gray );
}

# Follow path
my ( $lx, $ly ) = find(1);
for my $n ( 2 .. $numel ) {
    my ( $x, $y ) = find($n);
    print "Drawing image $n of $numel\n";

    $im->line(
        ( $lx + 0.5 ) * $csize,
        ( $ly + 0.5 ) * $csize,
        ( $x + 0.5 ) * $csize,
        ( $y + 0.5 ) * $csize,
        $blue
    );
    $im->line(
        ( $lx + 0.5 ) * $csize - 1,
        ( $ly + 0.5 ) * $csize,
        ( $x + 0.5 ) * $csize - 1,
        ( $y + 0.5 ) * $csize, $blue
    );
    open my ($outimg), ">", sprintf( "frame-%04d.png", $n );
    print $outimg $im->png;
    close $outimg;

    ( $lx, $ly ) = ( $x, $y );
}

# Find position of jump n
sub find {
    my $n = shift;
    my ( $x, $y ) = ( 0, 0 );
    for my $row (@data) {
        for my $el (@$row) {
            return ( $x, $y ) if $el == $n;
            $x++;
        }
        $x = 0;
        $y++;
    }
}
