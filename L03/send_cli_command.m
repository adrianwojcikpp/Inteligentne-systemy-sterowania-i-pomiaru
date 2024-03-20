argv = "./apc -aefm -r 1000 -u deg"; 
argc = numel(strsplit(strtrim(argv)));
cmd = char(argc)+argv;
udp_send(cmd)