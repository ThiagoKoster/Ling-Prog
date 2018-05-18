use Text::Table;
use warnings; use strict;

my @promoMatrix ; # [ [Id0,Store,Product,Price] , .... , [IdN,Store,Product,Price] ] 
use constant{ # constants to make indexing promoMatrix easier
    ID      => 0,
    STORE   => 1,
    PRODUCT => 2,
    PRICE   => 3,
};

my $fileName = 'posts.html';
open(my $fileHandler, '<',$fileName) or 
    die "Could not open file '$fileName' '$!'";

#Subrotines

#Prints a matrix in promoMatrix format
# matrix(protoMatrix format) -> void
sub printMatrix
{
    my(@matrix) = @_ ;
    my $table = Text::Table ->new("Id", "Store", "Product", "Price");
    for my $i (0 .. $#matrix)
    {
        $table->load(
            [$matrix[$i][0], $matrix[$i][1], $matrix[$i][2], $matrix[$i][3]]
        );
    }

    print $table;
}

#Searches for id ; If found includes it on promoMatrix at the correct position, and returns the string without it
#int , string -> string without Id
sub findIds
{
    my($index,$row) = @_;
    $row =~ s/(^\w*)//gi;
    $promoMatrix[$index][0] = $&;
    return $row;
    
}

#Searches for (store) or [store] ; If found includes it on promoMatrix at the correct position, and returns the string without it
# int, string -> string without store name
sub findStores 
{
    my ($index,$row) = @_;
    $row =~ s/^\S*\s\"\[(.*?)\]|^\S*\s\"\((.*?)\)//i; 
    $promoMatrix[$index][1] = $+;
    return $row;
}

#Searches for R$ price ; If found includes it on promoMatrix at the correct position, and returns the string without it
#int , string -> string without price and everything after it
sub findPrices
{
    my ($index,$row) = @_;
    #$row =~ s/\.//;
    #$row =~ s/R\$\s*(\d+[,]?\d{1,2}|\d+\.\d{3}[,]?\d{1,2}|\d+\.\d{3}).+//;
    $row =~ s/R\$\s*(\d+[.]?\d+[,]?\d{1,2}).+//; #searches for R$price and cuts it out of row
    my $price = $+ ; 
    $price =~ s/\.// ; # remove dots from price
    $promoMatrix[$index][3] = $price;
    return $row;
}

#Generates promoMatrix from the txt file
# void -> void
sub generatePromoMatrix
{
    my $count = 0 ;
    while(my $row = <$fileHandler>)
    {
        $row = findIds($count,$row);
        $row = findStores($count, $row);
        $row = findPrices($count,$row);

        my $product = $row; #after we exclude id,store and price from row all we have left is product
        $promoMatrix[$count][2] = $product;
        ++$count ;
    }
}

#Subrotine to search for substrings in a matrix in a given column  
#   returns a matrix(promoMatrix format) with the rows that have the given name at given column
# string, constant, matrix -> 
sub searchMatrix
{
    my ($name,$column, @matrix) = @_;
    my @auxMatrix; 
    for(my $index = 0; $index < $#matrix; $index++ )
    {
        if($matrix[$index][$column] =~ /($name)/)
        {
            print "achou\n";
            $auxMatrix[$index] = $matrix[$index]; ## <<<<<<<<<<<<<<<<<<<<<<<<<<<<< how to do this????
        }
    }

}

#Subrotines end


generatePromoMatrix();

printMatrix(@promoMatrix);

my @matrix = searchMatrix("Sub",STORE,@promoMatrix);

printMatrix(@matrix);

print "Done\n";
close $fileHandler;