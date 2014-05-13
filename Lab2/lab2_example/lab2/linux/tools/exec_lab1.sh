#!/bin/sh 
############################################################################
# File Name  : exec_lab1.sh
# Date       : Sep. 2011
# Author     : i.huang@ecemail.uwaterloo.ca
# Usage      : exec_lab1.sh <exec_name> <N> <B> <X>
#              exec_name: executible's name
#              N: number of items to produce
#              B: buffer size
#              X: number of times to run the executible for a given <N,B> pair 
#
#              For example: the following run './produce 20 8' 30 times
#              ./exec_lab1.sh ./produce 20 8 30
#
# Course Name: ECE254 Operating Systems and System Programming
# Description: Lab1 utility - extracting timing info.
#              The script assumes the following output format at stdout
#  -------------------------------------------
#  random char 1
#  random char 2
#  ...
#  random char N
#  time to initialize system: S1 seconds
#  time to transmit data: S2 seconds
#  -------------------------------------------
#  The script reads the last two lines where the timing info is and
#  then extract the S1 and S2 and output "S1 S2" in a line in the 
#  outputfile (${O_FILE} in the script)
#############################################################################

#echo $#
PID=$$
#echo $PID
if [ $# != 4 ]; then
    echo "Usage: $0 <exec_name> <N> <B> <X>" 
    echo "  exec_name: executible's name"
    echo "  N: number of items to produce"
    echo "  B: buffer size"
    echo "  X: number of times to run the executible for a given <N,B> pair "
    exit 1
else
    PROGRAM=$1
    NUM2PRODUCE=$2
    BUFFER_SIZE=$3
    X_TIMES=$4
fi

O_FILE='out_N'${NUM2PRODUCE}'_B'${BUFFER_SIZE}'_X'${X_TIMES}'_pid'${PID}.'dat'
touch ${O_FILE}

x=1
while [ ${x} -le ${X_TIMES} ]
do
    cmd="${PROGRAM} ${NUM2PRODUCE} ${BUFFER_SIZE}"
    str=`$cmd | tail -2 | awk -F: '{print $2}' | awk '{print $1}'`
    echo $str  >> ${O_FILE}
    x=`expr $x + 1`
done
