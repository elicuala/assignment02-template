dir="Testcases/Milestone Test Cases"
for input in "$dir"/*-input.txt; do
    expected="${input%-input.txt}-output.txt"
    if ./assg < "$input" | diff -q - "$expected" > /dev/null; then
        echo "PASS: $input"
    else
        echo "FAIL: $input"
    fi
done