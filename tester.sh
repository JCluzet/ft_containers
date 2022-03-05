# define colors
RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'

make re > /dev/null 2>&1
output=$(./container)

printf "FT::\n\n$output\n\n\n\n----------------------------------------------\n"

mv main.cpp mainback
cat mainback | sed 's/ft::stack/std::stack/g' | sed 's/ft::vector/std::vector/g' > main.cpp


make re > /dev/null 2>&1

output2=$(./container)

printf "STD::\n\n$output2\n"


diff=$(diff <(echo "$output") <(echo "$output2"))
printf "\n\nRESULT : "
# if diff is empty, then the two files are the same, else output diff
if [ -z "$diff" ]; then
    printf "$GREEN Test passed with same output :)$RESET\n\n"
else
    printf "$RED Test failed !$RESET\n"
    printf "$diff\n"
fi

printf "Restoring old version...\n"
rm main.cpp
mv mainback main.cpp