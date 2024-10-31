#!/usr/bin/perl
use strict;
use warnings;
# Add the path to your local Perl modules
BEGIN {
    eval {
        require CGI;
    };
    if ($@) {
        # If CGI is not found, add local library paths dynamically
        my @possible_libs = (
            "/home/rperez-t/perl5/lib/perl5",
            "/home/abaccari/perl5/lib/perl5",
            "/home/jsteenpu/perl5/lib/perl5"
        );
        foreach my $lib (@possible_libs) {
            if (-d $lib) {
                # If the directory exists, add it to @INC
                eval "use lib '$lib';";
            }
        }
        # Try loading CGI again after adding local paths
        eval {
            require CGI;
        };
        if ($@) {
            die "CGI module not found in any path!";
        }
    }
}
use CGI;

my $cgi = CGI->new;
my $name = $cgi->param('name') || 'World';

my $filename = './basicweb/site/cgi/cgiGetBeginPerl.html';
my $filename2 = './basicweb/site/cgi/cgiGetEnd.html';

# Print the beginning of the html
open(my $fh, '<', $filename) or die "Could not open file '$filename' $!";
while (my $line = <$fh>) {
    print $line;
}
close($fh);
# Print the HTML response
print "<h1>My first Perl CGI</h1><h2>Hello, $name!</h2>";
#Print the end of the html
open(my $fh2, '<', $filename2) or die "Could not open file '$filename2' $!";
while (my $line = <$fh2>) {
    print $line;
}
close($fh2);