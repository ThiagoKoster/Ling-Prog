use warnings; use strict;

my $fileName = 'posts.html';

open(my $fileHandler, '<',$fileName) or 
    die "Could not open file '$fileName' '$!'";

my @promoMatrix ;

my $count = 0 ;
while(my $row = <$fileHandler>)
{
    #Return everything inside [ ] or ( ) after first whitespace
    $row =~ /^\S\s\"\[(.*?)\]|^\S\s\"\((.*?)\)/gi ;
    $promoMatrix[$count][0] = $count; 
    $promoMatrix[$count][1] = $+; # $+ = last match
    ++$count ;
}

 for my $i ( 0 .. $#promoMatrix ) { # #promoMatrix = size of protoMatriz
     print "\t [ @{$promoMatrix[$i]} ],\n";
 }


print "Done\n";
#print $products[1][0];
close $fileHandler;