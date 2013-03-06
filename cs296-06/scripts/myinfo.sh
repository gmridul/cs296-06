#! /bin/bash

echo `date '+Today is %A, %d %B, %Y.'`

num_seconds_today=`date '+%s'`

num_seconds_bday=`date --date='Aug 07 08:09:00' '+%s'`
num_difference=$(($num_seconds_bday-$num_seconds_today))
num_hours_left=$(($num_difference/3600))
num_days_left=$((num_hours_left/24))
num_weeks_left=$((num_days_left/7))
num_days_left=$((num_days_left%7))
num_hours_left=$((num_hours_left%24))
echo "There are $num_weeks_left weeks $num_days_left days and $num_hours_left hours left for the birthday of Sagar"

num_seconds_bday=`date --date='09 Nov' '+%s'`
num_difference=$(($num_seconds_bday-$num_seconds_today))
num_hours_left=$(($num_difference/3600))
num_days_left=$((num_hours_left/24))
num_weeks_left=$((num_days_left/7))
num_days_left=$((num_days_left%7))
num_hours_left=$((num_hours_left%24))
echo "There are $num_weeks_left weeks $num_days_left days and $num_hours_left hours left for the birthday of Mridul"

num_seconds_bday=`date --date='25 Sep' '+%s'`
num_difference=$(($num_seconds_bday-$num_seconds_today))
num_hours_left=$(($num_difference/3600))
num_days_left=$((num_hours_left/24))
num_weeks_left=$((num_days_left/7))
num_days_left=$((num_days_left%7))
num_hours_left=$((num_hours_left%24))
echo "There are $num_weeks_left weeks $num_days_left days and $num_hours_left hours left for the birthday of Sudipto"

echo "Thank you for asking, `whoami`"

up_time=`uptime`

awk '{
time=$1
minutes=int((time/60))%60
if (minutes < 10)
{
print("Your system has been running for "int(time/86400) " days, " int((time/3600))%24":0" minutes " hours.")
}
else
{
print("Your system has been running for "int(time/86400) " days, " int((time/3600))%24":" minutes " hours.")
}
}' /proc/uptime

df -B GB | awk '{
if (NR==2)
{
print("The current disk on which your home folder is located is " $1 " and is " $5 " full")
}
}'

str_1=`lsb_release -c`
str_2=`lsb_release -r`
echo "You are running ${str_1:10} and ${str_2:9} with Kernel `uname -v`"

free -m | awk '{
if(NR==2)
{
print("Your machine has " $2/1024 " GB RAM. Of which " ($3/$2)*100 "% is in use.")
}
}'

cd scripts/
num_lines=`wc myinfo.sh -l | cut -d" " -f 1`
num_words=`wc -w myinfo.sh | cut -d" " -f 1`

awk -v lines=$num_lines -v words=$num_words '{
for (i= 1; i<=NF; i++)
{
count=count+length($i)
}
if (NR==lines-1)
{
printf "This script has %d words, %d lines and %d characters (without counting whitespace)\n",words,lines,count
}
}' myinfo.sh