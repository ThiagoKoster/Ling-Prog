use Text::Table;
use warnings; use strict;

my @promoMatrix ; # [ [Id0,Store,Product,Price] , .... , [IdN,Store,Product,Price] ] 
my $fileName = 'posts.html';
open(my $fileHandler, '<',$fileName) or 
    die "Could not open file '$fileName' '$!'";

#Subrotines

#The subrotines find each element and then returns the row without them.
sub printProducts
{
    my $table = Text::Table ->new("Id", "Store", "Product", "Price");
    for my $i (0 .. $#promoMatrix)
    {
        $table->load(
            [$promoMatrix[$i][0], $promoMatrix[$i][1], $promoMatrix[$i][2], $promoMatrix[$i][3]]
        );
    }

    print $table;
}

sub findIds
{
    my($count,$row) = @_;
    $row =~ s/(^\w*)//gi;
    $promoMatrix[$count][0] = $&;
    return $row;
    
}

sub findStores 
{
    my ($count,$row) = @_;
    $row =~ s/^\S*\s\"\[(.*?)\]|^\S*\s\"\((.*?)\)//i;
    $promoMatrix[$count][1] = $+;
    return $row;
}

sub findPrices
{
    my ($count,$row) = @_;
    $row =~ s/\.//;
    $row =~ s/R\$\s*(\d+[,]*\d{1,9})//;
    $promoMatrix[$count][3] = $+;
    return $row;
}


#Subrotines end

my $count = 0 ;
while(my $row = <$fileHandler>)
{
    #Return everything inside [ ] or ( ) after first whitespace
    #my ($store) = ($row =~ /^\d\s\"[\[|\(](.*?)[\]|\)]/gi );
    #$row =~ /^\S\s\"\[(.*?)\]|^\S\s\"\((.*?)\)/gi ;
    
    $row = findIds($count,$row);
    $row = findStores($count, $row);
    $row = findPrices($count,$row);
    
    #removeWords($row,@words);
    # \G continues regex search from where the last match ocurred
    #my ($product) = ($row =~ /\G(.*?)(R\$|\d+\,\d+)/i ); # R$ or numbers followed by . or ,
    my $product = $row;
    $promoMatrix[$count][2] = $product;
    ++$count ;
}

printProducts();


print "Done\n";
close $fileHandler;