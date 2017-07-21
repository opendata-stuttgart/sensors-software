#! /usr/bin/perl
use strict;

my $data_file = shift or die "Usage: $0 <device path>\n";

open (FILE, $data_file) or die ("Could not open file!"); 

my $len=0;
my $framelength = 0;
my $PM1cf = 0;
my $PM10cf = 0;
my $PM25cf = 0;
my $PM1 = 0;
my $PM10 = 0;
my $PM25 = 0;
my $PM03cnt = 0;
my $PM05cnt = 0;
my $PM1cnt = 0;
my $PM10cnt = 0;
my $PM25cnt = 0;
my $checksum_is = 0;
my $checksum_should = 0;
my $buffer = 0;

while (1) {
	$len = 0;
	$PM1 = 0;
	$PM10 = 0;
	$PM25 = 0;
	$checksum_is = 0;
	$checksum_should = 0;
	while($len!=32){
		read (FILE, $buffer, 1);
		printf ("%d Hex Format: %02lX - Dec Format: %d\n",$len,ord($buffer),ord($buffer));
		if ($len==0) { if (ord($buffer) != 66) { $len = -1 }; };
		if ($len==1) { if (ord($buffer) != 77) { $len = -1 }; };
		if ($len==2) { $checksum_is =ord($buffer);$framelength  = 256*ord($buffer); };
		if ($len==3) { $checksum_is+=ord($buffer);$framelength += ord($buffer); };
		if ($len==4) { $checksum_is+=ord($buffer);$PM1cf     = 256*ord($buffer); };
		if ($len==5) { $checksum_is+=ord($buffer);$PM1cf    += ord($buffer); };
		if ($len==6) { $checksum_is+=ord($buffer);$PM25cf    = 256*ord($buffer); };
		if ($len==7) { $checksum_is+=ord($buffer);$PM25cf   += ord($buffer); };
		if ($len==8) { $checksum_is+=ord($buffer);$PM10cf    = 256*ord($buffer); };
		if ($len==9) { $checksum_is+=ord($buffer);$PM10cf   += ord($buffer); };
		if ($len==10) { $checksum_is+=ord($buffer);$PM1      = 256*ord($buffer); };
		if ($len==11) { $checksum_is+=ord($buffer);$PM1     += ord($buffer); };
		if ($len==12) { $checksum_is+=ord($buffer);$PM25     = 256*ord($buffer); };
		if ($len==13) { $checksum_is+=ord($buffer);$PM25    += ord($buffer); };
		if ($len==14) { $checksum_is+=ord($buffer);$PM10     = 256*ord($buffer); };
		if ($len==15) { $checksum_is+=ord($buffer);$PM10    += ord($buffer); };
		if ($len==16) { $checksum_is+=ord($buffer);$PM03cnt  = 256*ord($buffer); };
		if ($len==17) { $checksum_is+=ord($buffer);$PM03cnt += ord($buffer); };
		if ($len==18) { $checksum_is+=ord($buffer);$PM05cnt  = 256*ord($buffer); };
		if ($len==19) { $checksum_is+=ord($buffer);$PM05cnt += ord($buffer); };
		if ($len==20) { $checksum_is+=ord($buffer); }
		if ($len==21) { $checksum_is+=ord($buffer); }
		if ($len==22) { $checksum_is+=ord($buffer); }
		if ($len==23) { $checksum_is+=ord($buffer); }
		if ($len==24) { $checksum_is+=ord($buffer); }
		if ($len==25) { $checksum_is+=ord($buffer); }
		if ($len==26) { $checksum_is+=ord($buffer); }
		if ($len==27) { $checksum_is+=ord($buffer); }
		if ($len==28) { $checksum_is+=ord($buffer); }
		if ($len==29) { $checksum_is+=ord($buffer); }
		if ($len==30) { $checksum_should = 256*ord($buffer); }
		if ($len==31) { $checksum_should += ord($buffer); }
		$len++;
	}

	$checksum_is += 143;

	print "PM1:   $PM1\n";
	print "PM2.5: $PM25\n";
	print "PM10:  $PM10\n";
	print "Checksum is: $checksum_is - Checksum_should: $checksum_should\n";

}

print "\n=====End of Script=====";

close(FILE);
