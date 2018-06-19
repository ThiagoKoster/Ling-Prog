use strict;
use warnings;
use perlLib;
use feature qw(switch say);
use lib '/';
use constant{ # constants to make indexing promoMatrix easier
    ID      => 0,
    STORE   => 1,
    PRODUCT => 2,
    PRICE   => 3,
    RESPONSES => 4,
    VIEWS => 5,
};