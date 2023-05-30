#!/bin/bash

# Uncomment the following line to enable debugging output
# set -x

# Set initial counts for success and failure
success=0
failure=0

# Loop through all the cat tests
for i in {1..452}; do
    echo ----------------------------------------------*CAT $i
    # Run the test using cat and output to file1
    cat_args=$(sed -n "${i}p" test/cat_args.txt)
    cat $cat_args > file1
    # Run the test using s21_cat and output to file2
    s21_cat_args=$(sed -n "${i}p" test/s21_cat_args.txt)
    ./s21_cat $s21_cat_args > file2
    # Compare the contents of file1 and file2 and output whether there are any differences or not
    if diff -q -s file1 file2; then
        echo "Success"
        ((success++))
    else
        echo "Failure"
        ((failure++))
    fi
    # Remove the temporary files file1 and file2
    rm file1 file2
done

# Display final counts of success and failure
echo "Tests completed: $((success+failure))"
echo "Success: $success"
echo "Failure: $failure"