#!/bin/bash


# Sean Szumlanski
# COP 3502, Fall 2018

# =============================
# LonelyPartyArray: test-all.sh
# =============================
# You can run this script at the command line like so:
#
#   bash test-all.sh
#
# For more details, see the assignment PDF.


################################################################################
# Shell check.
################################################################################

# Running this script with sh instead of bash can lead to false positives on the
# test cases. Yikes! These checks ensure the script is not being run through the
# Bourne shell (or any shell other than bash).

if [ "$BASH" != "/bin/bash" ]; then
  echo ""
  echo " Bloop! Please use bash to run this script, like so: bash test-all.sh"
  echo ""
  exit
fi

if [ -z "$BASH_VERSION" ]; then
  echo ""
  echo " Bloop! Please use bash to run this script, like so: bash test-all.sh"
  echo ""
  exit
fi


################################################################################
# Check header file integrity.
################################################################################

if [ ! -f checksum.dat ]; then
	echo ""
	echo " Error: You must also place checksum.dat in this directory before"
	echo "        we can proceed. Aborting test script."
	echo ""
	exit
fi

if [ -f LonelyPartyArray.h ]; then
	# Check integrity of header file.
	md5sum -c checksum.dat > /dev/null 2> /dev/null
	checksum_val=$?

	# Check for  failure.
	if [[ $checksum_val -eq 127 ]]; then
		echo ""
		echo "================================================================"
		echo "WARNING (md5sum)"
		echo "================================================================"
		echo ""
		echo "  Normally, this script would use a program called md5sum to"
		echo "  check that LonelyPartyArray.h hasn't been modified at all."
		echo "  However, it looks like md5sum isn't installed on your system,"
		echo "  so we're skipping that check. This is not a big deal, as long"
		echo "  as you're sure you haven't modified that header file at all."
	elif [[ $checksum_val != 0 ]]; then
		echo ""
		echo " Error: The LonelyPartyArray.h file has been modified. You must"
		echo "        place an unmodified version of LonelyPartyArray.h in this"
		echo "        directory in order to run this test script."
		echo ""
		exit
	fi
fi


################################################################################
# Initialization.
################################################################################

PASS_CNT=0
NUM_TEST_CASES=16
TOTAL_TEST_CNT=`expr $NUM_TEST_CASES + $NUM_TEST_CASES`


################################################################################
# Magical incantations.
################################################################################

# Ensure that obnoxious glibc errors are piped to stderr.
export LIBC_FATAL_STDERR_=1

# Now redirect all local error messages to /dev/null (like "process aborted").
exec 2> /dev/null


################################################################################
# Check that all required files are present.
################################################################################

if [ ! -f LonelyPartyArray.c ]; then
	echo ""
	echo " Error: You must place LonelyPartyArray.c in this directory before"
	echo "        we can proceed. Aborting test script."
	echo ""
	exit
elif [ ! -f LonelyPartyArray.h ]; then
	echo ""
	echo " Error: You must place LonelyPartyArray.h in this directory before"
	echo "        we can proceed. Aborting test script."
	echo ""
	exit
elif [ ! -f SanityCheck.c ]; then
	echo ""
	echo " Error: You must place SanityCheck.c in this directory before"
	echo "        we can proceed. Aborting test script."
	echo ""
	exit
elif [ ! -f CloneTest.c ]; then
	echo ""
	echo " Error: You must place CloneTest.c in this directory before"
	echo "        we can proceed. Aborting test script."
	echo ""
	exit
elif [ ! -d sample_output ]; then
	echo ""
	echo " Error: You must place the sample_output folder in this directory"
	echo "        before we can proceed. Aborting test script."
	echo ""
	exit
elif [ ! -f sample_output/SanityCheckOutput.txt ]; then
	echo ""
	echo " Error: You must place SanityCheckOutput.txt in the sample_output"
	echo "        directory before we can proceed. Aborting test script."
	echo ""
	exit
elif [ ! -f sample_output/CloneTestOutput.txt ]; then
	echo ""
	echo " Error: You must place CloneTestOutput.txt in the sample_output"
	echo "        directory before we can proceed. Aborting test script."
	echo ""
	exit
fi

for i in `seq -f "%02g" 1 $NUM_TEST_CASES`;
do
	if [ ! -f testcase$i.c ]; then
		echo ""
		echo " Error: You must place testcase$i.c in this directory before we"
		echo "        can proceed. Aborting test script."
		echo ""
		exit
	fi
done

for i in `seq -f "%02g" 1 $NUM_TEST_CASES`;
do
	if [ ! -f sample_output/output$i.txt ]; then
		echo ""
		echo " Error: You must place output$i.txt in the sample_output directory"
		echo "        before we can proceed. Aborting test script."
		echo ""
		exit
	fi
done

egrep -s -q "^#include \"LonelyPartyArray\.h\"" LonelyPartyArray.c
egrep_val=$?

if [[ $egrep_val != 0 ]]; then
	echo ""
	echo "  Whoa, buddy! Your LonelyPartyArray.c file does not appear to have"
	echo "  a proper #include statement for LonelyPartyArray.h. Please read"
	echo "  Section 2 of the assignment PDF before proceeding."
	echo ""
	exit
fi


################################################################################
# Run sanity check.
################################################################################

echo ""
echo "================================================================"
echo "Checking sizeof() values on this system..."
echo "================================================================"
echo ""

echo -n "  [Sanity Check] SanityCheck.c ... "

function run_sanity_check()
{
	# Attempt to compile.
	gcc LonelyPartyArray.c SanityCheck.c 2> /dev/null
	compile_val=$?
	if [[ $compile_val != 0 ]]; then
		echo "fail (failed to compile)"
		return
	fi

	# Run program. Capture return value to check whether it crashes.
	./a.out > sanitycheck_output.txt 2> /dev/null
	execution_val=$?
	if [[ $execution_val != 0 ]]; then
		echo "fail (program crashed)"
		return
	fi

	# Run diff and capture its return value.
	diff sanitycheck_output.txt sample_output/SanityCheckOutput.txt > /dev/null
	diff_val=$?

	# Output results based on diff's return value.
	if  [[ $diff_val != 0 ]]; then
		echo "fail (output mismatch)"
		echo ""
		echo "================================================================"
		echo "WARNING! WARNING! WARNING!"
		echo "================================================================"
		echo ""
		echo "  According to SanityCheck.c, your system appears to be using"
		echo "  non-standard sizeof() values for the following data type(s):"
		echo ""
		cat sanitycheck_output.txt

	else
		echo "PASS!"
	fi
}

run_sanity_check


################################################################################
# Run test cases.
################################################################################

echo ""
echo "================================================================"
echo "Running test cases..."
echo "================================================================"
echo ""

# Function for running a single test case.
function run_test_case()
{
	local testcase_file=$1
	local output_file=$2

	echo -n "  [Test Case] $testcase_file ... "

	# Attempt to compile.
	gcc LonelyPartyArray.c $testcase_file 2> /dev/null
	compile_val=$?
	if [[ $compile_val != 0 ]]; then
		echo "fail (failed to compile)"
		return
	fi

	# Run program. Capture return value to check whether it crashes.
	./a.out > myoutput.txt 2> /dev/null
	execution_val=$?
	if [[ $execution_val != 0 ]]; then
		echo "fail (program crashed)"
		return
	fi

	# Run diff and capture its return value.
	diff myoutput.txt sample_output/$output_file > /dev/null
	diff_val=$?
	
	# Output results based on diff's return value.
	if  [[ $diff_val != 0 ]]; then
		echo "fail (output mismatch)"
	else
		echo "PASS!"
		PASS_CNT=`expr $PASS_CNT + 1`
	fi
}

for i in `seq -f "%02g" 1 $NUM_TEST_CASES`;
do
	run_test_case "testcase$i.c" "output$i.txt"
done

rndnum=$RANDOM
thresh=40

if [ "$rndnum" -le "$thresh" ]; then
	echo ""
	echo "================================================================"
	echo "Eustis seems to be quite intrigued by your code..."
	echo "================================================================"
	echo ""
fi


################################################################################
# Check for memory leaks: run test cases through valgrind.
################################################################################

echo ""
echo "================================================================"
echo "Checking for memory leaks with valgrind..."
echo "================================================================"
echo ""

# Function for running a single test case through valgrind.
function run_valgrind_test()
{
	local testcase_file=$1
	local output_file=$2

	echo -n "  [Memory Leak Check] $testcase_file ... "

	# Attempt to compile.
	gcc LonelyPartyArray.c testcase$i.c -g 2> /dev/null
	compile_val=$?
	if [[ $compile_val != 0 ]]; then
		echo "fail (failed to compile)"
		return
	fi

	# Run program through valgrind. Check whether program crashes.
	valgrind --leak-check=yes ./a.out > myoutput.txt 2> err.log
	execution_val=$?
	if [[ $execution_val != 0 ]]; then
		echo "fail (program crashed)"
		return
	fi

	# Check output for indication of memory leaks.
	grep --silent "no leaks are possible" err.log
	valgrindfail=$?
	if [[ $valgrindfail != 0 ]]; then
		echo "fail (memory leak detected)"
		return
	fi

	# Run diff and capture its return value.
	diff myoutput.txt sample_output/$output_file > /dev/null
	diff_val=$?
	
	# Output results based on diff's return value.
	if  [[ $diff_val != 0 ]]; then
		echo "fail (output mismatch)"
	else
		echo "PASS!"
		PASS_CNT=`expr $PASS_CNT + 1`
	fi
}

for i in `seq -f "%02g" 1 $NUM_TEST_CASES`;
do
	run_valgrind_test "testcase$i.c" "output$i.txt"
done


################################################################################
# Run bonus test case. Don't count toward final count.
################################################################################

echo ""
echo "================================================================"
echo "Running bonus test case for cloneLonelyPartyArray()..."
echo "================================================================"
echo ""

function run_bonus_test ()
{
	echo -n "  [Bonus Test Case] CloneTest.c ... "

	# Attempt to compile.
	gcc LonelyPartyArray.c CloneTest.c 2> /dev/null
	compile_val=$?
	if [[ $compile_val != 0 ]]; then
		echo "fail (failed to compile)"
		return
	fi

	# Run program. Capture return value to check whether it crashes.
	./a.out > clonetest_output.txt 2> /dev/null
	execution_val=$?
	if [[ $execution_val != 0 ]]; then
		echo "fail (program crashed)"
		return
	fi

	# Run diff and capture its return value.
	diff clonetest_output.txt sample_output/CloneTestOutput.txt > /dev/null
	diff_val=$?
	
	# Output results based on diff's return value.
	if  [[ $diff_val != 0 ]]; then
		echo "fail (output mismatch)"
	else
		echo "PASS!"
	fi
}

run_bonus_test


################################################################################
# Cleanup phase.
################################################################################

# Clean up the executable and output files generated by this script.
rm -f a.out
rm -f err.log
rm -f sanitycheck_output.txt
rm -f clonetest_output.txt
rm -f myoutput.txt


################################################################################
# Final thoughts.
################################################################################

echo ""
echo "================================================================"
echo "Final Report"
echo "================================================================"

if [ $PASS_CNT -eq $TOTAL_TEST_CNT ]; then
	echo ""
	echo "              ,)))))))),,,"
	echo "            ,(((((((((((((((,"
	echo "            )\\\`\\)))))))))))))),"
	echo "     *--===///\`_    \`\`\`((((((((("
	echo "           \\\\\\ b\\  \\    \`\`)))))))"
	echo "            ))\\    |     ((((((((               ,,,,"
	echo "           (   \\   |\`.    ))))))))       ____ ,)))))),"
	echo "                \\, /  )  ((((((((-.___.-\"    \`\"((((((("
	echo "                 \`\"  /    )))))))               \\\`)))))"
	echo "                    /    ((((\`\`                  \\((((("
	echo "              _____|      \`))         /          |)))))"
	echo "             /     \\                 |          / ((((("
	echo "            /  --.__)      /        _\\         /   )))))"
	echo "           /  /    /     /'\`\"~----~\`  \`.       \\   (((("
	echo "          /  /    /     /\`              \`-._    \`-. \`)))"
	echo "         /_ (    /    /\`                    \`-._   \\ (("
	echo "        /__|\`   /   /\`                        \`\\\`-. \\ ')"
	echo "               /  /\`                            \`\\ \\ \\"
	echo "              /  /                                \\ \\ \\"
	echo "             /_ (                                 /_()_("
	echo "            /__|\`                                /__/__|"
	echo ""
	echo "                             Legendary."
	echo ""
	echo "                10/10 would run this program again."
	echo ""
	echo "  CONGRATULATIONS! You appear to be passing all required test"
	echo "  cases! (Now, don't forget to create some extra test cases of"
	echo "  your own. These test cases are not necessarily comprehensive.)"
	echo ""
else
	echo "                           ."
	echo "                          \":\""
	echo "                        ___:____     |\"\\/\"|"
	echo "                      ,'        \`.    \\  /"
	echo "                      |  o        \\___/  |"
	echo "                    ~^~^~^~^~^~^~^~^~^~^~^~^~"
	echo ""
	echo "                           (fail whale)"
	echo ""
	echo "Note: The fail whale is friendly and adorable! He is not here to"
	echo "      demoralize you, but rather, to bring you comfort and joy"
	echo "      in your time of need. \"Keep plugging away,\" he says! \"You"
	echo "      can do this!\""
	echo ""
fi
