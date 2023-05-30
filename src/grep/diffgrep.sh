#!/bin/bash

# Uncomment the following line to enable debugging output
#set -x

# Set initial counts for success and failure
success=0
failure=0

rm results.txt

# Redirect failure results to results.txt
for i in {1..185}; do
    echo ----------------------------------------------*GREP $i
    # Run the test using grep and output to file1
    grep_args=$(sed -n "${i}p" test/grep_args.txt)
    grep $grep_args > file1
    # Run the test using s21_grep and output to file2
    s21_grep_args=$(sed -n "${i}p" test/s21_grep_args.txt)
    ./s21_grep $s21_grep_args > file2
    # Compare the contents of file1 and file2 and output whether there are any differences or not
    if diff -q -s file1 file2; then
        echo -e "\033[32m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $t"
        ((success++))
    else
        echo -e "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m grep $t"
        ((failure++))
        echo "Failure in GREP $i" >> results.txt
    fi
    # Remove the temporary files file1 and file2
    rm file1 file2
done

# Display final counts of success and failure
echo "Tests completed: $((success+failure))"
echo -e "\033[32mSuccess: $success\033[0m"
echo -e "\033[31mFailure: $failure\033[0m"