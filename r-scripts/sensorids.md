# sensor id list from django config page

7
25
33
39
40
42
44
45
48
51
52
66
67
68
71
80
81
83
84
87
88


    grep -o 'value="[0-9]*"' ~/Downloads/sensors.html | grep -o '[0-9]*'| sort -n
