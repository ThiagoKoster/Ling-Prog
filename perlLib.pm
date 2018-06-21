package perlLib;
use strict;
#use warnings;
use Text::Table;
use constant{ # constants to make indexing promoMatrix easier
    ID      => 0,
    STORE   => 1,
    PRODUCT => 2,
    PRICE   => 3,
};
require Exporter;
our @ISA = qw(Exporter);
our %EXPORT_TAGS = ( 'all' => [ qw() ] );
our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );
our @EXPORT = qw(
        printMatrix
        findIds
        findStores
        findPrices
        generatePromoMatrix
        searchProductInMatrix
        searchNameInMatrix
        searchStoreInMatrix
        searchPriceRangeInMatrix
);
our $VERSION = '0.01';

#Prints a matrix in promoMatrix format into a file of given name
# matrixRef(promoMatrix format), string -> void
sub printMatrix
{
    my ($matrixRef,$fileName) = @_;
    
    my $table = Text::Table ->new("Id", "Loja", "Produto", "Preco");

     for my $i (0 .. @$matrixRef)
    {
        $table->load(
            [$$matrixRef[$i][0], $$matrixRef[$i][1], $$matrixRef[$i][2], $$matrixRef[$i][3]]
        );
    }
    open(FILEHANDLER, '>', $fileName) or die $!;
    print FILEHANDLER $table;
    close (FILEHANDLER);
}

#Searches for id ; If found includes it on promoMatrix at the correct position, and returns the string without it
#int , string, $promoMatrixReference -> string without Id
sub findIds
{
    my($index,$row,$promoMatrixRef) = @_;
    $row =~ s/(^\w*)//gi;
    $$promoMatrixRef[$index][ID] = $&;
    return $row;
    
}

#Searches for (store) or [store] ; If found includes it on promoMatrix at the correct position, and returns the string without it
# int, string, $promoMatrixReference -> string without store name
sub findStores 
{
    my ($index,$row,$promoMatrixRef) = @_;
    $row =~ s/^\S*\s\"\[(.*?)\]|^\S*\s\"\((.*?)\)//i; 
    $$promoMatrixRef[$index][STORE] = $+;
    return $row;
}

#Searches for R$ price ; If found includes it on promoMatrix at the correct position, and returns the string without it
#int , string, $promoMatrixReference -> string without price and everything after it
sub findPrices
{
    my ($index,$row,$promoMatrixRef) = @_;
    #$row =~ s/\.//;
    #$row =~ s/R\$\s*(\d+[,]?\d{1,2}|\d+\.\d{3}[,]?\d{1,2}|\d+\.\d{3}).+//;
    $row =~ s/R\$\s*(\d+[.]?\d+[,]?\d{1,2}).+//; #searches for R$price and cuts it out of row
    my $price = $+ ; 
    $price =~ s/\.// ; # remove dots from price
    $$promoMatrixRef[$index][PRICE] = $price;
    return $row;
}

#Generates promoMatrix from the file name given, return a 2 dimensional array in promoMatrix format
# string -> promoMatrix
sub generatePromoMatrix
{   
    my ($fileName) = @_;
    open(my $fileHandler, '<',$fileName) or 
        die "Could not open file '$fileName' '$!'";

    my @promoMatrix ; # [ [Id0,Store,Product,Price,Responses,Views] , .... , [Id0,Store,Product,Price,Responses,Views] ] 
    my $count = 0 ;
    while(my $row = <$fileHandler>)
    {
        $row = findIds($count,$row,\@promoMatrix);
        $row = findStores($count, $row,\@promoMatrix);
        $row = findPrices($count,$row,\@promoMatrix);

        my $product = $row; #after we exclude id,store and price from row all we have left is product
        $product =~ s/\s([\-]|por)\s$//i; # remove - and por at end of $product string
        $promoMatrix[$count][PRODUCT] = $product;
        ++$count ;
    }
    close $fileHandler;
    replaceStoreNames(\@promoMatrix); # \@promoMatrix = Reference to @promoMatrix
    return @promoMatrix;
}

#Subroutine to replace abbreviated store names to correct ones
# $promoMatrixReference -> void
sub replaceStoreNames
{
    my ($promoMatrixRef) = @_;
    my %stores = (
        'sub' => "Submarino",
        'marino' => "Submarino",
        'amaz' => "Amazon",
        'frio' => "PontoFrio",
        'fast' => "FastShop",
        'rapi' => "FastShop",
        'temp' => "ShopTime",
        'time' => "ShopTime",
        'luiza' => "Magazine Luiza",
        'maga' => "Magazine Luiza",
        'bahia' => "Casas Bahia",
        'ricard' => "Ricardo Eletro",
        'barat' => "SouBarato",
        'wal' => "Walmart"
    );
    my @abbreviations = keys %stores;

    for(my $count = 0; $count < @$promoMatrixRef; $count++ )
    {
        foreach my $i (@abbreviations)
        {
            if ( index(lc($$promoMatrixRef[$count][STORE]) , $i) > -1) # index(string,substring) returns first position of substring in string, -1 if not found
            {                                                      # lc(string) returns lowercase string
                $$promoMatrixRef[$count][STORE] = $stores{$i}; #if abbreviation found replace it by its value in %stores hash
            }
        }
    }
}

#Subrotine to search for substrings in a matrix in a given column  
#   returns a matrix(promoMatrix format) with rows that have the given name at given column
# string, constant, matrixRef -> matrix
sub searchNameInMatrix
{
    my ($name,$column, $matrixRef) = @_;
    my @auxMatrix;
    my $count = 0; 
    for(my $index = 0; $index < @$matrixRef; $index++ )
    {
        if($$matrixRef[$index][$column] =~ /($name)/gi) #global and case insensitive
        {
            $auxMatrix[$count] = $$matrixRef[$index];
            ++$count;
        }
    }
    return @auxMatrix ;
}

sub searchStoreInMatrix
{
    my ($storeName) = @_;
    my @auxMatrix = generatePromoMatrix("posts.txt");
    @auxMatrix = searchNameInMatrix($storeName,STORE,\@auxMatrix);
    printMatrix(\@auxMatrix,"storePromotions.txt");
    return "storePromotions.txt";
}

sub searchProductInMatrix
{
    my ($productName) = @_;
    my @auxMatrix = generatePromoMatrix("posts.txt");
    @auxMatrix = searchNameInMatrix($productName,PRODUCT,\@auxMatrix);
    printMatrix(\@auxMatrix,"productPromotions.txt");
    return "productPromotions.txt";
}

#Subroutine to search for products higher or smaller than given price
#   returns a matrix(promoMatrix format) with rows that meet the price option
# float, int , matrixRef -> matrix
sub searchPriceInMatrix 
{
    my ($price,$option, $matrixRef) = @_ ; #option = 0 for <= | option = 1 for >=
    my @auxMatrix;
    my $count = 0;
    if ($option == 0)
    {
        for(my $index = 0; $index < @$matrixRef; $index++ )
        {
            if($$matrixRef[$index][PRICE] <= $price) 
            {
                $auxMatrix[$count] = $$matrixRef[$index];
                ++$count;
            }
        }
    }
    elsif ($option == 1)
    {
        for(my $index = 0; $index < @$matrixRef; $index++ )
        {
            if($$matrixRef[$index][PRICE] >= $price) 
            {
                $auxMatrix[$count] = $$matrixRef[$index];
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
# float, float -> matrix
sub searchPriceRangeInMatrix 
{
    my ($minPrice,$maxPrice) = @_;
    my @promoMatrix = generatePromoMatrix("posts.txt");
    my @auxMatrix;
    if( ($minPrice >= $maxPrice) | ($maxPrice < $minPrice) ) 
    {
       # print "ERROR: The price Range is wrong\n";
        return '0';
    }
    else
    {
        @auxMatrix = searchPriceInMatrix($maxPrice,0,\@promoMatrix); # lower than max price
        @auxMatrix = searchPriceInMatrix($minPrice,1,\@auxMatrix); # higher than min price
        printMatrix(\@auxMatrix,"priceRangePromotions.txt");
        return "priceRangePromotions.txt";
    }    
}
