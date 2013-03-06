#!/bin/bash

i=$(whoami)

ps aux | grep firefox | tr -s ' ' | awk -v user=$i '{
	if($11 ~ /\/usr\/lib\/firefox/ )  {
		printf "%d %s\n",$2,$1
		if(user == $1) { 
			printf "Do you want to kill the firefox process\n"
			getline reply < "/dev/tty"
			if(reply=="y" || reply=="Y") {
				system( "kill " $2 )
			}
			exit
		}
		else {
			printf "%s does not have permission to terminate the firefox process\n",user
			exit
		}
	}
}'

