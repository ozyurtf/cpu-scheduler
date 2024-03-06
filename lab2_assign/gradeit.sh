#!/bin/bash

# Author: Hubertus Franke  (frankeh@cims.nyu.edu)

DIR1=$1
DIR2=$2

#------- some simple error checking on the parameters                                               
usage() {
    [[ "${1}" == "" ]] || echo "${1}"
    echo "usage(): $0 <referencoutputdir> <youroutputdir>"
    exit
}

[[ ${#} -lt 2 ]]        && usage ""                             # check right arguments
[[ ! -d ${1} ]]         && usage "<${1}> not a valid directory" # check reference dir
[[ ! -d ${2} ]]         && usage "<${2}> not a valid directory" # check youroutput dir
[[ "${1}" == "${2}" ]]  && usage "directories are identical"    # 

#------- passed basic test now lets run                                                             

LOG=${3:-${DIR2}/LOG.txt}
DARGS="-B"
INS="`seq 0 7`"
OUTPRE="out"

SCHEDS="   F    L    S   R2   R5   P2   P5:3 E2:5  E4"  

#SCHEDS="   F"     # example if you only want to run the F scheduler during development

############################################################################
#  NO TRACING 
############################################################################

# run with RFILE1 RFILE2

declare -ai counters
declare -i x=0
for s in ${SCHEDS}; do 
	let counters[$x]=0
	let x=$x+1
done

#OUTLINE="SUM"
#x=0
#for s in ${SCHEDS}; do 
#	OUTLINE=`printf "%s %2d " "${OUTLINE}" "${counters[$x]}"`
#	let x=$x+1
#done
#echo "${OUTLINE}"

declare -i COUNT=0
declare -i TESTCASES=0

rm -f ${LOG}
echo "in ${SCHEDS}"
for f in ${INS}; do
	OUTLINE=`printf "%02d" ${f}`
	x=0
	for s in ${SCHEDS}; do 
		COUNT=0

			let TESTCASES=${TESTCASES}+1
			OUTF="${OUTPRE}_${f}_${s//\:/_}"
			if [[ ! -e ${DIR1}/${OUTF} ]]; then
				echo "${DIR1}/${OUTF} does not exist" >> ${LOG}
			elif [[ ! -e ${DIR2}/${OUTF} ]]; then
				echo "${DIR2}/${OUTF} does not exist" >> ${LOG}
            else	
                diff -b ${DARGS} ${DIR1}/${OUTF} ${DIR2}/${OUTF} 2>&1 > /dev/null
                if [[ $? -eq 0 ]]; then
				    COUNT=`expr ${COUNT} + 1`
			    else
				    echo "diff -b ${DARGS} ${DIR1}/${OUTF} ${DIR2}/${OUTF}" >> ${LOG}
				    SUMX=`egrep "^SUM" ${DIR1}/${OUTF}`
				    SUMY=`egrep "^SUM" ${DIR2}/${OUTF}`
				    echo "DIR1-SUM ==> ${SUMX}" >> ${LOG}
				    echo "DIR2-SUM ==> ${SUMY}" >> ${LOG}
                fi
			fi

		OUTLINE=`printf "%s   %2d" "${OUTLINE}" "${COUNT}"`
		#echo `expr ${counters[$x]} + ${COUNT}`
		let counters[$x]=`expr ${counters[$x]} + ${COUNT}`
		let x=$x+1
	done
	echo "${OUTLINE}"
done

#x=0
#for s in ${SCHEDS}; do 
#	printf "%d " ${counters[$x]}
#	let x=$x+1
#done

echo
OUTLINE="SUM"
x=0
TOTAL=0
for s in ${SCHEDS}; do 
	OUTLINE=`printf "%s  %2d " "${OUTLINE}" "${counters[$x]}"`
	let TOTAL=${TOTAL}+${counters[$x]}
	let x=$x+1
done
PTS=`echo "scale=4; 60.0*(${TOTAL}.0 / ${TESTCASES}.0)" | bc`
RESULT=`echo "scale=4; 40+${PTS}" | bc`

echo "${OUTLINE}"
echo "${TOTAL} out of ${TESTCASES} correct"
