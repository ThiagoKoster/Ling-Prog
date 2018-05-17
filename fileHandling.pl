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

#Subrotine to search for an specific store
sub searchName
{   # $name os the name of the store to be found and @matrix is promoMatrix
    my ($name, @matrix) = @_;
    my $matrixSize = @matrix;

    for(my $index = 0; $index < $matrixSize; $index++ )
    {
        if($matrix[$index][1] =~ /($name)/)
        {
            print "achou\n";
        }
    }

}


#Subrotines end

my $count = 0 ;
while(my $row = <$fileHandler>)
{
    
    $row = findIds($count,$row);
    $row = findStores($count, $row);
    $row = findPrices($count,$row);
    
   
    my $product = $row;
    $promoMatrix[$count][2] = $product;
    ++$count ;
}

printProducts();

searchName ("Sub",@promoMatrix);

print "Done\n";
close $fileHandler;