my $filename = 'posts.html';

open(my $fh, '<',$filename) or 
    die "Could not open file '$filename' '$!'";

while(my $row = <$fh>)
{
    #Return everything inside [ ] or ( )
    #[] is $1 and () is $2
    if($row =~ /\[(.*?)\]|\((.*?)\)/g)
    {
        print "$2\n";
    } 
}


print "Done\n";
close $fh;