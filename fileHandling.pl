use warnings; use strict;

my $filename = 'posts.html';


open(my $fh, '<',$filename) or 
    die "Could not open file '$filename' '$!'";




#push @products, [(0)x$numberOfLines] for (0..$numberOfLines);   #id store name

while(my $row = <$fh>)
{
    #Return everything inside [ ] or ( ) after first whitespace
    #[] is $1 and () is $2

    
    while($row =~ /^\S\s\"\[(.*?)\]|^\S\s\"\((.*?)\)/gi)
    {
        #$products[$index][0] = $row =~ /(.*?)/;
        if($1)
        {            
            print "$1\n";
         #   $products[$index][1] = $1;
        }
        if($2)
        {
            print "$2\n";
          #  $products[$index][1] = $1;                 
        }
    } 
}

print "Done\n";
#print $products[1][0];
close $fh;