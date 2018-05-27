use Text::Table;
#use warnings; 
use strict;

my @promoMatrix ; # [ [Id0,Store,Product,Price,Responses,Views] , .... , [Id0,Store,Product,Price,Responses,Views] ] 

use constant{ # constants to make indexing promoMatrix easier
    ID      => 0,
    STORE   => 1,
    PRODUCT => 2,
    PRICE   => 3,
    RESPONSES => 4,
    VIEWS => 5,
};

my $fileName = 'posts.html';
open(my $fileHandler, '<',$fileName) or 
    die "Could not open file '$fileName' '$!'";

#Subrotines

#Prints a matrix in promoMatrix format
# matrix(promoMatrix format) -> void
sub printMatrix
{
    my (@matrix) = @_;
    
    my $table = Text::Table ->new("Id", "Store", "Product", "Price", "Responses", "Views");

     for my $i (0 .. @matrix)
    {
        $table->load(
            [$matrix[$i][0], $matrix[$i][1], $matrix[$i][2], $matrix[$i][3], $matrix[$i][4], $matrix[$i][5]]
        );
    }
    print $table;
}

#Prints the first N lines of a matrix
# matrix -> void
sub printNLinesInMatrix
{
    my ($numLines, @matrix) = @_;
    my @auxMatrix;
    if($numLines > @matrix)
    {
        print "ERROR : N > matrix size";
    }
    else
    {
        for(my $line = 0; $line < $numLines; $line++)
            {
                $auxMatrix[$line] = $matrix[$line]; 
            }
        printMatrix(@auxMatrix);
    }
}

#Searches for number os Responses ; If found includes it on promoMatrix at the correct position, and returns the string without it
#int , string -> string 
sub findResponses
{
    my($index,$row) = @_;
    $row =~ /'.*?'\s(\d*)/;
    $promoMatrix[$index][RESPONSES] = $+;
    return $row;
}

#Searches for number os Responses ; If found includes it on promoMatrix at the correct position, and returns the string without it
#int , string -> string
sub findViews
{
    my($index,$row) = @_;
    $row =~ /'.*?'\s\d*\s(\d*)/;
    $promoMatrix[$index][VIEWS] = $+;
    return $row;
}

#Searches for id ; If found includes it on promoMatrix at the correct position, and returns the string without it
#int , string -> string without Id
sub findIds
{
    my($index,$row) = @_;
    $row =~ s/(^\w*)//gi;
    $promoMatrix[$index][ID] = $&;
    return $row;
    
}

#Searches for (store) or [store] ; If found includes it on promoMatrix at the correct position, and returns the string without it
# int, string -> string without store name
sub findStores 
{
    my ($index,$row) = @_;
    $row =~ s/^\S*\s\'\[(.*?)\]|^\S*\s\'\((.*?)\)//i; 
    $promoMatrix[$index][STORE] = $+;
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
    $promoMatrix[$index][PRICE] = $price;
    return $row;
}

#Generates promoMatrix from the txt file
# void -> void
sub generatePromoMatrix
{
    my $count = 0 ;
    while(my $row = <$fileHandler>)
    {
        $row = findViews($count,$row);
        $row = findResponses($count,$row);
        $row = findIds($count,$row);
        $row = findStores($count, $row);
        $row = findPrices($count,$row);

        my $product = $row; #after we exclude id,store and price from row all we have left is product
        $promoMatrix[$count][PRODUCT] = $product;
        ++$count ;
    }
}

#Subroutine to replace abbreviated store names to correct ones
#void -> void
sub replaceStoreNames
{
    my %stores = (
        'sub' => "Submarino",
        'amaz' => "Amazon",
        'frio' => "PontoFrio",
        'fast' => "FastShop",
        'rapi' => "FastShop",
        'time' => "ShopTime",
        'luiza' => "Magazine Luiza",
        'bahia' => "Casas Bahia",
        'ricard' => "Ricardo Eletro",
        'barat' => "SouBarato",
        'wal' => "Walmart"
    );
    my @abbreviations = keys %stores;

    for(my $count = 0; $count < @promoMatrix; $count++ )
    {
        foreach my $i (@abbreviations)
        {
            if ( index(lc($promoMatrix[$count][STORE]) , $i) > -1) # index(string,substring) returns first position of substring in string, -1 if not found
            {                                                      # lc(string) returns lowercase string
                $promoMatrix[$count][STORE] = $stores{$i}; #if abbreviation found replace it by its value in %stores hash
            }
        }
    }
}

#Subrotine to search for substrings in a matrix in a given column  
#   returns a matrix(promoMatrix format) with rows that have the given name at given column
# string, constant, matrix -> matrix
sub searchNameInMatrix
{
    my ($name,$column, @matrix) = @_;
    my @auxMatrix;
    my $count = 0; 
    for(my $index = 0; $index < @matrix; $index++ )
    {
        if($matrix[$index][$column] =~ /($name)/gi) #global and case insensitive
        {
            $auxMatrix[$count] = $matrix[$index];
            ++$count;
        }
    }
    return @auxMatrix ;
}

#Subroutine to search for products higher or smaller than given price
#   returns a matrix(promoMatrix format) with rows that meet the price option
# float, int , matrix -> matrix
sub searchPriceInMatrix 
{
    my ($price,$option, @matrix) = @_ ; #option = 0 for <= | option = 1 for >=
    my @auxMatrix;
    my $count = 0;
    if ($option == 0)
    {
        for(my $index = 0; $index < @matrix; $index++ )
        {
            if($matrix[$index][PRICE] <= $price) 
            {
                $auxMatrix[$count] = $matrix[$index];
                ++$count;
            }
        }
    }
    elsif ($option == 1)
    {
        for(my $index = 0; $index < @matrix; $index++ )
        {
            if($matrix[$index][PRICE] >= $price) 
            {
                $auxMatrix[$count] = $matrix[$index];
                ++$count;
            }
        }
    }
    else
    {
        print "ERROR : Unspecified option, chose 0 for lower than price\n";
        print "\t or 1 for higher than price";
        return 0;
    }

    return @auxMatrix;
}

#Subroutine to search for products in a price ranger
# float, float , matrix -> matrix
sub searchPriceRangeInMatrix
{
    my ($minPrice,$maxPrice,@matrix) = @_;
    my @auxMatrix;
    if( ($minPrice >= $maxPrice) | ($maxPrice < $minPrice) ) 
    {
        print "ERROR: The price Range is wrong\n";
    }
    @auxMatrix = searchPriceInMatrix($maxPrice,0,@matrix); # lower than max price
    @auxMatrix = searchPriceInMatrix($minPrice,1,@auxMatrix); # higher than min price

    return @auxMatrix;    
}

#Subroutines to find the row with the most items in the given column
# int,matrix > array
sub findMostInColumn
{
    my($column,@matrix) = @_;
    my $maxInColumn = 0;
    my $count = 0;
    for(my $index = 0; $index <@matrix; $index++)
    {
        my $numInColumn = $matrix[$index][$column] ;
        if( $numInColumn >= $maxInColumn)
        {
            $maxInColumn = $numInColumn;
            $count = $index;
        }
    }
    return $matrix[$count];
}

#Subrotines end


######## test area #########

generatePromoMatrix();
replaceStoreNames();
printMatrix(@promoMatrix);

my @matrix = searchNameInMatrix("samsung",PRODUCT,@promoMatrix);
print "\nForam encontradas as seguintes promocoes contendo Samsung:\n";
printMatrix(@matrix);

@matrix = searchNameInMatrix("sub",STORE,@promoMatrix);
print "\nForam encontradas as seguintes promocoes na loja Submarino:\n";
printMatrix(@matrix);

@matrix = findMostInColumn(RESPONSES,@promoMatrix);
print "\nPromocao mais comentada\n";
printMatrix(@matrix);

@matrix = findMostInColumn(VIEWS,@promoMatrix);
print "\nPromocao mais vista\n";
printMatrix(@matrix);

@matrix = searchPriceInMatrix(1100,1,@promoMatrix);
print "\nForam encontradas as seguintes promocoes acima de R\$1100:\n";
printMatrix(@matrix); 

@matrix = searchPriceInMatrix(1100,0,@promoMatrix);
print "\nForam encontradas as seguintes promocoes abaixo de R\$1100:\n";
printMatrix(@matrix); 

print "\nForam encontradas as seguintes promocoes acima de R\$2100 e abaixo de R\$3000:\n";
@matrix = searchPriceRangeInMatrix(2100,3000,@promoMatrix);
printMatrix(@matrix); 

print ("\n4 primeiras promocoes:\n");
printNLinesInMatrix(4,@promoMatrix);
######## end of test area #########

print "Done\n";
close $fileHandler;