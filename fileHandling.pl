use warnings; use strict;

my $fileName = 'posts.html';

open(my $fileHandler, '<',$fileName) or 
    die "Could not open file '$fileName' '$!'";

my @promoMatrix ; # [ [Id0,Store,Product,Price] , .... , [IdN,Store,Product,Price] ] 

my $count = 0 ;
while(my $row = <$fileHandler>)
{
    #Return everything inside [ ] or ( ) after first whitespace
    #my ($store) = ($row =~ /^\d\s\"[\[|\(](.*?)[\]|\)]/gi );
    $row =~ /^\S\s\"\[(.*?)\]|^\S\s\"\((.*?)\)/gi ;
    my $store = $+ ; # $+ = last match
    # \G continues regex search from where the last match ocurred
    my ($product) = ($row =~ /\G(.*?)(R\$|\d+\,\d+)/i ); # R$ or numbers followed by . or ,
    my ($price) = ($row =~ /(R\$\s*\d+[\.?|\,?]\d*\,?)/); # BUG  ===== R$ 2060 doesnt work, why? shouldnt \d* treat that?

    $promoMatrix[$count][0] = $count;  # id?
    $promoMatrix[$count][1] = $store;
    $promoMatrix[$count][2] = $product;
    $promoMatrix[$count][3] = $price;
    ++$count ;
}

 for my $i ( 0 .. $#promoMatrix ) { # $#protoMatrix = size of protoMatriz
     print "\t [ @{$promoMatrix[$i]} ],\n";
 }


print "Done\n";
#print $products[1][0];
close $fileHandler;