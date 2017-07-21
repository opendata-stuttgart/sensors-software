#! /usr/bin/perl
use strict;

#$data_file="/dev/cu.wchusbserial1410";

my $data_file = shift or die "Usage: $0 <device path>\n";

open (FILE, $data_file) or die ("Could not open file!"); 

my $len=0;
my $PM10 = 0;
my $PM25 = 0;
my $checksum_is = 0;
my $checksum_should = 0;
my $buffer = 0;

while (1) {
	$len = 0;
	$PM10 = 0;
	$PM25 = 0;
	$checksum_is = 0;
	$checksum_should = 0;
	while($len!=10){
		read (FILE, $buffer, 1);
		printf ("%d Hex Format: %02lX - Dec Format: %d\n",$len,ord($buffer),ord($buffer));
		if ($len==0) { if (ord($buffer) != 170) { $len = -1; }; };
		if ($len==1) { if (ord($buffer) != 192) { $len = -1; }; };
		if ($len==2) { $checksum_is+=ord($buffer);$PM25 += ord($buffer); };
		if ($len==3) { $checksum_is+=ord($buffer);$PM25 += 256*ord($buffer); $PM25=$PM25; };
		if ($len==4) { $checksum_is+=ord($buffer);$PM10 += ord($buffer); };
		if ($len==5) { $checksum_is+=ord($buffer);$PM10 += 256*ord($buffer); $PM10=$PM10; };
		if ($len==6) { $checksum_is+=ord($buffer); }
		if ($len==7) { $checksum_is+=ord($buffer); }
		if ($len==8) { $checksum_should+=ord($buffer); }
		$len++;
	}

	print "PM2.5: ".($PM25/10)."\n";
	print "PM10: ".($PM10/10)."\n";
	print "Checksum is: $checksum_is - Checksum_should: $checksum_should\n";

}

print "\n=====End of Script=====";

close(FILE);
