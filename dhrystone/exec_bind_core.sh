#! /bin/bash
rm nohup.out
nohup ./build_x86/dhrystone &

mode=0
# 0--min,1--mid,2--max

process='dhrystone'
pid=$(ps x | grep $process | grep -v grep | awk '{print $1}')
echo "running dhrystone pid: " $pid

# bind 8155 min kernel
if [ $mode -eq 0 ]
then 
   # cd /sys/devices/system/cpu/cpufreq/policy0
   # echo 1785600 > scaling_min_freq
   # taskset -p f pid
   echo "test success"
fi

# bind 8155 mid kernel
if [ $mode -eq 1 ] 
then
   cd /sys/devices/system/cpu/cpufreq/policy4
   echo 2131200 > scaling_min_freq
   taskset -p f pid
fi

# bind 8155 max kernel
if [ $mode -eq 2 ]
then
   cd /sys/devices/system/cpu/cpufreq/policy7
   echo 2419200 > scaling_min_freq
   taskset -p f pid
fi

# Wait for test results to be generated

PID_EXIST=$(pgrep dhrystone)

while [ $PID_EXIST ]; do
    echo "waiting"
    PID_EXIST=$(pgrep dhrystone)
    sleep 1
done
# view test results

echo "DMIPS generated"
cat nohup.out | grep -n "DMIPS"
